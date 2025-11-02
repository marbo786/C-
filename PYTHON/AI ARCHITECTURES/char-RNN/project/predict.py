import torch
import torch.nn as nn
import pickle
from torchtext.data.utils import get_tokenizer

# ----- Load vocab -----
with open("vocab.pkl", "rb") as f:
    vocab = pickle.load(f)

tokenizer = get_tokenizer("basic_english")
pad_idx = vocab["<pad>"]

def text_pipeline(x):
    return vocab(tokenizer(x))

# ----- Model (must match train.py) -----
class BiLSTMClassifier(nn.Module):
    def __init__(self, vocab_size, embed_dim=100, hidden_dim=128, num_layers=1, bidirectional=True, dropout=0.5, pad_idx=0):
        super().__init__()
        self.embedding = nn.Embedding(vocab_size, embed_dim, padding_idx=pad_idx)
        self.lstm = nn.LSTM(embed_dim, hidden_dim, num_layers=num_layers,
                            batch_first=True, bidirectional=bidirectional, dropout=0 if num_layers==1 else 0.2)
        out_dim = hidden_dim * (2 if bidirectional else 1)
        self.fc = nn.Sequential(
            nn.Dropout(dropout),
            nn.Linear(out_dim, 64),
            nn.ReLU(),
            nn.Dropout(0.3),
            nn.Linear(64, 1)
        )
    
    def forward(self, x):
        emb = self.embedding(x)
        out, _ = self.lstm(emb)
        out = torch.max(out, dim=1)[0]
        return self.fc(out).squeeze(1)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model = BiLSTMClassifier(len(vocab), pad_idx=pad_idx).to(device)
model.load_state_dict(torch.load("bilstm_imdb.pth", map_location=device))
model.eval()

def predict(text):
    seq = torch.tensor([text_pipeline(text)], dtype=torch.long).to(device)
    with torch.no_grad():
        prob = torch.sigmoid(model(seq)).item()
    label = "Positive" if prob >= 0.5 else "Negative"
    return label, prob

# Example
print(predict("The movie was absolutely wonderful and touching!"))
print(predict("I hated every second of it, waste of time."))
