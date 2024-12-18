def test_predict_missing_form_data(client):
    form_data = {
        'area': '1200',
        'bedrooms': '3',
        'bathrooms': '2',
        'stories': '2',
        'parking': '1',
        # Missing 'mainroad', 'guestroom', 'basement', 'hotwaterheating', 'airconditioning', 'prefarea', and 'furnishingstatus'
    }
    
    response = client.post('/predict', data=form_data)
    
    # Check if the response contains an error message
    assert response.status_code == 400
    assert b'Error: Missing required fields' in response.data

    print(response.data.decode('utf-8'))
