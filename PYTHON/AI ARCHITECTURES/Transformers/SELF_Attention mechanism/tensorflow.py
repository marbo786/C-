import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

def create_self_attention_layer(input_dim, num_heads, key_dim):
    """
    Creates a self-attention layer using tf.keras.layers.MultiHeadAttention.

    Args:
        input_dim (int): The dimension of the input features.
        num_heads (int): The number of attention heads.
        key_dim (int): The dimensionality of the key and query vectors.

    Returns:
        tf.keras.layers.Layer: A Keras layer implementing self-attention.
    """
    # MultiHeadAttention is designed for self-attention when query, key, and value
    # are all the same input.
    attention_layer = layers.MultiHeadAttention(
        num_heads=num_heads,
        key_dim=key_dim
    )
    return attention_layer

# Example usage:
# Assume an input sequence with shape (batch_size, sequence_length, embedding_dim)
# For self-attention, the input serves as query, key, and value.
batch_size = 32
sequence_length = 100
embedding_dim = 128
num_heads = 8
key_dim = 64 # Typically key_dim = embedding_dim // num_heads

# Create a dummy input tensor
input_tensor = tf.random.normal((batch_size, sequence_length, embedding_dim))

# Create the self-attention layer
self_attention_layer = create_self_attention_layer(embedding_dim, num_heads, key_dim)

# Apply the self-attention layer
# In self-attention, the query, key, and value are all the same input.
output_tensor = self_attention_layer(query=input_tensor, value=input_tensor, key=input_tensor)

print(f"Input shape: {input_tensor.shape}")
print(f"Output shape: {output_tensor.shape}")