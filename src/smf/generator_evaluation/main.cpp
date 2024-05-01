#include <iostream>
#include <random>
#include <vector>

bool isUniformSequence(const std::vector<double>& values) {
    // Оцениваем генератор на равномерность
    double sum = 0.0;
    for (const auto& value : values) {
        sum += value;
    }
    double mean = sum / values.size();

    double squaredDiffSum = 0.0;
    for (const auto& value : values) {
        double diff = value - mean;
        squaredDiffSum += diff * diff;
    }
    double variance = squaredDiffSum / values.size();

    // Проверяем, является ли дисперсия достаточно малой
    // для считывания последовательности как равномерной
    double epsilon = 1e-6; // Пороговое значение
    return variance < epsilon;
}

int main() {
    // Создаем генератор случайных чисел с равномерным распределением
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Создаем вектор для хранения сгенерированных значений
    std::vector<double> values;

    // Генерируем и сохраняем 1000 случайных значений
    for (int i = 0; i < 1000; ++i) {
        double randomValue = dis(gen);
        values.push_back(randomValue);
    }

    // Проверяем, является ли последовательность равномерной
    bool isUniform = isUniformSequence(values);

    // Выводим результат
    if (isUniform) {
        std::cout << "Последовательность является равномерной." << std::endl;
    } else {
        std::cout << "Последовательность НЕ является равномерной." << std::endl;
    }

    return 0;
}
