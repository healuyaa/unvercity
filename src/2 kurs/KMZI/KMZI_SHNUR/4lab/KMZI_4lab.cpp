#include <iostream>
#include <cmath>

bool isPerfectSquare(long long n) {
    long long sqrtN = sqrt(n);
    return sqrtN * sqrtN == n;
}

void fermatFactorization(long long n) {
    if (n <= 1) {
        std::cout << "Число должно быть больше 1." << std::endl;
        return;
    }

    if (isPerfectSquare(n)) {
        std::cout << "Число является квадратом простого числа: " << sqrt(n) << std::endl;
        return;
    }

    long long a = ceil(sqrt(n));            // Ближайшее целое число от исходного числа
    long long b2 = a * a - n;               // Математика для проверки
    while (!isPerfectSquare(b2)) {          // Мы делаем пока b2 не станет квадратом целого числа
        a++;                                // В теле увеличаем (a++), тем самым перебирая числа. 
        b2 = a * a - n;                     // Пересчитываем b2, при новом a
    }

    long long b = sqrt(b2);
    long long factor1 = a - b;
    long long factor2 = a + b;

    std::cout << "Факторизация числа " << n << ":" << std::endl;
    std::cout << n << " = " << factor1 << " * " << factor2 << std::endl;
}

int main() {
    long long number;
    std::cout << "Введите число для факторизации: ";
    std::cin >> number;

    fermatFactorization(number);

    return 0;
}

// Факторизация - разделение числа на множители, они могут быть не всегда простыми
// Метод Ферма - это по сути перебор первого множителя, пока второй не будет целым числом(без дробной части)
// isPerfectSquare() - функция проверки на квадратность, если подать: 100, программа напишет - Число является квадратом простого числа: 10