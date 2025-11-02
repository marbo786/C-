import streamlit as st
from model import LeNet5
import torch
import torch.nn.functional as F
from torchvision import transforms
from streamlit_drawable_canvas import st_canvas
from PIL import Image, ImageOps
import numpy as np

# ------------------------ Setup ------------------------

st.set_page_config(page_title="Digit Classifier", page_icon="✍️", layout="centered")

# Load the model
@st.cache_resource
def load_model():
    model = LeNet5(num_classes=10)
    model.load_state_dict(torch.load("lenet5_mnist.pth", map_location=torch.device("cpu")))
    model.eval()
    return model

model = load_model()

# Image transform
transform = transforms.Compose([
    transforms.Resize((32, 32)),
    transforms.ToTensor(),
    transforms.Normalize((0.1307,), (0.3081,))
])

# ------------------------ Header ------------------------

st.markdown("""
    <h1 style='text-align: center; color: #3c4f65;'>🧠 Digit Classifier</h1>
    <p style='text-align: center; color: #6c757d;'>Built with LeNet-5 on MNIST</p>
    <hr style="border-top: 1px solid #bbb;">
""", unsafe_allow_html=True)

st.markdown("### 📷 Upload or ✍️ Draw a digit below:")

# ------------------------ Upload Section ------------------------

with st.container():
    st.markdown("#### 1. Upload an Image (optional)")
    uploaded_file = st.file_uploader("Choose a grayscale digit image", type=["png", "jpg", "jpeg"], label_visibility="collapsed")
    image = None

    if uploaded_file:
        image = Image.open(uploaded_file).convert("L")
        st.image(image, caption="Uploaded Image", width=150)

# ------------------------ Drawing Section ------------------------

st.markdown("#### 2. Or Draw Below")

canvas_result = st_canvas(
    fill_color="#000000",
    stroke_width=12,
    stroke_color="#FFFFFF",
    background_color="#000000",
    width=280,
    height=280,
    drawing_mode="freedraw",
    key="canvas"
)

if canvas_result.image_data is not None:
    drawn_img = Image.fromarray((canvas_result.image_data[:, :, 0]).astype("uint8"))
    if drawn_img.getbbox():
        image = drawn_img.resize((28, 28))
        st.image(image, caption="Drawn Digit", width=150)

# ------------------------ Prediction Button ------------------------

if image:
    st.markdown("### 🔍 Ready to Predict?")
    if st.button("✨ Predict Digit", use_container_width=True):
        image = ImageOps.expand(image, border=2, fill=0)  # 32x32
        img_tensor = transform(image).unsqueeze(0)

        with torch.no_grad():
            outputs = model(img_tensor)
            probabilities = F.softmax(outputs, dim=1)
            predicted_class = torch.argmax(probabilities).item()
            confidence = torch.max(probabilities).item() * 100

        st.success(f"### 🎯 Predicted Digit: `{predicted_class}` ({confidence:.2f}% confidence)")

# ------------------------ Footer ------------------------

st.markdown("""
<hr>
<p style='text-align: center; font-size: 0.9em; color: #999;'>Built with ❤️ using PyTorch and Streamlit</p>
""", unsafe_allow_html=True)
