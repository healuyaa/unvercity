import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.metrics import classification_report, confusion_matrix
import tensorflow as tf
from tensorflow.keras import layers, models

url = "https://archive.ics.uci.edu/ml/machine-learning-databases/thyroid-disease/allhypo.data"
column_names = ["target", "feature1", "feature2", "feature3", "feature4", "feature5", "feature6", "feature7", "feature8", 
                "feature9", "feature10", "feature11", "feature12", "feature13", "feature14", "feature15", "feature16", 
                "feature17", "feature18", "feature19", "feature20", "feature21", "feature22", "feature23", "feature24", "feature25"]
data = pd.read_csv(url, names=column_names, na_values="?")

data.dropna(inplace=True)
data['target'] = LabelEncoder().fit_transform(data['target'])

X = data.drop("target", axis=1)
y = data["target"]

scaler = StandardScaler()
X = scaler.fit_transform(X)

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

def build_classification_model():
    model = models.Sequential([
        layers.Dense(64, activation='relu', input_shape=(X_train.shape[1],)),
        layers.Dense(32, activation='relu'),
        layers.Dense(16, activation='relu'),
        layers.Dense(1, activation='sigmoid')
    ])
    model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
    return model

model_no_pretrain = build_classification_model()
history_no_pretrain = model_no_pretrain.fit(X_train, y_train, epochs=20, batch_size=32, validation_split=0.2, verbose=1)

y_pred_no_pretrain = (model_no_pretrain.predict(X_test) > 0.5).astype("int32")
print("Без предобучения:")
print(classification_report(y_test, y_pred_no_pretrain))
print(confusion_matrix(y_test, y_pred_no_pretrain))

def build_autoencoder():
    encoder = models.Sequential([
        layers.Dense(64, activation='relu', input_shape=(X_train.shape[1],)),
        layers.Dense(32, activation='relu'),
        layers.Dense(16, activation='relu')
    ])
    decoder = models.Sequential([
        layers.Dense(32, activation='relu', input_shape=(16,)),
        layers.Dense(64, activation='relu'),
        layers.Dense(X_train.shape[1], activation='sigmoid')
    ])
    autoencoder = models.Sequential([encoder, decoder])
    autoencoder.compile(optimizer='adam', loss='mse')
    return autoencoder, encoder

autoencoder, encoder = build_autoencoder()
autoencoder.fit(X_train, X_train, epochs=50, batch_size=32, validation_split=0.2, verbose=1)

def build_classification_model_with_pretrain(encoder):
    model = models.Sequential([
        encoder,
        layers.Dense(1, activation='sigmoid')
    ])
    model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
    return model

model_with_pretrain = build_classification_model_with_pretrain(encoder)
history_with_pretrain = model_with_pretrain.fit(X_train, y_train, epochs=20, batch_size=32, validation_split=0.2, verbose=1)

y_pred_with_pretrain = (model_with_pretrain.predict(X_test) > 0.5).astype("int32")
print("С предобучением:")
print(classification_report(y_test, y_pred_with_pretrain))
print(confusion_matrix(y_test, y_pred_with_pretrain))

print("Сравнение моделей:")
print("Без предобучения:")
print(classification_report(y_test, y_pred_no_pretrain))
print("С предобучением:")
print(classification_report(y_test, y_pred_with_pretrain))
