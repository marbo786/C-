import streamlit as st
from predict import predict

st.title("🎬 Movie Review Sentiment Analyzer")
st.write("Enter a movie review below and find out if it's Positive or Negative!")

user_input = st.text_area("Your Review:")

if st.button("Analyze"):
    if user_input.strip():
        label, prob = predict(user_input)
        st.write(f"**Prediction:** {label}")
        st.write(f"**Confidence:** {prob:.2f}")
    else:
        st.warning("Please enter some text!")
