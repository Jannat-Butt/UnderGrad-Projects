from flask import Flask, request, render_template, send_file
from model import generate_image
import PIL
from PIL import Image

from werkzeug.utils import secure_filename
import os

app = Flask(__name__)

# Set Upload Folder
UPLOAD_FOLDER = "static/uploads"
OUTPUT_FOLDER = "static/generated"
os.makedirs(UPLOAD_FOLDER, exist_ok=True)
os.makedirs(OUTPUT_FOLDER, exist_ok=True)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # Get uploaded sketch
        if "file" not in request.files:
            return "No file uploaded", 400
        file = request.files["file"]
        if file.filename == "":
            return "No selected file", 400
        
        # Save Sketch
        filename = secure_filename(file.filename)
        filepath = os.path.join(UPLOAD_FOLDER, filename)
        file.save(filepath)

        # Generate Image
        with open(filepath, "rb") as f:
            image_buffer = generate_image(Image.open(f))

        # Save generated image
        output_path = os.path.join(OUTPUT_FOLDER, f"generated_{filename}")
        with open(output_path, "wb") as f:
            f.write(image_buffer.getbuffer())

        return render_template("index.html", sketch_path=filepath, gen_path=output_path)

    return render_template("index.html", sketch_path=None, gen_path=None)

if __name__ == "__main__":
    app.run(debug=True)
