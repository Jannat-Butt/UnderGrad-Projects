import pytest
from app import app  

@pytest.fixture
def client():
    app.config['TESTING'] = True
    with app.test_client() as client:
        yield client

def test_home_page_loads(client):
    response = client.get('/')
    assert response.status_code == 200
    
    # Print the HTML content to understand what is actually being returned
    print(response.data.decode('utf-8'))
    
    # placeholder text with actual content from  homepage
    assert b'House Price Predictor' in response.data 
