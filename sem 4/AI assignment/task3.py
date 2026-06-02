import numpy as np
import matplotlib.pyplot as plt

def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-z))

def sigmoid_deriv(z):
    s = sigmoid(z)
    return s * (1 - s)

X = np.array([[0, 0],
              [0, 1],
              [1, 0],
              [1, 1]], dtype=float)          # shape (4, 2)

y = np.array([[0],
              [1],
              [1],
              [0]], dtype=float)             # shape (4, 1)


n_input, n_hidden, n_output = 2, 4, 1

W1 = np.random.randn(n_input,  n_hidden) * 0.5     # (2, 4)
b1 = np.zeros((1, n_hidden))                       # (1, 4)
W2 = np.random.randn(n_hidden, n_output) * 0.5     # (4, 1)
b2 = np.zeros((1, n_output))                       # (1, 1)

lr     = 0.5
epochs = 10_000
losses = []

for epoch in range(1, epochs + 1):

    Z1   = X @ W1 + b1          # (4, 4)
    A1   = sigmoid(Z1)          # (4, 4)

    Z2   = A1 @ W2 + b2         # (4, 1)
    A2   = sigmoid(Z2)          # (4, 1)  — final output

    loss = np.mean((y - A2) ** 2)
    losses.append(loss)

    dL_dA2  = -2 * (y - A2) / y.shape[0]            # (4, 1)
    dA2_dZ2 = sigmoid_deriv(Z2)                     # (4, 1)
    delta2   = dL_dA2 * dA2_dZ2                     # (4, 1)

    dW2 = A1.T @ delta2                             # (4, 1)
    db2 = np.sum(delta2, axis=0, keepdims=True)     # (1, 1)

    # Hidden layer delta
    dA1_dZ1 = sigmoid_deriv(Z1)                     # (4, 4)
    delta1   = (delta2 @ W2.T) * dA1_dZ1            # (4, 4)

    dW1 = X.T @ delta1                              # (2, 4)
    db1 = np.sum(delta1, axis=0, keepdims=True)     # (1, 4)

    #  Gradient descent 
    W2 -= lr * dW2
    b2 -= lr * db2
    W1 -= lr * dW1
    b1 -= lr * db1

print("=" * 50)
print("AI202 Assignment 03 — Q4: MLP for XOR")
print("=" * 50)
print(f"\nFinal training loss (MSE): {losses[-1]:.6f}\n")
print("Predicted outputs after training:")
print(f"{'Input':<12} {'Predicted':>12} {'Target':>10} {'Rounded':>10}")
print("-" * 48)

Z1_test = X @ W1 + b1
A1_test = sigmoid(Z1_test)
Z2_test = A1_test @ W2 + b2
A2_test = sigmoid(Z2_test)

for i in range(4):
    inp     = X[i]
    pred    = A2_test[i, 0]
    target  = int(y[i, 0])
    rounded = int(round(pred))
    print(f"({int(inp[0])}, {int(inp[1])})       {pred:>12.6f} {target:>10}  {rounded:>9}")

fig, axes = plt.subplots(1, 2, figsize=(13, 5))

axes[0].plot(range(1, epochs + 1), losses, color='steelblue', linewidth=1.5)
axes[0].set_xlabel("Epoch", fontsize=12)
axes[0].set_ylabel("MSE Loss", fontsize=12)
axes[0].set_title("Training Loss vs Epoch", fontsize=13, fontweight='bold')
axes[0].grid(True, linestyle='--', alpha=0.5)
axes[0].set_yscale('log')

resolution = 300
xs = np.linspace(-0.2, 1.2, resolution)
ys = np.linspace(-0.2, 1.2, resolution)
xx, yy = np.meshgrid(xs, ys)
grid = np.c_[xx.ravel(), yy.ravel()]

Z1g  = grid @ W1 + b1
A1g  = sigmoid(Z1g)
Z2g  = A1g @ W2 + b2
A2g  = sigmoid(Z2g).reshape(resolution, resolution)

axes[1].contourf(xx, yy, A2g, levels=50, cmap='RdYlBu_r', alpha=0.85)
axes[1].contour(xx, yy, A2g, levels=[0.5], colors='black', linewidths=2)

colors = ['#1a6faf', '#d62728']
labels = ['Class 0', 'Class 1']
for cls in range(2):
    idx = (y.ravel() == cls)
    axes[1].scatter(X[idx, 0], X[idx, 1],
                    c=colors[cls], edgecolors='white',
                    s=200, zorder=5, label=labels[cls])

axes[1].set_xlabel("x\u2081", fontsize=12)
axes[1].set_ylabel("x\u2082", fontsize=12)
axes[1].set_title("Decision Boundary (XOR)", fontsize=13, fontweight='bold')
axes[1].legend(fontsize=11)
axes[1].grid(True, linestyle='--', alpha=0.3)

plt.tight_layout()
plt.savefig("mlp_xor.png", dpi=150)
print("\nPlot saved as 'mlp_xor.png'")
plt.show()