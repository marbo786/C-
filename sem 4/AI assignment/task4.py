import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches


n = 200 // 3

cluster1 = np.random.randn(n + 1, 2) * 1.0 + np.array([2, 8])
cluster2 = np.random.randn(n,     2) * 1.0 + np.array([8, 5])
cluster3 = np.random.randn(n,     2) * 1.0 + np.array([5, 1])

X = np.vstack([cluster1, cluster2, cluster3])   


def euclidean(a, b):
    return np.sqrt(np.sum((a - b) ** 2, axis=1))

def kmeans(X, K, max_iter=100, seed=0):
   
    rng = np.random.default_rng(seed)

    idx = rng.choice(len(X), size=K, replace=False)
    centroids = X[idx].copy()

    labels_history    = []
    centroids_history = [centroids.copy()]
    wcss_history      = []

    for _ in range(max_iter):
       
        dists  = np.stack([euclidean(X, c) for c in centroids], axis=1)  # (n, K)
        labels = np.argmin(dists, axis=1)
        labels_history.append(labels.copy())

        wcss = sum(np.sum((X[labels == k] - centroids[k]) ** 2)
                   for k in range(K))
        wcss_history.append(wcss)

        new_centroids = np.array([X[labels == k].mean(axis=0) for k in range(K)])

        if np.allclose(centroids, new_centroids):
            break
        centroids = new_centroids
        centroids_history.append(centroids.copy())

    return labels_history, centroids_history, wcss_history

K = 3
labels_hist, cents_hist, wcss_hist = kmeans(X, K=K, seed=0)
n_iters = len(labels_hist)

print("=" * 55)
print("AI202 Assignment 04 – Q4: K-Means Visualizer")
print("=" * 55)
print(f"\nK=3 converged in {n_iters} iterations.\n")
print(f"{'Iter':>5}  {'WCSS':>12}")
print("-" * 20)
for i, w in enumerate(wcss_hist, 1):
    print(f"{i:>5}  {w:>12.4f}")

COLORS = ['#1f77b4', '#ff7f0e', '#2ca02c']

def scatter_clusters(ax, X, labels, centroids, title):
    for k in range(K):
        mask = labels == k
        ax.scatter(X[mask, 0], X[mask, 1], c=COLORS[k], s=25, alpha=0.7,
                   edgecolors='white', linewidths=0.4)
    for k, c in enumerate(centroids):
        ax.scatter(*c, marker='X', s=250, c=COLORS[k], edgecolors='black',
                   linewidths=1.5, zorder=5)
    ax.set_title(title, fontsize=11, fontweight='bold')
    ax.set_xlabel("x"); ax.set_ylabel("y")
    ax.grid(True, linestyle='--', alpha=0.4)

fig, axes = plt.subplots(2, 2, figsize=(12, 10))
fig.suptitle("K-Means Clustering (K=3)  –  Step-by-Step Snapshots",
             fontsize=14, fontweight='bold')

axes[0, 0].scatter(X[:, 0], X[:, 1], c='steelblue', s=25, alpha=0.6,
                   edgecolors='white', linewidths=0.4)
axes[0, 0].scatter(*cents_hist[0].T, marker='X', s=250, c=COLORS[:K],
                   edgecolors='black', linewidths=1.5, zorder=5)
axes[0, 0].set_title("Initial Data + Starting Centroids", fontsize=11, fontweight='bold')
axes[0, 0].set_xlabel("x"); axes[0, 0].set_ylabel("y")
axes[0, 0].grid(True, linestyle='--', alpha=0.4)

scatter_clusters(axes[0, 1], X, labels_hist[0],
                 cents_hist[min(1, len(cents_hist)-1)], "After Iteration 1")

iter3_idx = min(2, len(labels_hist)-1)
scatter_clusters(axes[1, 0], X, labels_hist[iter3_idx],
                 cents_hist[min(3, len(cents_hist)-1)], f"After Iteration {iter3_idx+1}")

scatter_clusters(axes[1, 1], X, labels_hist[-1], cents_hist[-1],
                 f"Final (Converged – Iter {n_iters})")

patches = [mpatches.Patch(color=COLORS[k], label=f"Cluster {k+1}") for k in range(K)]
fig.legend(handles=patches, loc='lower center', ncol=K, fontsize=10, frameon=True)
plt.tight_layout(rect=[0, 0.04, 1, 1])
plt.savefig("kmeans_snapshots.png", dpi=150)
print("\nSaved: kmeans_snapshots.png")

fig2, ax2 = plt.subplots(figsize=(7, 4))
ax2.plot(range(1, len(wcss_hist)+1), wcss_hist,
         marker='o', color='steelblue', linewidth=2, markersize=7)
ax2.set_xlabel("Iteration", fontsize=12)
ax2.set_ylabel("WCSS (Within-Cluster Sum of Squares)", fontsize=12)
ax2.set_title("WCSS vs Iteration  (K=3)", fontsize=13, fontweight='bold')
ax2.grid(True, linestyle='--', alpha=0.5)
plt.tight_layout()
plt.savefig("kmeans_wcss.png", dpi=150)
print("Saved: kmeans_wcss.png")

K_range = [2, 3, 4, 5]
elbow_wcss = []

print(f"\n{'K':>4}  {'Final WCSS':>14}")
print("-" * 22)
for k in K_range:
    lh, _, wh = kmeans(X, K=k, seed=0)
    final_wcss = wh[-1]
    elbow_wcss.append(final_wcss)
    print(f"{k:>4}  {final_wcss:>14.4f}")

fig3, ax3 = plt.subplots(figsize=(7, 4))
ax3.plot(K_range, elbow_wcss, marker='o', color='darkorange',
         linewidth=2.5, markersize=9)
ax3.set_xlabel("Number of Clusters (K)", fontsize=12)
ax3.set_ylabel("Final WCSS", fontsize=12)
ax3.set_title("Elbow Curve – WCSS vs K", fontsize=13, fontweight='bold')
ax3.set_xticks(K_range)
ax3.grid(True, linestyle='--', alpha=0.5)

ax3.annotate("Elbow at K=3\n(optimal)", xy=(3, elbow_wcss[1]),
             xytext=(3.4, elbow_wcss[1] + (elbow_wcss[0]-elbow_wcss[1])*0.3),
             fontsize=10, color='darkred',
             arrowprops=dict(arrowstyle='->', color='darkred'))

plt.tight_layout()
plt.savefig("kmeans_elbow.png", dpi=150)
print("Saved: kmeans_elbow.png")

print(f"\nOptimal K = 3  (largest WCSS drop occurs between K=2 and K=3; gains diminish after)")
plt.show()