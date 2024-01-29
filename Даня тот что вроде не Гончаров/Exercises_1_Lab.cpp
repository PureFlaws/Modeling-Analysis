#include "Exercises_1_Lab.h"

void printReverse(const std::string& str, int index) {
    if (index < 0) return;
    std::cout << str[index];
    printReverse(str, index - 1);
}

//Обмін вузлів у звязному списку

//Функція обміну вузлів
ListNode* swapPairs(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* temp = head->next;
    head->next = swapPairs(head->next->next);
    temp->next = head;

    return temp;
}


//Числа Фібоначчі
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int climbStairs(int n) {
    if (n <= 1) return 1;
    return climbStairs(n - 1) + climbStairs(n - 2);
}

double power(double x, int n) {
    if (n == 0) return 1;
    if (n < 0) return 1 / power(x, -n);
    double half = power(x, n / 2);
    return (n % 2 == 0) ? half * half : x * half * half;
}

//Функції меню
void caseOneLab1()
{
    std::string str;
    std::cout << "Enter a string: ";
    std::cin >> str;
    printReverse(str, static_cast<int>(str.length()) - 1);
}
void caseTwoLab1()
{
    // Створення списку для тестування
    ListNode* head = createList({ 1, 2, 3, 4 });

    std::cout << "Original list: ";
    printList(head);

    // Обмін вузлів у списку
    ListNode* newHead = swapPairs(head);

    std::cout << "Swapped list: ";
    printList(newHead);

    // Очищення пам'яті
    deleteList(newHead);
}
void caseThreeLab1()
{
    int n;
    std::cout << "Enter n for Fibonacci: ";
    std::cin >> n;
    std::cout << "Fibonacci(" << n << ") = " << fibonacci(n) << std::endl;
}
void caseFourLab1()
{
    int n;
    std::cout << "Enter number of stairs: ";
    std::cin >> n;
    std::cout << "Number of ways: " << climbStairs(n) << std::endl;
}
void caseFiveLab1()
{
    double x;
    int n;
    std::cout << "Enter x and n for power function: ";
    std::cin >> x >> n;
    std::cout << "Power(" << x << ", " << n << ") = " << power(x, n) << std::endl;
}

void Lab_1()
{
    std::vector<std::string> menuItems = {
        "1. Print String in Reverse\n",
        "2. Swap Pairs in Linked List\n",
        "3. Fibonacci Number\n",
        "4. Climbing Stairs\n",
        "5. Power of X\n",
        "0. Exit\n"
    };

    std::vector<std::function<void()>> actions = {
        []() { caseOneLab1(); },
        []() { caseTwoLab1(); },
        []() { caseThreeLab1(); },
        []() { caseFourLab1(); },
        []() { caseFiveLab1(); }
    };

    DisplayMenu(menuItems, actions);

    return;
}