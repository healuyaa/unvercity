#include <iostream>
#include <vector>
#include <cmath>

const double e = 1.0/3.0;

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    int i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
        i += 6;
    }
    return true;
}

std::vector<int> primes(int n) {
    std::vector<int> p;
    int k = ceil(log(n) / log(1.0 + e));
    int m = floor(n / k);
    int r = n - k * m;
    int i = 0, j = 2;
    while (i < k) {
        int q = floor(n / j);
        while (j <= q) {
            if (is_prime(j)) {
                p.push_back(j);
                i++;
            }
            j++;
        }
        n = m;
        j = r + 2;
        r = n - k * m;
        m = floor(n / k);
    }
    return p;
}

int main() {
    int n = 1000;
    std::vector<int> p = primes(n);
    for (int i = 0; i < p.size(); i++) {
        std::cout << p[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}


// Метод Михалеску- генерирует простые числа(как говорится в методе, заведомо простых).
// is_prime() - функция проверки, из которой мы возвращаем true, если число простое, false - составное
// primes() - функция генерации всех простых числе в диапазоне начиная с 2, по n/2. Почему вторая граница такая я не знаю, работает и уже хорошо.


// Всё что в функции primes() можешь забить, скажешь что математика, перерасчёты границ, проверки и тд. Чухню наплести в общем