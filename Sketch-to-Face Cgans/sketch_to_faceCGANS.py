#Loading Libraries
import os
from PIL import Image
from torch.utils.data import Dataset, DataLoader
import torchvision.transforms as transforms
import torch.nn.functional as F
import torch
import torch.nn as nn
import torch.optim as optim
from tqdm import tqdm
import torchvision.utils as vutils
import matplotlib.pyplot as plt

# Data Augmentation and Loading
class SketchFaceDataset(Dataset):
    def __init__(self, base_dir, phase='train', transform=None):
        self.sketch_dir = os.path.join(base_dir, phase, 'sketches')
        self.original_dir = os.path.join(base_dir, phase, 'photos')
        self.transform = transform

        # Get list of sketch files and ensure original files match
        self.sketch_files = sorted(os.listdir(self.sketch_dir))
        self.original_files = sorted(os.listdir(self.original_dir))

    def __len__(self):
        return len(self.sketch_files)

    def __getitem__(self, idx):
        sketch_path = os.path.join(self.sketch_dir, self.sketch_files[idx])
        original_path = os.path.join(self.original_dir, self.original_files[idx])

        sketch = Image.open(sketch_path).convert("RGB")
        original = Image.open(original_path).convert("RGB")

        if self.transform:
            sketch = self.transform(sketch)
            original = self.transform(original)

        return sketch, original

# Define transforms
transform = transforms.Compose([
    transforms.Resize((64, 64)),
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
])

# Base directory for dataset (adjust for Kaggle)
base_dir = "/kaggle/input/person-face-sketches/"

# Create datasets
train_dataset = SketchFaceDataset(base_dir, phase='train', transform=transform)
val_dataset = SketchFaceDataset(base_dir, phase='val', transform=transform)
test_dataset = SketchFaceDataset(base_dir, phase='test', transform=transform)

# Create DataLoaders
train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
val_loader = DataLoader(val_dataset, batch_size=64, shuffle=False)
test_loader = DataLoader(test_dataset, batch_size=64, shuffle=False)

# Check if the dataset is loading correctly
for sketches, originals in train_loader:
    print(f"Batch size: {sketches.shape}, {originals.shape}")
    break  # Print first batch only

#Generator Class
class Generator(nn.Module):
    def __init__(self):
        super(Generator,self).__init__()
        self.main=nn.Sequential(
            nn.ConvTranspose2d(100+3,512,4,1,0,bias=False),
            nn.BatchNorm2d(512),
            nn.ReLU(True),
            nn.ConvTranspose2d(512,256,4,2,1,bias=False),
            nn.BatchNorm2d(256),
            nn.ReLU(True),
            nn.ConvTranspose2d(256,128,4,2,1,bias=False),
            nn.BatchNorm2d(128),
            nn.ReLU(True),
            nn.ConvTranspose2d(128,64,4,2,1,bias=False),
            nn.BatchNorm2d(64),
            nn.ReLU(True),
            nn.ConvTranspose2d(64,3,4,2,1,bias=False),
            nn.Tanh()
        )

    def forward(self,noise,sketch):
        noise=noise.view(noise.size(0),100,1,1)
        sketch_pooled=F.adaptive_avg_pool2d(sketch,(1,1))
        combined_input=torch.cat([noise,sketch_pooled],dim=1)
        fake_images=self.main(combined_input)
        return fake_images

#Discriminator Class
class MinibatchDiscrimination(nn.Module):
    def __init__(self,in_features,out_features,num_kernels,kernel_dim):
        super(MinibatchDiscrimination,self).__init__()
        self.num_kernels=num_kernels
        self.out_features=out_features
        self.T=nn.Parameter(torch.randn(in_features,num_kernels,kernel_dim))

    def forward(self,x):
        M=x.mm(self.T.view(x.size(1),-1))
        M=M.view(-1,self.num_kernels,M.size(1)//self.num_kernels)
        out=[]
        for i in range(M.size(0)):
            out.append(torch.sum(torch.abs(M[i]-M), dim=2))

        out=torch.stack(out,dim=0)
        out=torch.exp(-out)
        out_sum=torch.sum(out,dim=1)-1
        return torch.cat([x,out_sum],dim=1)


class Discriminator(nn.Module):
    def __init__(self):
        super(Discriminator,self).__init__()

        self.main=nn.Sequential(
            nn.Conv2d(6,64,4,2,1,bias=False),
            nn.LeakyReLU(0.2,inplace=True),
            nn.Conv2d(64,128,4,2,1,bias=False),
            nn.BatchNorm2d(128),
            nn.LeakyReLU(0.2,inplace=True),
            nn.Conv2d(128,256,4,2,1,bias=False),
            nn.BatchNorm2d(256),
            nn.LeakyReLU(0.2,inplace=True)
        )
        self.fc=nn.Linear(256*8*8,512)
        self.minibatch_discriminator=MinibatchDiscrimination(512,512,num_kernels=100,kernel_dim=5)
        self.final_layer=nn.Sequential(
            nn.Linear(512+100,1),
            nn.Sigmoid()
        )

    def forward(self,sketch,image):
        combined_input=torch.cat([sketch,image],dim=1)
        x=self.main(combined_input)
        x=x.view(x.size(0),-1)
        x=self.fc(x)
        x=self.minibatch_discriminator(x)
        return self.final_layer(x).view(-1)

    def get_features(self,sketch,image):
        combined_input=torch.cat([sketch,image],dim=1)
        x=self.main(combined_input)
        return x.view(x.size(0),-1)

# Training Loop
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# Initialize generator and discriminator
netG = Generator().to(device)
netD = Discriminator().to(device)

# Loss and optimizer
criterion = nn.BCELoss()
optimizerD = optim.Adam(netD.parameters(), lr=0.0001, betas=(0.5, 0.999))
optimizerG = optim.Adam(netG.parameters(), lr=0.00005, betas=(0.5, 0.999))

# Fixed set of sketches for validation
fixed_sketches, _ = next(iter(val_loader))
fixed_sketches = fixed_sketches[:64].to(device)

# Save fixed sketches (updated path)
vutils.save_image(fixed_sketches, '/kaggle/working/sketches.png', normalize=True)

fixed_noise = torch.randn(64, 100, 1, 1, device=device)

epochs = 30
real_label = 1.0
fake_label = 0.0

# Initialize best loss for model saving
best_lossG = float('inf')

for epoch in range(epochs):
    netG.train()
    netD.train()
    for i, data in enumerate(tqdm(train_loader)):
        sketches, real_images = data
        sketches, real_images = sketches.to(device), real_images.to(device)
        b_size = real_images.size(0)

        # Label smoothing for discriminator
        real_label_tensor = torch.full((b_size,), 0.9, dtype=torch.float, device=device)
        fake_label_tensor = torch.full((b_size,), 0.1, dtype=torch.float, device=device)

        # Train Discriminator
        netD.zero_grad()
        output_real = netD(sketches, real_images).view(-1)
        lossD_real = criterion(output_real, real_label_tensor)
        lossD_real.backward()

        # Generate fake images
        noise = torch.randn(b_size, 100, 1, 1, device=device)
        fake_images = netG(noise, sketches)

        # Train with fake images
        output_fake = netD(sketches, fake_images.detach()).view(-1)
        lossD_fake = criterion(output_fake, fake_label_tensor)
        lossD_fake.backward()
        optimizerD.step()

        # Train Generator
        netG.zero_grad()
        output_gen = netD(sketches, fake_images).view(-1)
        lossG = criterion(output_gen, real_label_tensor)

        # Feature matching loss
        real_features = netD.get_features(sketches, real_images)
        fake_features = netD.get_features(sketches, fake_images)
        feature_matching_loss = torch.mean(torch.abs(real_features - fake_features))

        total_lossG = lossG + 0.1 * feature_matching_loss
        total_lossG.backward()
        optimizerG.step()

    print(f'Epoch [{epoch+1}/{epochs}] Loss_D: {(lossD_real + lossD_fake).item():.4f}, Loss_G: {total_lossG.item():.4f}')

    # Save model if Generator improves
    if total_lossG.item() < best_lossG:
        best_lossG = total_lossG.item()
        torch.save(netG.state_dict(), f'/kaggle/working/best_generator_epoch_{epoch+1}_loss_{best_lossG:.4f}.pth')
        torch.save(netD.state_dict(), f'/kaggle/working/best_discriminator_epoch_{epoch+1}.pth')
        print(f"Model saved at Epoch {epoch+1} with Generator Loss: {best_lossG:.4f}")

    # Save and display generated images every 3 epochs
    if (epoch + 1) % 3 == 0:
        with torch.no_grad():
            fake = netG(fixed_noise, fixed_sketches)
            img_path = f'/kaggle/working/fake_epoch_{epoch+1}.png'
            vutils.save_image(fake, img_path, normalize=True)

            # Display images
            grid_img = vutils.make_grid(fake, normalize=True).cpu().permute(1, 2, 0).numpy()
            plt.figure(figsize=(8, 8))
            plt.imshow(grid_img)
            plt.axis('off')
            plt.title(f'Generated Images at Epoch {epoch+1}')
            plt.show()









