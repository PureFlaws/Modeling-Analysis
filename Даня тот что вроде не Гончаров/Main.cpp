#include "Exercises_1_Lab.h"
#include "Exercises_2_Lab.h"
#include "Exercises_3_Lab.h"
#include "Exercises_4_Lab_Stack.h"
#include "Exercises_4_Lab_Queue.h"
#include "Exercises_5_Lab.h"

void MainMenu() {
    std::vector<std::string> menuItems = {
        "1. 1 Лабораторна робота\n",
        "2. 2 Лабораторна робота\n",
        "3. 3 Лабораторна робота\n",
        "4. 4 Лабораторна робота(Стек)\n",
        "5. 4 Лабораторна робота(Черга)\n",
        "6. 5 Лабораторна робота\n",
        "0. Вихід з меню\n"
    };

    // Переконайтеся, що функції лабораторних робіт визначені як void Lab_x() {}
    std::vector<std::function<void()>> actions = {
        []() { Lab_1(); },
        []() { Lab_2(); },
        []() { Lab_3(); },
        []() { Lab_4_Stack(); },
        []() { Lab_4_Queue(); },
        []() { Lab_5(); }
    };

    DisplayMenu(menuItems, actions);
}

int main() {
    SetConsoleOutputCP(1251); // Встановлюємо кодування сторінки для виводу
    SetConsoleCP(1251); // Встановлюємо кодування сторінки для вводу
    //Запускаємо наше основне меню з ЛР по нашому предмету
    MainMenu();
    return 0;
}