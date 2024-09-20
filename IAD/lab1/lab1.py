import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA

data = np.loadtxt('seeds_dataset.txt')

X = data[:, :-1]
y = data[:, -1]
X_mean = np.mean(X, axis=0)
X_std = np.std(X, axis=0)
X_normalized = (X - X_mean) / X_std

cov_matrix = np.cov(X_normalized.T)

eigenvalues, eigenvectors = np.linalg.eig(cov_matrix)

sorted_indices = np.argsort(eigenvalues)[::-1]
eigenvalues = eigenvalues[sorted_indices]
eigenvectors = eigenvectors[:, sorted_indices]

X_pca_manual_2D = X_normalized @ eigenvectors[:, :2]
X_pca_manual_3D = X_normalized @ eigenvectors[:, :3]

pca = PCA(n_components=3)
X_pca_sklearn = pca.fit_transform(X_normalized)

plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.scatter(X_pca_manual_2D[:, 0], X_pca_manual_2D[:, 1], c=y, cmap='viridis')
plt.title('PCA (Manual) 2D')
plt.colorbar()

plt.subplot(1, 2, 2)
plt.scatter(X_pca_sklearn[:, 0], X_pca_sklearn[:, 1], c=y, cmap='viridis')
plt.title('PCA (sklearn) 2D')
plt.colorbar()

plt.show()

total_variance = np.sum(eigenvalues)
explained_variance_2D = np.sum(eigenvalues[:2]) / total_variance
explained_variance_3D = np.sum(eigenvalues[:3]) / total_variance

loss_2D = 1 - explained_variance_2D
loss_3D = 1 - explained_variance_3D

print(f'Потери для проекции на 2 компоненты: {loss_2D * 100:.2f}%')
print(f'Потери для проекции на 3 компоненты: {loss_3D * 100:.2f}%')
