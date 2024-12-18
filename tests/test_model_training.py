import pytest
import pandas as pd
import numpy as np
# Adjust import based on the actual script name
from train_model import LinearRegression, train_test_split  


def create_sample_data():
    data = {
        'area': [1200, 1500, 1800],
        'bedrooms': [3, 4, 3],
        'bathrooms': [2, 3, 2],
        'stories': [2, 2, 3],
        'parking': [1, 2, 1],
        'mainroad': [1, 0, 1],
        'guestroom': [0, 1, 0],
        'basement': [0, 1, 0],
        'hotwaterheating': [1, 1, 0],
        'airconditioning': [1, 1, 0],
        'prefarea': [1, 0, 1],
        'furnishingstatus': ['semi-furnished', 'unfurnished', 'semi-furnished'],
        'price': [500000, 600000, 550000]
    }
    df = pd.DataFrame(data)
    return df

def test_linear_regression_training():
    df = create_sample_data()

    # Handle missing values (even though we have no missing values in the sample)
    df.fillna(df.mean(numeric_only=True), inplace=True)

    # One-hot encoding
    categorical_features = ['mainroad', 'guestroom', 'basement', 'hotwaterheating', 'airconditioning', 'prefarea', 'furnishingstatus']
    df = pd.get_dummies(df, columns=categorical_features, drop_first=True)

    X = df.drop('price', axis=1)
    y = df['price']

    # Feature scaling
    def manual_standardize(X):
        mean = X.mean(axis=0)
        std = X.std(axis=0)
        return (X - mean) / std

    X_scaled = manual_standardize(X)
    y_mean = y.mean()
    y_std = y.std()
    y_scaled = (y - y_mean) / y_std

    # Train-test split
    X_train, X_test, y_train, y_test = train_test_split(X_scaled.values, y_scaled.values)

    # Initialize and train the model
    model = LinearRegression(learning_rate=0.01, epochs=100)
    model.fit(X_train, y_train)

    # Evaluate the model
    mse, r2 = model.score(X_test, y_test)

    # Check if training and scoring did not produce errors
    assert isinstance(model.theta, np.ndarray), "Model parameters (theta) should be an ndarray."
    assert mse >= 0, "Mean Squared Error should be non-negative."
    assert -1 <= r2 <= 1, "R-squared should be between -1 and 1."

    print(f"Mean Squared Error: {mse:.2f}")
    print(f"R-squared: {r2:.2f}")
