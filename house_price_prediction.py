import pandas as pd
import numpy as np
import pickle

# Load dataset
df = pd.read_csv("Housing.csv")

# Handle missing values
df.fillna(df.mean(numeric_only=True), inplace=True)

# One-hot encoding for categorical variables
categorical_features = ['mainroad', 'guestroom', 'basement', 'hotwaterheating', 'airconditioning', 'prefarea', 'furnishingstatus']
df = pd.get_dummies(df, columns=categorical_features, drop_first=True)

# Prepare features and labels
X = df.drop('price', axis=1)
y = df['price']

# Feature scaling manually
def manual_standardize(X):
    mean = X.mean(axis=0)
    std = X.std(axis=0)
    return (X - mean) / std

X_scaled = manual_standardize(X)

# Standardize y manually
y_mean = y.mean()
y_std = y.std()
y_scaled = (y - y_mean) / y_std

# Train-test split manually
def train_test_split(X, y, test_size=0.2, random_state=42):
    np.random.seed(random_state)
    indices = np.arange(X.shape[0])
    np.random.shuffle(indices)
    split_index = int(X.shape[0] * (1 - test_size))
    train_indices, test_indices = indices[:split_index], indices[split_index:]
    return X[train_indices], X[test_indices], y[train_indices], y[test_indices]

X_train, X_test, y_train, y_test = train_test_split(X_scaled.values, y_scaled.values)

class LinearRegression:
    def __init__(self, learning_rate=0.01, epochs=1000):
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.theta = None

    def fit(self, X, y):
        m, n = X.shape
        self.theta = np.zeros(n)  # No bias term

        for _ in range(self.epochs):
            predictions = X.dot(self.theta)
            errors = predictions - y
            gradient = X.T.dot(errors) / m
            self.theta -= self.learning_rate * gradient

    def predict(self, X):
        return X.dot(self.theta)

    def score(self, X, y):
        predictions = self.predict(X)
        mse = np.mean((predictions - y) ** 2)
        ss_res = np.sum((y - predictions) ** 2)
        ss_tot = np.sum((y - np.mean(y)) ** 2)
        r2 = 1 - (ss_res / ss_tot)
        return mse, r2

# Initialize and train the model
model = LinearRegression(learning_rate=0.01, epochs=1000)
model.fit(X_train, y_train)

# Evaluate the model
mse, r2 = model.score(X_test, y_test)
print(f"Mean Squared Error: {mse:.2f}")
print(f"R-squared: {r2:.2f}")

# Save the model parameters and scalers
# Ensure this captures the final features used in training
model_features = list(X.columns) 
with open('model_params.pkl', 'wb') as f:
    pickle.dump({'theta': model.theta,
                 'mean_X': X.mean(),
                 'std_X': X.std(),
                 'mean_y': y_mean,
                 'std_y': y_std,
                 'model_features': model_features}, f)

print("Training Features Shape:", X_train.shape)
print("Testing Features Shape:", X_test.shape)
print("Model Features Length:", len(model_features))
print("Model Features:", model_features)
