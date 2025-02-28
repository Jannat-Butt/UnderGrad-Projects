import PIL
from PIL import Image
import numpy as np
import torch
import torchvision.utils as vutils
from generator import Generator
import io

# Load Model
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
netG = Generator().to(device)
netG.load_state_dict(torch.load("best_generator.pth", map_location=device))
netG.eval()

def generate_image(sketch):
    """
    Generate an image using the trained model given a sketch image.
    """
    # Convert sketch to RGB (if not already)
    sketch = sketch.convert("RGB")  # Ensure it's 3 channels (RGB)
    sketch = np.array(sketch)  # Convert to numpy array
    sketch = torch.from_numpy(sketch).float().unsqueeze(0) / 255.0  # Normalize and add batch dimension

    # Ensure the sketch tensor has the correct shape [1, 3, H, W]
    sketch = sketch.permute(0, 3, 1, 2)  # Change shape from [1, H, W, 3] to [1, 3, H, W]
    print(f"Sketch shape after permute: {sketch.shape}")

    # Ensure the sketch is on the same device as the model
    sketch = sketch.to(device)

    # Resize the sketch to the same spatial size expected by the generator
    sketch = torch.nn.functional.interpolate(sketch, size=(4, 4), mode='bilinear', align_corners=False)
    print(f"Sketch shape after resizing: {sketch.shape}")

    # Pool the sketch to [1, 3, 1, 1]
    sketch_pooled = torch.nn.functional.adaptive_avg_pool2d(sketch, (1, 1))
    print(f"Sketch pooled shape: {sketch_pooled.shape}")

    # Generate Noise (100 channels) – match the spatial size of sketch after pooling
    noise = torch.randn(1, 100, 1, 1, device=device)  # Match spatial size to the generator's expected input
    print(f"Noise shape: {noise.shape}")
    print(f"Noise contents: {noise}")

    # Ensure the combined input has the correct number of channels
    expected_channels = 103  # 100 (noise) + 3 (sketch)

    # Check if the noise tensor is empty
    if noise.numel() == 0:
        print("Error: Noise tensor is empty!")
        return None  # Or handle the error appropriately

    # Ensure sketch_pooled is on the same device as noise
    sketch_pooled = sketch_pooled.to(device)

    # Concatenate the noise and pooled sketch
    combined_input = torch.cat([noise, sketch_pooled], dim=1)
    print(f"Combined input shape: {combined_input.shape}")

    # Pass both noise and sketch separately to the generator
    with torch.no_grad():
        fake_image = netG(noise, sketch_pooled)  # Pass noise and sketch separately

    # Convert to PIL Image
    fake_image = fake_image.cpu().squeeze(0).detach()
    image_buffer = io.BytesIO()
    vutils.save_image(fake_image, image_buffer, format="PNG", normalize=True)
    image_buffer.seek(0)

    return image_buffer