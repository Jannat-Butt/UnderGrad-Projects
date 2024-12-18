import pytest
from app import app

@pytest.fixture
def client():
    app.config['TESTING'] = True
    with app.test_client() as client:
        yield client

def test_predict(client):
    # Define the form data to send with the POST request
    form_data = {
        'area': '1200',
        'bedrooms': '3',
        'bathrooms': '2',
        'stories': '2',
        'parking': '1',
        'mainroad': 'yes',
        'guestroom': 'no',
        'basement': 'no',
        'hotwaterheating': 'yes',
        'airconditioning': 'yes',
        'prefarea': 'yes',
        'furnishingstatus': 'semi-furnished'  # This will be converted to multiple features
    }

    # Send a POST request to the /predict endpoint
    response = client.post('/predict', data=form_data)

    # Assert that the response is successful (status code 200)
    assert response.status_code == 200

    # Assert that the response contains the prediction value
    assert b'Prediction' in response.data

    # Print the response data for debugging if necessary
    print(response.data.decode('utf-8'))
