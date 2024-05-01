#include <iostream>
#include <vector>

class LinearCongruentialGenerator {
private:
    unsigned long long seed;
    unsigned long long a;
    unsigned long long c;
    unsigned long long m;

public:
    LinearCongruentialGenerator(unsigned long long seed = 0) { 
        this->seed = seed;
        a = 1103515245;
        c = 12345;
        m = 2147483648; // 2^31
    }

    unsigned long long generate() {
        seed = (a * seed + c) % m; // все числа генерятся по этой формуле, где "a", "c" и "m" - это константы(их мы можем трогать и ставить всё что душе угодно).
        return seed % 15;                // При этом мы каждый раз генерируем новое число исходя из прошлого 
    }
};

bool isUniformSequence(const std::vector<unsigned long long>& values) {
    // Оцениваем генератор на равномерность
    unsigned long long sum = 0.0;
    for (const auto& value : values) {
        sum += value;
    }
    unsigned long long mean = sum / values.size();

    unsigned long long squaredDiffSum = 0.0;
    for (const auto& value : values) {
        unsigned long long diff = value - mean;
        squaredDiffSum += diff * diff;
    }
    double variance = (double)squaredDiffSum / values.size();

    // Проверяем, является ли дисперсия достаточно малой
    // для считывания последовательности как равномерной
    double epsilon = 1e-6; // Пороговое значение
    return variance < epsilon;
}

int main() {
    LinearCongruentialGenerator generator(42); // 42 начальное число
    std::vector<unsigned long long> generatedNumbers;

    for (int i = 0; i < 100; i++) { 
        unsigned long long randomNumber = generator.generate();
        generatedNumbers.push_back(randomNumber);
    }

    for (const auto& number : generatedNumbers) { // Вывод сгенерированных значений
        std::cout << number << ' ';
    }
    std::cout << "\n";

    // Проверяем, является ли последовательность равномерной
    bool isUniform = isUniformSequence(generatedNumbers);

    // Выводим результат
    if (isUniform) {
        std::cout << "Последовательность является равномерной." << std::endl;
    } else {
        std::cout << "Последовательность НЕ является равномерной." << std::endl;
    }
}


// Через класс проще всего было сделать + Хацкевич не доебёться до константных чисел(меня отправила раз: переписать 1 константу, пиздец...)
// в классе метод generate твой генератор, он принимает seed - просто какое-то число
// если нужно будет увеличить количество элементов в первый цикле(for) увеличь количество итераций


// По правому столбику в варианте:
// "Мультипликативный генератор Лемера" - это тот же самый генератор, что и у нас(конгруэнтным генератором), но с одним отличием коэффицент "c" = 0
// Смешанный генератор - это несколько таких генераторов(конгруэнтным генератором), но с разными параметрами

// Функция isUniformSequence проверяет ли последовательность равномерной
// Если в 2 словах, она вычисляет дисперсию и оценивает её, если она меньше чем число 0.000001(10^-6), значит она равномерна, и в точности да наобарот

// Есть ещё оценка алгоритма на период(появление одинаковых значений, спустя некоторое время), тут сложнее. Это всё зависит от коэфицентов, какие ты поставить. 