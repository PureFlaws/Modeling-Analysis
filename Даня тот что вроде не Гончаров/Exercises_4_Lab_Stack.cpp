#include "Exercises_4_Lab_Stack.h"
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <stack>
#include <limits>
#include <string>

#include <fstream>
#include <sstream>

using namespace std;

//1 Валідні дужки
bool isValid(const std::string& s) {
    std::unordered_map<char, char> bracketPairs = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };
    std::stack<char> stack;

    for (char c : s) {
        if (bracketPairs.find(c) != bracketPairs.end()) {
            if (stack.empty() || stack.top() != bracketPairs[c]) {
                return false;
            }
            stack.pop();
        }
        else {
            stack.push(c);
        }
    }

    return stack.empty();
}
//2 Обхід бінарного дерева в порядку (Inorder Traversal)

// Допоміжна функція для рекурсивного обходу
void inorderTraversalHelper(TreeNode* root, std::vector<int>& result) {
    if (root != nullptr) {
        inorderTraversalHelper(root->left, result);
        result.push_back(root->val);
        inorderTraversalHelper(root->right, result);
    }
}

// Функція для виконання обходу
void inorderTraversal(TreeNode* root, std::vector<int>& result) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left, result);
    result.push_back(root->val);
    inorderTraversal(root->right, result);
}
TreeNode* insertLevelOrder(const std::vector<int>& values, int i) {
    if (i < values.size()+1 && values[i] != -1) {
        TreeNode* root = new TreeNode(values[i]);
        root->left = insertLevelOrder(values, 2 * i + 1);
        root->right = insertLevelOrder(values, 2 * i + 2);
        return root;
    }
    return nullptr;
}

//5 Декодувати рядок
std::string decodeString(const std::string& s) {
    std::stack<std::string> charsStack;
    std::stack<int> numsStack;
    std::string currentString;
    int currentNum = 0;

    for (char c : s) {
        if (isdigit(c)) {
            currentNum = currentNum * 10 + (c - '0');
        }
        else if (c == '[') {
            numsStack.push(currentNum);
            charsStack.push(currentString);
            currentNum = 0;
            currentString.clear();
        }
        else if (c == ']') {
            std::string decodedString = charsStack.top();
            charsStack.pop();
            for (int i = numsStack.top(); i > 0; --i) {
                decodedString += currentString;
            }
            numsStack.pop();
            currentString = decodedString;
        }
        else {
            currentString += c;
        }
    }

    return currentString;
}

//6 Оцініть зворотну польську нотацію
int evalRPN(const std::vector<std::string>& tokens) {
    std::stack<int> stack;
    for (const std::string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int operand2 = stack.top(); stack.pop();
            int operand1 = stack.top(); stack.pop();
            switch (token[0]) {
            case '+': stack.push(operand1 + operand2); break;
            case '-': stack.push(operand1 - operand2); break;
            case '*': stack.push(operand1 * operand2); break;
            case '/': stack.push(operand1 / operand2); break;
            }
        }
        else {
            stack.push(stoi(token));
        }
    }
    return stack.top();
}

//7 Найдовші дійсні дужки
int longestValidParentheses(const std::string& s) {
    int maxLength = 0;
    std::stack<int> stack;
    stack.push(-1); // база для визначення довжини
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            stack.push(i);
        }
        else {
            stack.pop();
            if (stack.empty()) {
                stack.push(i); // нова база
            }
            else {
                maxLength = std::max(maxLength, i - stack.top());
            }
        }
    }
    return maxLength;
}

//Функції меню
//////////////////////////////////////////////////////////////////////////////////////////
//1 кейс
void caseOneLab4()
{
    std::string inputString;
    std::cout << "Введіть рядок з дужками: ";
    std::cin >> inputString;

    // Перевірка довжини рядка і символів
    if (checkCin((inputString.length() < 1 || inputString.length() > 10000),
        "Помилка: неправильна довжина рядка.", 
        (inputString.find_first_not_of("()[]{}") != std::string::npos),
        "Помилка: рядок містить неприпустимі символи."))  
    {   return; }

    bool isValidResult = isValid(inputString);
    std::cout << "Результат: " << (isValidResult ? "true" : "false") << std::endl;

}
//////////////////////////////////////////////////////////////////////////////////////////
//2 кейс
void caseTwoLab4() {
    std::cout << "Введіть значення вузлів дерева через пробіл (використовуйте -1 для відсутнього вузла): ";
    std::vector<int> values;
    std::string element;

    while (std::cin >> element && element != "end") {
        if (element == "null") {
            values.push_back(-1); // NULL will represent a null node
        }
        else {
            int num = std::stoi(element);
            if (num < -100 || num > 100) {
                std::cout << "Помилка: значення вузла не входить в дозволений діапазон." << std::endl;
                return;
            }
            values.push_back(num);
        }
    }

    TreeNode* root = insertLevelOrder(values, 0);
    std::vector<int> result;
    inorderTraversal(root, result);
    std::cout << "Inorder Traversal: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//3 кейс
void minStackPush(MinStack& minStack) {
    int value;
    std::cout << "Введіть значення для push: ";
    std::cin >> value;
    if (!std::cin.fail()) {
        minStack.push(value);
    }
    else {
        std::cout << "Помилка: некоректне значення." << std::endl;
        std::cin.clear(); // Очищуємо помилку вводу
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ігноруємо неправильний ввід
    }
}
void minStackPop(MinStack& minStack) {
    if (!minStack.empty()) {
        minStack.pop();
        std::cout << "Елемент видалено.\n";
    }
    else {
        std::cout << "Стек порожній.\n";
    }
}
void minStackTop(MinStack& minStack) {
    if (!minStack.empty()) {
        std::cout << "Top елемент: " << minStack.top() << std::endl;
    }
    else {
        std::cout << "Стек порожній.\n";
    }
}
void minStackGetMin(MinStack& minStack) {
    if (!minStack.empty()) {
        std::cout << "Мінімальний елемент: " << minStack.getMin() << std::endl;
    }
    else {
        std::cout << "Стек порожній.\n";
    }
}
void caseThreeLab4() {
    MinStack minStack;

    std::vector<std::string> minStackMenuItems = {
        "1. Push",
        "2. Pop",
        "3. Top",
        "4. GetMin",
        "0. Вихід"
    };

    std::vector<std::function<void()>> minStackActions = {
        [&]() { minStackPush(minStack); },
        [&]() { minStackPop(minStack); },
        [&]() { minStackTop(minStack); },
        [&]() { minStackGetMin(minStack); }
    };

    DisplayMenu(minStackMenuItems, minStackActions);
}
//////////////////////////////////////////////////////////////////////////////////////////
//4 кейс
void queuePush(MyQueue& myQueue) {
    int value;
    std::cout << "Введіть значення для push (від 1 до 9): ";
    std::cin >> value;
    if (!std::cin.fail() && value >= 1 && value <= 9) {
        myQueue.push(value);
    }
    else {
        std::cout << "Помилка: значення має бути в діапазоні від 1 до 9." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
void queuePop(MyQueue& myQueue) {
    if (!myQueue.empty()) 
        std::cout << "Елемент на початку черги: " << myQueue.pop() << " видалено.\n";    
    else 
        std::cout << "Черга порожня.\n";    
}
void queuePeek(MyQueue& myQueue) {
    if (!myQueue.empty()) 
        std::cout << "Елемент на початку черги: " << myQueue.peek() << std::endl;    
    else 
        std::cout << "Черга порожня.\n";    
}
void queueEmpty(MyQueue& myQueue) {
    std::cout << (myQueue.empty() ? "Черга порожня.\n" : "Черга містить елементи.\n");
}

void caseFourLab4() {
    MyQueue myQueue;
    std::vector<std::string> queueMenuItems = {
        "1. Push",
        "2. Pop",
        "3. Peek",
        "4. Empty",
        "0. Вихід"
    };

    std::vector<std::function<void()>> queueActions = {
        [&]() { queuePush(myQueue); },
        [&]() { queuePop(myQueue); },
        [&]() { queuePeek(myQueue); },
        [&]() { queueEmpty(myQueue); }
    };

    DisplayMenu(queueMenuItems, queueActions);
}
//////////////////////////////////////////////////////////////////////////////////////////
//5 кейс
void caseFiveLab4()
{
    std::string inputString;
    std::cout << "Введіть закодований рядок (довжина від 1 до 30 символів, лише малі літери, цифри та квадратні дужки): ";
    std::cin >> inputString;

    // Перевірка обмежень
    if (checkCin((inputString.length() < 1 || inputString.length() > 30),
        "Помилка: недопустима довжина рядка.\n"))
        return;

    // Перевірка на допустимі символи
    bool isValidCharacter = true;
    for (char c : inputString) {
        if (!std::isdigit(c) && (c < 'a' || c > 'z') && c != '[' && c != ']') {
            isValidCharacter = false;
            break;
        }
    }

    if (!isValidCharacter) {
        std::cout << "Помилка: рядок містить недопустимі символи.\n";
        return;
    }

    // Виконання декодування
    try {
        std::string decodedString = decodeString(inputString);
        std::cout << "Декодований рядок: " << decodedString << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Виникла помилка при декодуванні: " << e.what() << std::endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//6 кейс
void caseSixLab4() {
    std::vector<std::string> tokens;
    std::string token;
    std::cout << "Введіть елементи виразу, розділені пробілами (закінчіть вводом 'end'): ";
    while (std::cin >> token && token != "end") {
        tokens.push_back(token);
    }

    // Перевірка обмежень
    if (checkCin((tokens.size() < 1 || tokens.size() > 104), "Помилка: недопустима кількість токенів.\n")) {
        return;
    }

    for (const auto& t : tokens) {
        if (std::isdigit(t[0]) || t[0] == '-' && t.size() > 1) {
            if (std::stoi(t) < -200 || std::stoi(t) > 200) {
                std::cout << "Помилка: токен за межами діапазону [-200, 200].\n";
                return;
            }
        }
        else if (t != "+" && t != "-" && t != "*" && t != "/") {
            std::cout << "Помилка: невідомий оператор '" << t << "'.\n";
            return;
        }
    }

    try {
        int result = evalRPN(tokens);
        std::cout << "Результат виразу: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Виникла помилка при обчисленні виразу: " << e.what() << std::endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//7 кейс
void caseSevenLab4() {
    std::string inputString;
    std::cout << "Введіть рядок, що складається з '(' і ')': ";
    std::cin >> inputString;

    // Перевірка обмежень
    if (inputString.length() > 30000) {
        std::cout << "Помилка: рядок завеликий.\n";
        return;
    }

    bool isValidCharacter = true;
    for (char c : inputString) {
        if (!std::isdigit(c) && (c < 'a' || c > 'z') && c != '[' && c != ']') {
            isValidCharacter = false;
            break;
        }
    }

    if (!isValidCharacter) {
        std::cout << "Помилка: рядок містить недопустимі символи.\n";
        return;
    }

    int result = longestValidParentheses(inputString);
    std::cout << "Довжина найдовших дійсних дужок підрядку: " << result << std::endl;
}

void Lab_4_Stack() {
    std::vector<std::string> menuItems = {
        "1. Валідні дужки\n",
        "2. Обхід бінарного дерева в порядку\n",
        "3. Мінімальний стек\n",
        "4. Реалізуйте чергу використовуючи стеки\n",
        "5. Декодувати рядок\n",
        "6. Оцініть зворотну польську нотацію\n",
        "7. Найдовші дійсні дужки\n",
       "0. Вихід з меню\n"
    };


    std::vector<std::function<void()>> actions = {
        []() { caseOneLab4(); },
        []() { caseTwoLab4(); },
        []() { caseThreeLab4(); },
        []() { caseFourLab4(); },
        []() { caseFiveLab4(); },
        []() { caseSixLab4(); },
        []() { caseSevenLab4(); }
    };

    DisplayMenu(menuItems, actions);
}