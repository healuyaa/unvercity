import torch
import torch.nn as nn
import torch.optim as optim
import pandas as pd
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split
from torch.utils.data import DataLoader, Dataset

# Загрузка и предобработка данных
data = pd.read_csv('lab1/mushrooms.csv')

# Преобразование категориальных данных в числовые
labelencoder = LabelEncoder()
for col in data.columns:
    data[col] = labelencoder.fit_transform(data[col])

# Разделение на обучающий и тестовый наборы
X_train, X_test = train_test_split(data, test_size=0.2)

# Создание класса Dataset для работы с данными
class MushroomDataset(Dataset):
    def __init__(self, data):
        self.data = data.values.astype(float)  # Преобразование к типу float

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        return torch.FloatTensor(self.data[idx])  # Преобразование входных данных к типу float

# Параметры
input_size = len(data.columns)
hidden_size = 100
output_size = input_size

# Создание модели автоэнкодера
class Autoencoder(nn.Module):
    def __init__(self):
        super(Autoencoder, self).__init__()
        self.encoder = nn.Sequential(
            nn.Linear(input_size, hidden_size),
            nn.ReLU()
        )
        self.decoder = nn.Sequential(
            nn.Linear(hidden_size, output_size),
            nn.Sigmoid()  # Используем Sigmoid на выходе
        )

    def forward(self, x):
        x = self.encoder(x)
        x = self.decoder(x)
        return x

# Обучение автоэнкодера
def train_autoencoder(model, dataloader, num_epochs=10, learning_rate=0.001):
    criterion = nn.MSELoss()  # Меняем функцию потерь на MSE
    optimizer = optim.Adam(model.parameters(), lr=learning_rate)
    total_step = len(dataloader)
    for epoch in range(num_epochs):
        for i, inputs in enumerate(dataloader):
            outputs = model(inputs)
            loss = criterion(outputs, inputs)
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            if (i+1) % 100 == 0:
                print('Epoch [{}/{}], Step [{}/{}], Loss: {:.4f}'
                      .format(epoch+1, num_epochs, i+1, total_step, loss.item()))

# Создание DataLoader для обучающего и тестового наборов
train_dataset = MushroomDataset(X_train)
test_dataset = MushroomDataset(X_test)
train_loader = DataLoader(dataset=train_dataset, batch_size=64, shuffle=True)
test_loader = DataLoader(dataset=test_dataset, batch_size=64, shuffle=False)

# Инициализация и обучение модели
model = Autoencoder()
train_autoencoder(model, train_loader)

# Оценка модели на тестовом наборе
def test_autoencoder(model, dataloader):
    criterion = nn.MSELoss()  # Меняем функцию потерь на MSE
    test_loss = 0.0
    with torch.no_grad():
        for inputs in dataloader:
            outputs = model(inputs)
            loss = criterion(outputs, inputs)
            test_loss += loss.item()
    average_loss = test_loss / len(dataloader)
    print('Average Test Loss: {:.4f}'.format(average_loss))

test_autoencoder(model, test_loader)
