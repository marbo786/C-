import torch
import torch.nn as nn
import torch.nn.functional as F

class SelfAttention(nn.Module):
    def __init__(self, embed_size, heads):
        super(SelfAttention, self).__init__()
        self.embed_size = embed_size
        self.heads = heads
        self.head_dim = embed_size // heads

        assert (
            self.head_dim * heads == embed_size
        ), "Embedding size needs to be divisible by heads"

        self.values = nn.Linear(self.head_dim, self.head_dim, bias=False)
        self.keys = nn.Linear(self.head_dim, self.head_dim, bias=False)
        self.queries = nn.Linear(self.head_dim, self.head_dim, bias=False)
        self.fc_out = nn.Linear(heads * self.head_dim, embed_size)

    def forward(self, value, key, query, mask=None):
        N = query.shape[0]  # Batch size
        value_len, key_len, query_len = value.shape[1], key.shape[1], query.shape[1]

        # Split the embedding into self.heads pieces
        value = value.reshape(N, value_len, self.heads, self.head_dim)
        key = key.reshape(N, key_len, self.heads, self.head_dim)
        query = query.reshape(N, query_len, self.heads, self.head_dim)

        values = self.values(value)
        keys = self.keys(key)
        queries = self.queries(query)

        # Scaled dot-product attention
        # queries shape: (N, query_len, heads, head_dim)
        # keys shape: (N, key_len, heads, head_dim)
        # scores shape: (N, heads, query_len, key_len)
        energy = torch.einsum("nqhd,nkhd->nhqk", [queries, keys])

        if mask is not None:
            energy = energy.masked_fill(mask == 0, float("-1e20")) # Use a large negative number for masking

        attention = F.softmax(energy / (self.embed_size ** (0.5)), dim=-1)

        # attention shape: (N, heads, query_len, key_len)
        # values shape: (N, value_len, heads, head_dim)
        # out shape: (N, query_len, heads, head_dim)
        out = torch.einsum("nhql,nlhd->nqhd", [attention, values]).reshape(
            N, query_len, self.heads * self.head_dim
        )

        out = self.fc_out(out)
        return out

# Example Usage:
if __name__ == "__main__":
    batch_size = 2
    sequence_length = 10
    embed_dim = 256
    num_heads = 8

    # Create dummy input data
    x = torch.randn(batch_size, sequence_length, embed_dim)

    # Instantiate the self-attention module
    self_attn_module = SelfAttention(embed_size=embed_dim, heads=num_heads)

    # Pass the input through the module
    # In self-attention, query, key, and value are the same input
    output = self_attn_module(x, x, x)

    print(f"Input shape: {x.shape}")
    print(f"Output shape: {output.shape}")