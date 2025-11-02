import pandas as pd
import os
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
import tensorflow as tf
from tensorflow.keras.layers import Input, Embedding, Dot, Flatten, Dense
from tensorflow.keras.models import Model
import matplotlib.pyplot as plt

# Load the dataset
file_path = r"C:\Users\HP\Desktop\C++\python\ratings.csv"
if not os.path.exists(file_path):
    # Check if the dataset file exists, and raise an error if not
    raise FileNotFoundError(f"File not found at {file_path}. Please check the path.")

ratings = pd.read_csv(file_path)  # Load the CSV file into a DataFrame

# Display basic dataset information
print("Dataset Head:")
print(ratings.head())  # Show the first few rows of the dataset
print("\nDataset Info:")
print(ratings.info())  # Display dataset structure and types
print("\nSummary Statistics:")
print(ratings.describe())  # Show summary statistics for numerical columns

# Check for missing values
if ratings.isnull().sum().any():
    # Warn if there are missing values in the dataset
    print("\nWarning: Dataset contains missing values. Please handle them before proceeding.")
else:
    print("\nNo missing values detected.")

# Encode userId and movieId
user_encoder = LabelEncoder()
ratings['user'] = user_encoder.fit_transform(ratings['userId'])  # Encode userId as integers

movie_encoder = LabelEncoder()
ratings['movie'] = movie_encoder.fit_transform(ratings['movieId'])  # Encode movieId as integers

print("\nEncoded Dataset Head:")
print(ratings.head())  # Show the first few rows of the encoded dataset

# Split dataset into training and testing sets
train, test = train_test_split(ratings, test_size=0.2, random_state=42)  # Use 80/20 split

print(f"\nTrain size: {len(train)}, Test size: {len(test)}")

# Extract user, movie, and rating data for training and testing
train_users = train['user'].values
train_movies = train['movie'].values
train_ratings = train['rating'].values

test_users = test['user'].values
test_movies = test['movie'].values
test_ratings = test['rating'].values

# Define constants
num_users = ratings['user'].nunique()  # Number of unique users
num_movies = ratings['movie'].nunique()  # Number of unique movies
embedding_size = 50  # Size of the dense embedding vectors

# Build the model
user_input = Input(shape=(1,), name='user_input')  # Input for user IDs
user_embedding = Embedding(num_users, embedding_size, name='user_embedding')(user_input)  # User embedding layer

movie_input = Input(shape=(1,), name='movie_input')  # Input for movie IDs
movie_embedding = Embedding(num_movies, embedding_size, name='movie_embedding')(movie_input)  # Movie embedding layer

# Dot product of user and movie embeddings
dot_product = Dot(axes=1)([user_embedding, movie_embedding])  # Compute dot product

dot_product = Flatten()(dot_product)  # Flatten the result to feed into the output layer

# Output layer
output = Dense(1, activation='linear', name='output')(dot_product)  # Predict the rating

# Compile the model
model = Model(inputs=[user_input, movie_input], outputs=output)
model.compile(optimizer='adam', loss='mse', metrics=['mae'])  # Use Adam optimizer and MSE loss

print("\nModel Summary:")
model.summary()  # Print the model architecture

# Train the model
history = model.fit(
    [train_users, train_movies],  # Inputs: user and movie IDs
    train_ratings,  # Targets: actual ratings
    validation_data=([test_users, test_movies], test_ratings),  # Validation data
    epochs=20,  # Number of epochs
    batch_size=64  # Batch size
)

# Evaluate the model
loss, mae = model.evaluate([test_users, test_movies], test_ratings)  # Evaluate on test set
print(f"\nTest Loss: {loss}, Test MAE: {mae}")

# Plot training history
plt.figure(figsize=(12, 6))
plt.plot(history.history['loss'], label='Training Loss')
plt.plot(history.history['val_loss'], label='Validation Loss')
plt.title('Model Loss Over Epochs')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()  # Show the loss plot

plt.figure(figsize=(12, 6))
plt.plot(history.history['mae'], label='Training MAE')
plt.plot(history.history['val_mae'], label='Validation MAE')
plt.title('Model MAE Over Epochs')
plt.xlabel('Epochs')
plt.ylabel('Mean Absolute Error (MAE)')
plt.legend()
plt.show()  # Show the MAE plot

# Predict ratings
predictions = model.predict([test_users, test_movies])  # Generate predictions for test set
print("\nFirst 5 Predictions:")
for i in range(5):
    # Display the first 5 predictions along with actual ratings
    print(f"User: {user_encoder.inverse_transform([test_users[i]])[0]}, \
          Movie: {movie_encoder.inverse_transform([test_movies[i]])[0]}, \
          Predicted Rating: {predictions[i][0]:.2f}, \
          Actual Rating: {test_ratings[i]}")

# Save the model
model_save_path = r"C:\Users\HP\Desktop\C++\python\recommender_model.h5"
model.save(model_save_path)  # Save the trained model to the specified path
print(f"\nModel saved to {model_save_path}")
