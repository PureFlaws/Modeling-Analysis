#include "Menu.h"
#include<stdlib.h>
#include<conio.h>
#include <stdio.h>
#include<windows.h>
#define _CRT_SECURE_NO_DEPRECATE

using namespace std;

void DisplayMenu(const std::vector<std::string>& menuItems, const std::vector<std::function<void()>>& actions) {
    int choice = 0;
    bool exit = false;

    while (!exit) {
        // Виводимо пункти меню
        for (int i = 0; i < menuItems.size(); i++) {
            std::cout << (i == choice ? "> " : "  ") << menuItems[i] << "\n";
        }

        // Input handling
        int pressed = _getch();
        if (pressed == 'w' || pressed == 'W') {
            choice = (choice == 0) ? menuItems.size() - 1 : choice - 1;
        }
        else if (pressed == 's' || pressed == 'S') {
            choice = (choice + 1) % menuItems.size();
        }
        else if (pressed == '\r' || pressed == '\n') {
            if (choice >= 0 && choice < actions.size()) {
                system("pause");
                system("cls");
                cout << "\n";
                cout << menuItems[choice]<<"\n";
                actions[choice]();  // Виклик обраної функції
                cout << "\n";
                system("pause");
                system("cls");
                cout << "\n";
            }
            if (choice == menuItems.size() - 1) {  // Перевірка на вихід
                exit = true;
            }
        }

        system("cls");
    }
}
