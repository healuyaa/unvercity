import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.manifold import TSNE
import tensorflow as tf
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Input, Dense
from tensorflow.keras.optimizers import Adam

data_file = 'dataset/seeds_dataset.txt'

column_names = [
    'area', 'perimeter', 'compactness', 'length_of_kernel',
    'width_of_kernel', 'asymmetry_coefficient', 'length_of_kernel_groove', 'class'
]
data = pd.read_csv(data_file, sep='\s+', header=None, names=column_names)

X = data.iloc[:, :-1].values
y = data.iloc[:, -1].values

scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

X_train, X_test, y_train, y_test = train_test_split(
    X_scaled, y, test_size=0.2, random_state=42, stratify=y
)

def build_autoencoder(input_dim, encoding_dim):
    input_layer = Input(shape=(input_dim,))
    encoded = Dense(8, activation='relu')(input_layer)
    encoded = Dense(encoding_dim, activation='relu')(encoded)
    decoded = Dense(8, activation='relu')(encoded)
    decoded = Dense(input_dim, activation='linear')(decoded)
    
    autoencoder = Model(inputs=input_layer, outputs=decoded)
    encoder = Model(inputs=input_layer, outputs=encoded)
    
    autoencoder.compile(optimizer=Adam(learning_rate=0.001), loss='mse')
    return autoencoder, encoder

input_dim = X_train.shape[1]

autoencoder_2, encoder_2 = build_autoencoder(input_dim, 2)
autoencoder_3, encoder_3 = build_autoencoder(input_dim, 3)

history_2 = autoencoder_2.fit(
    X_train, X_train,
    epochs=200,
    batch_size=16,
    shuffle=True,
    validation_data=(X_test, X_test),
    verbose=0
)

history_3 = autoencoder_3.fit(
    X_train, X_train,
    epochs=200,
    batch_size=16,
    shuffle=True,
    validation_data=(X_test, X_test),
    verbose=0
)

encoded_2 = encoder_2.predict(X_scaled)
encoded_3 = encoder_3.predict(X_scaled)

def plot_encoded_data(encoded_data, y, title, dimensions=2):
    plt.figure(figsize=(8, 6))
    if dimensions == 2:
        scatter = plt.scatter(encoded_data[:, 0], encoded_data[:, 1], c=y, cmap='viridis', alpha=0.7)
        plt.xlabel('Компонента 1')
        plt.ylabel('Компонента 2')
    elif dimensions == 3:
        from mpl_toolkits.mplot3d import Axes3D
        ax = plt.axes(projection='3d')
        scatter = ax.scatter(encoded_data[:, 0], encoded_data[:, 1], encoded_data[:, 2], c=y, cmap='viridis', alpha=0.7)
        ax.set_xlabel('Компонента 1')
        ax.set_ylabel('Компонента 2')
        ax.set_zlabel('Компонента 3')
    plt.title(title)
    plt.colorbar(scatter, label='Класс')
    plt.show()

plot_encoded_data(encoded_2, y, 'Автоэнкодер: 2 компоненты')
plot_encoded_data(encoded_3, y, 'Автоэнкодер: 3 компоненты', dimensions=3)

tsne_2 = TSNE(n_components=2, random_state=42)
tsne_result_2 = tsne_2.fit_transform(X_scaled)

tsne_3 = TSNE(n_components=3, random_state=42)
tsne_result_3 = tsne_3.fit_transform(X_scaled)

plot_encoded_data(tsne_result_2, y, 't-SNE: 2 компоненты')
plot_encoded_data(tsne_result_3, y, 't-SNE: 3 компоненты', dimensions=3)
