import pandas as pd
import os
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
import tensorflow as tf
from tensorflow.keras.layers import Input, Embedding, Dot, Flatten, Dense
from tensorflow.keras.models import Model
import pickle

# Load the dataset
file_path = r"ratings.csv"
if not os.path.exists(file_path):
    raise FileNotFoundError(f"File not found at {file_path}. Please check the path.")

ratings = pd.read_csv(file_path)

# Encode userId and movieId
user_encoder = LabelEncoder()
ratings['user'] = user_encoder.fit_transform(ratings['userId'])

movie_encoder = LabelEncoder()
ratings['movie'] = movie_encoder.fit_transform(ratings['movieId'])

# Save encoders for later use
with open('user_encoder.pkl', 'wb') as file:
    pickle.dump(user_encoder, file)
with open('movie_encoder.pkl', 'wb') as file:
    pickle.dump(movie_encoder, file)

# Split dataset into training and testing sets
train, test = train_test_split(ratings, test_size=0.2, random_state=42)

train_users = train['user'].values
train_movies = train['movie'].values
train_ratings = train['rating'].values

test_users = test['user'].values
test_movies = test['movie'].values
test_ratings = test['rating'].values

# Define constants
num_users = ratings['user'].nunique()
num_movies = ratings['movie'].nunique()
embedding_size = 50

# Build the model
user_input = Input(shape=(1,), name='user_input')
user_embedding = Embedding(num_users, embedding_size, name='user_embedding')(user_input)

movie_input = Input(shape=(1,), name='movie_input')
movie_embedding = Embedding(num_movies, embedding_size, name='movie_embedding')(movie_input)

dot_product = Dot(axes=1)([user_embedding, movie_embedding])
dot_product = Flatten()(dot_product)

output = Dense(1, activation='linear', name='output')(dot_product)

model = Model(inputs=[user_input, movie_input], outputs=output)
model.compile(optimizer='adam', loss='mse', metrics=['mae'])

# Train the model
history = model.fit(
    [train_users, train_movies],
    train_ratings,
    validation_data=([test_users, test_movies], test_ratings),
    epochs=5,  # Reduced for simplicity
    batch_size=64
)

# Save the trained model
model.save('recommender_model.h5')
print("\nModel training complete and saved as recommender_model.h5")

# Load model and encoders
model = tf.keras.models.load_model('recommender_model.h5')
with open('user_encoder.pkl', 'rb') as file:
    user_encoder = pickle.load(file)
with open('movie_encoder.pkl', 'rb') as file:
    movie_encoder = pickle.load(file)

# Function to predict rating for a given user and movie
def predict_rating(user_id, movie_name, user_rating=None):
    try:
        movie_id = movie_encoder.transform([movie_name])[0]
    except ValueError:
        print(f"Movie '{movie_name}' not found in the dataset!")
        return

    user_encoded = user_encoder.transform([user_id])[0]
    predicted_rating = model.predict([[user_encoded], [movie_id]])[0][0]

    actual_movie_ratings = ratings[ratings['movie'] == movie_id]['rating']
    actual_avg_rating = actual_movie_ratings.mean()

    print(f"\n--- Movie: {movie_name} ---")
    print(f"Predicted Rating: {predicted_rating:.2f}")
    print(f"Average Actual Rating: {actual_avg_rating:.2f}")
    if user_rating is not None:
        print(f"Your Rating: {user_rating}")

# Recommend top N movies for a user
def recommend_movies(user_id, top_n=5):
    user_encoded = user_encoder.transform([user_id])[0]
    all_movie_ids = range(num_movies)
    predicted_ratings = model.predict([[user_encoded] * num_movies, list(all_movie_ids)]).flatten()

    top_movie_indices = predicted_ratings.argsort()[-top_n:][::-1]
    top_movies = movie_encoder.inverse_transform(top_movie_indices)

    print(f"\n--- Recommendations for User {user_id} ---")
    for i, movie in enumerate(top_movies, start=1):
        print(f"{i}. {movie} - Predicted Rating: {predicted_ratings[top_movie_indices[i-1]]:.2f}")

# Interactive session
def interactive_session():
    print("Welcome to the Movie Recommender System!")

    while True:
        user_id = input("\nEnter your user ID (or type 'exit' to quit): ")
        if user_id.lower() == 'exit':
            break

        movie_name = input("Enter the movie name: ")
        user_rating = input("Enter your rating for the movie (optional): ")
        user_rating = float(user_rating) if user_rating else None

        predict_rating(user_id, movie_name, user_rating)

        recommend = input("Would you like recommendations? (yes/no): ")
        if recommend.lower() == 'yes':
            recommend_movies(user_id)

    print("Thank you for using the recommender system!")

if __name__ == "__main__":
    interactive_session()
