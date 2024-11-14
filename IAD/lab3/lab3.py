import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.metrics import f1_score, confusion_matrix
from tensorflow.keras.models import Sequential, Model
from tensorflow.keras.layers import Dense, Input
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

def build_classification_model():
    model = Sequential([
        Dense(64, activation='relu', input_shape=(X_train.shape[1],)),
        Dense(32, activation='relu'),
        Dense(16, activation='relu'),
        Dense(3, activation='softmax')
    ])
    model.compile(optimizer=Adam(0.001), loss='sparse_categorical_crossentropy', metrics=['accuracy'])
    return model

model_no_pretrain = build_classification_model()
history_no_pretrain = model_no_pretrain.fit(X_train, y_train, epochs=50, batch_size=32, validation_split=0.2, verbose=1)

y_pred_no_pretrain = np.argmax(model_no_pretrain.predict(X_test), axis=1)
f1_no_pretrain = f1_score(y_test, y_pred_no_pretrain, average='weighted')
conf_matrix_no_pretrain = confusion_matrix(y_test, y_pred_no_pretrain)

def build_autoencoder(input_dim):
    input_layer = Input(shape=(input_dim,))
    encoder = Dense(64, activation='relu')(input_layer)
    encoder = Dense(32, activation='relu')(encoder)
    bottleneck = Dense(16, activation='relu')(encoder)
    decoder = Dense(32, activation='relu')(bottleneck)
    decoder = Dense(64, activation='relu')(decoder)
    output_layer = Dense(input_dim, activation='linear')(decoder)
    
    autoencoder = Model(inputs=input_layer, outputs=output_layer)
    autoencoder.compile(optimizer=Adam(0.001), loss='mse')
    return autoencoder

autoencoder = build_autoencoder(X_train.shape[1])
autoencoder.fit(X_train, X_train, epochs=50, batch_size=32, validation_split=0.2, verbose=1)

pretrained_weights = autoencoder.layers[1].get_weights()

model_with_pretrain = build_classification_model()
model_with_pretrain.layers[0].set_weights(pretrained_weights)

history_with_pretrain = model_with_pretrain.fit(X_train, y_train, epochs=50, batch_size=32, validation_split=0.2, verbose=1)

y_pred_with_pretrain = np.argmax(model_with_pretrain.predict(X_test), axis=1)
f1_with_pretrain = f1_score(y_test, y_pred_with_pretrain, average='weighted')
conf_matrix_with_pretrain = confusion_matrix(y_test, y_pred_with_pretrain)

plt.figure(figsize=(14, 5))
plt.subplot(1, 2, 1)
plt.plot(history_no_pretrain.history['accuracy'], label='Train Accuracy (без предобучения)')
plt.plot(history_no_pretrain.history['val_accuracy'], label='Val Accuracy (без предобучения)')
plt.plot(history_no_pretrain.history['loss'], label='Train Loss (без предобучения)')
plt.plot(history_no_pretrain.history['val_loss'], label='Val Loss (без предобучения)')
plt.title('Обучение без предобучения')
plt.xlabel('Epoch')
plt.ylabel('Accuracy / Loss')
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(history_with_pretrain.history['accuracy'], label='Train Accuracy (с предобучением)')
plt.plot(history_with_pretrain.history['val_accuracy'], label='Val Accuracy (с предобучением)')
plt.plot(history_with_pretrain.history['loss'], label='Train Loss (с предобучением)')
plt.plot(history_with_pretrain.history['val_loss'], label='Val Loss (с предобучением)')
plt.title('Обучение с предобучением')
plt.xlabel('Epoch')
plt.ylabel('Accuracy / Loss')
plt.legend()
plt.show()

plt.figure()
bars = plt.bar(['Без предобучения', 'С предобучением'], [f1_no_pretrain, f1_with_pretrain], color=['blue', 'green'])
plt.title('Сравнение F1 Score')
plt.ylabel('F1 Score')

for bar in bars:
    yval = bar.get_height()
    plt.text(bar.get_x() + bar.get_width() / 2, yval, round(yval, 3), ha='center', va='bottom')

plt.show()

