# Human Activity Recognition using Vision Transformer (ViT)

This project implements **Human Activity Recognition (HAR)** using the HMDB dataset. It leverages a pretrained Vision Transformer (ViT) for robust classification of human activities in video data.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Dataset](#dataset)
4. [Setup and Installation](#setup-and-installation)
5. [How to Run](#how-to-run)
6. [What's Done and How](#whats-done-and-how)
7. [Results](#results)
8. [Acknowledgments](#acknowledgments)

---

## Introduction

**Human Activity Recognition (HAR)** is a crucial application in computer vision, useful in areas such as surveillance, healthcare, and robotics. This project uses the HMDB dataset and fine-tunes a pretrained Vision Transformer (ViT) to achieve strong performance in recognizing human activities.

---

## Features
- **Frame Extraction**: Extracts video frames from HMDB dataset videos for preprocessing.
- **Preprocessing**: Frames are resized, normalized, and augmented for model training.
- **ViT Model**: Fine-tuned Vision Transformer model for HAR.
- **Visualization**: Displays correctly classified frames with true and predicted labels.

---

## Dataset

The **HMDB dataset** (Human Motion Database) contains 51 activity classes, including actions like running, eating, and jumping. Each class consists of multiple video samples.

### Dataset Preparation
1. Download the HMDB dataset from its official source.
2. Upload the dataset to Kaggle under "Add Dataset" in your Kaggle notebook environment.
3. Ensure the folder structure is maintained for training and testing.

---

## Setup and Installation

### Prerequisites
- **Python**: Version 3.8 or later.
- **Libraries**:
    - `torch`
    - `transformers`
    - `scikit-learn`
    - `opencv-python`
    - `matplotlib`
    - `pandas`

### Installation

1. Clone this repository:

    git clone https://github.com/JannatButt-mlops/Computer-Vision.git
    
    cd Computer-Vision
        
    git checkout HAR

2. Set up the HMDB dataset on Kaggle:
    - Navigate to "Add Dataset" in your Kaggle notebook environment.
    - Upload the dataset and place it under the directory `data/hmdb`.

---

## How to Run

1. **Step 1: Load the Notebook**  
   Upload the notebook from this repository into your Kaggle kernel.

2. **Step 2: Set the Dataset Path**  
   Define the path for processed frames:
   ```python 
   base_path = '/kaggle/working/preprocessed_frames' 

 

  ## Step 3: Preprocessing
  Run the preprocessing cells to:
  - Extract frames from videos.
  - Resize, normalize, and augment the frames.

  ## Step 4: Training the Model
  Execute the cells to:
  - Load the pretrained Vision Transformer (ViT) model.
  - Fine-tune it on the HMDB dataset using the training data.

  ## Step 5: Evaluation and Visualization
  Run the final inference cell to:
  - Calculate metrics like accuracy, precision, recall, and F1-score.
  - Visualize correctly classified images with true and predicted labels.

  ## What's Done and How

  ### Data Loading and Preparation
  - **What**: Load and preprocess the HMDB dataset for training and evaluation.
  - **How**: Custom function `load_data()` reads images and labels from the dataset directory. Data is split into training and testing sets.

  ### Label Encoding
  - **What**: Convert string labels to numeric format for model training.
  - **How**: `LabelEncoder` from scikit-learn encodes class labels.

  ### ViT Model Initialization
  - **What**: Use a pretrained Vision Transformer model for classification.
  - **How**: Fine-tune `google/vit-base-patch16-224-in21k` from Hugging Face with a modified output layer.

  ### Custom Dataset and DataLoader
  - **What**: Create PyTorch-compatible datasets and dataloaders for batching.
  - **How**: A `CustomDataset` class preprocesses images dynamically and maps them to labels.

  ### Training the Model
  - **What**: Fine-tune the ViT model on the HMDB dataset.
  - **How**: Use cross-entropy loss, AdamW optimizer, and a learning rate scheduler for stable convergence.

  ### Evaluation and Metrics
  - **What**: Evaluate the model's performance on the test set.
  - **How**: Compute metrics like accuracy, precision, recall, and F1-score using `classification_report`.

  ### Visualization
  - **What**: Display correctly classified frames with true and predicted labels.
  - **How**: Use Matplotlib to create visualizations of sample results.

  ## Results
  - **Training Accuracy**: 92%
  - **Validation Accuracy**: 84%
  - **Test Accuracy**: 84%.

  ### Visualization Example
  The notebook includes code to visualize correctly classified samples, displaying both true and predicted labels for selected frames.

  ## Acknowledgments
  This project utilizes:
  - **Hugging Face Transformers**: For the pretrained Vision Transformer (ViT) model.
  - **PyTorch**: For building and training deep learning models.
  - **HMDB Dataset**: Benchmark dataset for human activity recognition task.
  

