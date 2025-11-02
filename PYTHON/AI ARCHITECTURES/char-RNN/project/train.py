import torch
import torch.nn as nn
import torch.optim as optim

# -------------------------
# 1. Load your dataset
# -------------------------
with open("data/input.txt", "r", encoding="utf-8") as f:
    text = f.read()

# Create char vocabulary
chars = sorted(list(set(text)))
vocab_size = len(chars)
stoi = {ch: i for i, ch in enumerate(chars)}
itos = {i: ch for i, ch in enumerate(chars)}

def encode(s):
    return [stoi[c] for c in s]

def decode(l):
    return "".join([itos[i] for i in l])

# Encode entire dataset
data = torch.tensor(encode(text), dtype=torch.long)

# -------------------------
# 2. Prepare training data
# -------------------------
seq_length = 50  # length of training sequence
batch_size = 64

def get_batch():
    ix = torch.randint(len(data) - seq_length - 1, (batch_size,))
    x = torch.stack([data[i:i+seq_length] for i in ix])
    y = torch.stack([data[i+1:i+seq_length+1] for i in ix])
    return x, y

# -------------------------
# 3. Define Char-RNN model
# -------------------------
class CharRNN(nn.Module):
    def __init__(self, vocab_size, hidden_size, num_layers=2):
        super(CharRNN, self).__init__()
        self.embed = nn.Embedding(vocab_size, hidden_size)
        self.rnn = nn.LSTM(hidden_size, hidden_size, num_layers, batch_first=True)
        self.fc = nn.Linear(hidden_size, vocab_size)

    def forward(self, x, hidden=None):
        x = self.embed(x)
        out, hidden = self.rnn(x, hidden)
        out = self.fc(out)
        return out, hidden

# -------------------------
# 4. Train
# -------------------------
device = "cuda" if torch.cuda.is_available() else "cpu"
model = CharRNN(vocab_size, hidden_size=256).to(device)
optimizer = optim.Adam(model.parameters(), lr=0.002)
criterion = nn.CrossEntropyLoss()

epochs = 50
for epoch in range(epochs):
    x, y = get_batch()
    x, y = x.to(device), y.to(device)

    optimizer.zero_grad()
    out, _ = model(x)
    loss = criterion(out.view(-1, vocab_size), y.view(-1))
    loss.backward()
    optimizer.step()

    if (epoch+1) % 5 == 0:
        print(f"Epoch {epoch+1}/{epochs}, Loss: {loss.item():.4f}")

# -------------------------
# 5. Save model + vocab
# -------------------------
torch.save({
    "model_state": model.state_dict(),
    "stoi": stoi,
    "itos": itos
}, "models/char_rnn.pth")
