#include "Exercises_1_Lab.h"
#include "Exercises_2_Lab.h"
#include "Exercises_3_Lab.h"
#include "Exercises_4_Lab_Stack.h"
#include "Exercises_4_Lab_Queue.h"
#include "Exercises_5_Lab.h"

void MainMenu() {
    std::vector<std::string> menuItems = {
        "1. 1 ����������� ������\n",
        "2. 2 ����������� ������\n",
        "3. 3 ����������� ������\n",
        "4. 4 ����������� ������(����)\n",
        "5. 4 ����������� ������(�����)\n",
        "6. 5 ����������� ������\n",
        "0. ����� � ����\n"
    };

    // �������������, �� ������� ������������ ���� �������� �� void Lab_x() {}
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
    SetConsoleOutputCP(1251); // ������������ ��������� ������� ��� ������
    SetConsoleCP(1251); // ������������ ��������� ������� ��� �����
    //��������� ���� ������� ���� � �� �� ������ ��������
    MainMenu();
    return 0;
}