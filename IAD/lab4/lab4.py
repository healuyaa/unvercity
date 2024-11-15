import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.metrics import f1_score, confusion_matrix
from sklearn.neural_network import BernoulliRBM
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import Adam
import matplotlib.pyplot as plt

url = 'https://archive.ics.uci.edu/ml/machine-learning-databases/thyroid-disease/ann-train.data'
data = pd.read_csv(url, delim_whitespace=True, header=None)
data = data.dropna()

X = data.iloc[:, :-1].values
y = data.iloc[:, -1].values

label_encoder = LabelEncoder()
y = label_encoder.fit_transform(y)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

def pretrain_rbm_stack(X, layer_sizes, epochs=20, learning_rate=0.001, batch_size=10):
    rbm_layers = []
    input_data = X

    for i, size in enumerate(layer_sizes):
        rbm = BernoulliRBM(n_components=size, learning_rate=learning_rate, n_iter=epochs, batch_size=batch_size, random_state=42)
        rbm.fit(input_data)
        rbm_layers.append(rbm)
        input_data = rbm.transform(input_data)

    return rbm_layers

layer_sizes = [64, 32, 16]
rbm_layers = pretrain_rbm_stack(X_train, layer_sizes, epochs=20, learning_rate=0.001)

def build_classification_model_with_rbm(rbm_layers, input_dim, output_dim):
    model = Sequential()
    model.add(Dense(64, activation='relu', input_shape=(input_dim,)))

    model.layers[0].set_weights([rbm_layers[0].components_.T, np.zeros(64)])

    model.add(Dense(32, activation='relu'))
    model.layers[1].set_weights([rbm_layers[1].components_.T, np.zeros(32)])

    model.add(Dense(16, activation='relu'))
    model.layers[2].set_weights([rbm_layers[2].components_.T, np.zeros(16)])

    model.add(Dense(output_dim, activation='softmax'))
    model.compile(optimizer=Adam(0.001), loss='sparse_categorical_crossentropy', metrics=['accuracy'])

    return model

model_with_pretrain = build_classification_model_with_rbm(rbm_layers, input_dim=X_train.shape[1], output_dim=3)
history_with_pretrain = model_with_pretrain.fit(X_train, y_train, epochs=50, batch_size=32, validation_split=0.2, verbose=1)

y_pred_with_pretrain = np.argmax(model_with_pretrain.predict(X_test), axis=1)
f1_with_pretrain = f1_score(y_test, y_pred_with_pretrain, average='weighted')
conf_matrix_with_pretrain = confusion_matrix(y_test, y_pred_with_pretrain)

plt.figure(figsize=(14, 5))
plt.plot(history_with_pretrain.history['accuracy'], label='Train Accuracy (с предобучением RBM)')
plt.plot(history_with_pretrain.history['val_accuracy'], label='Val Accuracy (с предобучением RBM)')
plt.plot(history_with_pretrain.history['loss'], label='Train Loss (с предобучением RBM)')
plt.plot(history_with_pretrain.history['val_loss'], label='Val Loss (с предобучением RBM)')
plt.title('Обучение с предобучением RBM')
plt.xlabel('Epoch')
plt.ylabel('Accuracy / Loss')
plt.legend()
plt.show()

plt.figure()
bars = plt.bar(['С предобучением (RBM)'], [f1_with_pretrain], color='green')
plt.title('Сравнение F1 Score (с предобучением RBM)')
plt.ylabel('F1 Score')

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width() / 2, yval, round(yval, 3), ha='center', va='bottom')

plt.show()

