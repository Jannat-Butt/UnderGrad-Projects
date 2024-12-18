from flask import Flask, render_template, request, jsonify
import pandas as pd
import numpy as np
import pickle

# Load model parameters
with open('model_params.pkl', 'rb') as f:
    model_params = pickle.load(f)

theta = model_params['theta']
mean_X = model_params['mean_X']
std_X = model_params['std_X']
mean_y = model_params['mean_y']
std_y = model_params['std_y']
model_features = model_params['model_features']

def manual_standardize(X, mean, std):
    return (X - mean) / std

def preprocess_data(input_data):
    X_scaled = manual_standardize(input_data, mean_X, std_X)
    return X_scaled

def model_predict(features):
    if features.shape[0] != len(theta):
        raise ValueError(f"Feature mismatch: Expected {len(theta)} features, got {features.shape[0]}")
    prediction = features.dot(theta) * std_y + mean_y
    return np.array([prediction])

app = Flask(__name__)

@app.route('/')
def home():
    return render_template("frontend.html")

@app.route("/predict", methods=['POST'])
def predict():
    required_fields = ['area', 'bedrooms', 'bathrooms', 'stories', 'parking',
                       'mainroad', 'guestroom', 'basement', 'hotwaterheating',
                       'airconditioning', 'prefarea', 'furnishingstatus']
    
    missing_fields = [field for field in required_fields if field not in request.form]
    
    if missing_fields:
        return jsonify({"error": f"Missing required fields: {', '.join(missing_fields)}"}), 400

    try:
        area = float(request.form['area'])
        bedrooms = int(request.form['bedrooms'])
        bathrooms = int(request.form['bathrooms'])
        stories = int(request.form['stories'])
        parking = int(request.form['parking'])

        def convert_to_numeric(value):
            return 1 if value in ['yes', '1'] else 0

        mainroad = convert_to_numeric(request.form['mainroad'])
        guestroom = convert_to_numeric(request.form['guestroom'])
        basement = convert_to_numeric(request.form['basement'])
        hotwaterheating = convert_to_numeric(request.form['hotwaterheating'])
        airconditioning = convert_to_numeric(request.form['airconditioning'])
        prefarea = convert_to_numeric(request.form['prefarea'])
        
        furnishingstatus = request.form['furnishingstatus']
        
        input_dict = {
            'area': [area],
            'bedrooms': [bedrooms],
            'bathrooms': [bathrooms],
            'stories': [stories],
            'parking': [parking],
            'mainroad_yes': [mainroad],
            'guestroom_yes': [guestroom],
            'basement_yes': [basement],
            'hotwaterheating_yes': [hotwaterheating],
            'airconditioning_yes': [airconditioning],
            'prefarea_yes': [prefarea],
            'furnishingstatus_semi-furnished': [1 if furnishingstatus == 'semi-furnished' else 0],
            'furnishingstatus_unfurnished': [1 if furnishingstatus == 'unfurnished' else 0]
        }
        
        input_df = pd.DataFrame(input_dict)
        
        for feature in model_features:
            if feature not in input_df.columns:
                input_df[feature] = 0
        
        input_df = input_df[model_features]
        
        features = input_df.values.flatten()
        
        features_scaled = preprocess_data(features)
        
        pred = model_predict(features_scaled)
        
        if isinstance(pred, np.ndarray) and pred.size > 0:
            return render_template("after.html", prediction=pred[0])
        else:
            return "Prediction error: Result is not an array."
    except Exception as e:
        return jsonify({"error": str(e)}), 400

if __name__ == "__main__":
    app.run(debug=True)
