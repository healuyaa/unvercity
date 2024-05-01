#include <iostream>
#include <Windows.h>
#include <conio.h>

int main() {
    std::string input = "";
    bool endPressed = false;

    while (!endPressed) {
        // Проверяем состояние клавиши End (VK_END)
        if (GetAsyncKeyState(VK_END)) {
            std::cout << "Ввод завершен по нажатию End." << std::endl;
            endPressed = true;
        }

        if (!kbhit()) {
            // Задержка, чтобы не слишком часто проверять клавиши
            Sleep(100); // Задержка в миллисекундах
            continue;
        }

        char c = getch();
        // Добавляем символы к текущей строке
        input += c;
        std::cout << c;
    }

    return 0;
}
