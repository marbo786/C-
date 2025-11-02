import pandas as pd

# Load the dataset
ratings = pd.read_csv(r"C:\Users\HP\Desktop\C++\python\ratings.csv")


# Display the first few rows
print(ratings.head())


from sklearn.preprocessing import LabelEncoder

user_encoder = LabelEncoder()
ratings['user'] = user_encoder.fit_transform(ratings['userId'])

movie_encoder = LabelEncoder()
ratings['movie'] = movie_encoder.fit_transform(ratings['movieId'])

print(ratings.head())


from sklearn.model_selection import train_test_split

train, test = train_test_split(ratings, test_size=0.2, random_state=42)

print(f"Train size: {len(train)}, Test size: {len(test)}")

train_users = train['user'].values
train_movies = train['movie'].values
train_ratings = train['rating'].values

test_users = test['user'].values
test_movies = test['movie'].values
test_ratings = test['rating'].values


import tensorflow as tf
from tensorflow.keras.layers import Input, Embedding, Dot, Flatten, Dense
from tensorflow.keras.models import Model

# Define constants
num_users = ratings['user'].nunique()
num_movies = ratings['movie'].nunique()
embedding_size = 50  # Size of the dense embedding vectors

# User and Movie Embedding layers
user_input = Input(shape=(1,), name='user_input')
user_embedding = Embedding(num_users, embedding_size, name='user_embedding')(user_input)

movie_input = Input(shape=(1,), name='movie_input')
movie_embedding = Embedding(num_movies, embedding_size, name='movie_embedding')(movie_input)



# Dot product of user and movie embeddings
dot_product = Dot(axes=2)([user_embedding, movie_embedding])
dot_product = Flatten()(dot_product)

# Output layer
output = Dense(1, activation='linear', name='output')(dot_product)

# Build the model
model = Model(inputs=[user_input, movie_input], outputs=output)
model.compile(optimizer='adam', loss='mse', metrics=['mae'])

model.summary()



history = model.fit(
    [train_users, train_movies], 
     train_ratings, 
     validation_data=([test_users, test_movies], test_ratings), 
    epochs=20, 
     batch_size=64
 )



loss, mae = model.evaluate([test_users, test_movies], test_ratings)
print(f"Test Loss: {loss}, Test MAE: {mae}")




predictions = model.predict([test_users, test_movies])
print(predictions[:5])  # Display the first 5 predictions

