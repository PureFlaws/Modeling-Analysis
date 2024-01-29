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

//1 ����� �����
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
//2 ����� �������� ������ � ������� (Inorder Traversal)

// �������� ������� ��� ������������ ������
void inorderTraversalHelper(TreeNode* root, std::vector<int>& result) {
    if (root != nullptr) {
        inorderTraversalHelper(root->left, result);
        result.push_back(root->val);
        inorderTraversalHelper(root->right, result);
    }
}

// ������� ��� ��������� ������
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

//5 ���������� �����
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

//6 ������ �������� �������� �������
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

//7 �������� ���� �����
int longestValidParentheses(const std::string& s) {
    int maxLength = 0;
    std::stack<int> stack;
    stack.push(-1); // ���� ��� ���������� �������
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            stack.push(i);
        }
        else {
            stack.pop();
            if (stack.empty()) {
                stack.push(i); // ���� ����
            }
            else {
                maxLength = std::max(maxLength, i - stack.top());
            }
        }
    }
    return maxLength;
}

//������� ����
//////////////////////////////////////////////////////////////////////////////////////////
//1 ����
void caseOneLab4()
{
    std::string inputString;
    std::cout << "������ ����� � �������: ";
    std::cin >> inputString;

    // �������� ������� ����� � �������
    if (checkCin((inputString.length() < 1 || inputString.length() > 10000),
        "�������: ����������� ������� �����.", 
        (inputString.find_first_not_of("()[]{}") != std::string::npos),
        "�������: ����� ������ ����������� �������."))  
    {   return; }

    bool isValidResult = isValid(inputString);
    std::cout << "���������: " << (isValidResult ? "true" : "false") << std::endl;

}
//////////////////////////////////////////////////////////////////////////////////////////
//2 ����
void caseTwoLab4() {
    std::cout << "������ �������� ����� ������ ����� ����� (�������������� -1 ��� ���������� �����): ";
    std::vector<int> values;
    std::string element;

    while (std::cin >> element && element != "end") {
        if (element == "null") {
            values.push_back(-1); // NULL will represent a null node
        }
        else {
            int num = std::stoi(element);
            if (num < -100 || num > 100) {
                std::cout << "�������: �������� ����� �� ������� � ���������� �������." << std::endl;
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
//3 ����
void minStackPush(MinStack& minStack) {
    int value;
    std::cout << "������ �������� ��� push: ";
    std::cin >> value;
    if (!std::cin.fail()) {
        minStack.push(value);
    }
    else {
        std::cout << "�������: ���������� ��������." << std::endl;
        std::cin.clear(); // ������� ������� �����
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �������� ������������ ���
    }
}
void minStackPop(MinStack& minStack) {
    if (!minStack.empty()) {
        minStack.pop();
        std::cout << "������� ��������.\n";
    }
    else {
        std::cout << "���� �������.\n";
    }
}
void minStackTop(MinStack& minStack) {
    if (!minStack.empty()) {
        std::cout << "Top �������: " << minStack.top() << std::endl;
    }
    else {
        std::cout << "���� �������.\n";
    }
}
void minStackGetMin(MinStack& minStack) {
    if (!minStack.empty()) {
        std::cout << "̳�������� �������: " << minStack.getMin() << std::endl;
    }
    else {
        std::cout << "���� �������.\n";
    }
}
void caseThreeLab4() {
    MinStack minStack;

    std::vector<std::string> minStackMenuItems = {
        "1. Push",
        "2. Pop",
        "3. Top",
        "4. GetMin",
        "0. �����"
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
//4 ����
void queuePush(MyQueue& myQueue) {
    int value;
    std::cout << "������ �������� ��� push (�� 1 �� 9): ";
    std::cin >> value;
    if (!std::cin.fail() && value >= 1 && value <= 9) {
        myQueue.push(value);
    }
    else {
        std::cout << "�������: �������� �� ���� � ������� �� 1 �� 9." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
void queuePop(MyQueue& myQueue) {
    if (!myQueue.empty()) 
        std::cout << "������� �� ������� �����: " << myQueue.pop() << " ��������.\n";    
    else 
        std::cout << "����� �������.\n";    
}
void queuePeek(MyQueue& myQueue) {
    if (!myQueue.empty()) 
        std::cout << "������� �� ������� �����: " << myQueue.peek() << std::endl;    
    else 
        std::cout << "����� �������.\n";    
}
void queueEmpty(MyQueue& myQueue) {
    std::cout << (myQueue.empty() ? "����� �������.\n" : "����� ������ ��������.\n");
}

void caseFourLab4() {
    MyQueue myQueue;
    std::vector<std::string> queueMenuItems = {
        "1. Push",
        "2. Pop",
        "3. Peek",
        "4. Empty",
        "0. �����"
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
//5 ����
void caseFiveLab4()
{
    std::string inputString;
    std::cout << "������ ����������� ����� (������� �� 1 �� 30 �������, ���� ��� �����, ����� �� �������� �����): ";
    std::cin >> inputString;

    // �������� ��������
    if (checkCin((inputString.length() < 1 || inputString.length() > 30),
        "�������: ����������� ������� �����.\n"))
        return;

    // �������� �� �������� �������
    bool isValidCharacter = true;
    for (char c : inputString) {
        if (!std::isdigit(c) && (c < 'a' || c > 'z') && c != '[' && c != ']') {
            isValidCharacter = false;
            break;
        }
    }

    if (!isValidCharacter) {
        std::cout << "�������: ����� ������ ���������� �������.\n";
        return;
    }

    // ��������� �����������
    try {
        std::string decodedString = decodeString(inputString);
        std::cout << "����������� �����: " << decodedString << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "������� ������� ��� ����������: " << e.what() << std::endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//6 ����
void caseSixLab4() {
    std::vector<std::string> tokens;
    std::string token;
    std::cout << "������ �������� ������, ������� �������� (�������� ������ 'end'): ";
    while (std::cin >> token && token != "end") {
        tokens.push_back(token);
    }

    // �������� ��������
    if (checkCin((tokens.size() < 1 || tokens.size() > 104), "�������: ����������� ������� ������.\n")) {
        return;
    }

    for (const auto& t : tokens) {
        if (std::isdigit(t[0]) || t[0] == '-' && t.size() > 1) {
            if (std::stoi(t) < -200 || std::stoi(t) > 200) {
                std::cout << "�������: ����� �� ������ �������� [-200, 200].\n";
                return;
            }
        }
        else if (t != "+" && t != "-" && t != "*" && t != "/") {
            std::cout << "�������: �������� �������� '" << t << "'.\n";
            return;
        }
    }

    try {
        int result = evalRPN(tokens);
        std::cout << "��������� ������: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "������� ������� ��� ��������� ������: " << e.what() << std::endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//7 ����
void caseSevenLab4() {
    std::string inputString;
    std::cout << "������ �����, �� ���������� � '(' � ')': ";
    std::cin >> inputString;

    // �������� ��������
    if (inputString.length() > 30000) {
        std::cout << "�������: ����� ���������.\n";
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
        std::cout << "�������: ����� ������ ���������� �������.\n";
        return;
    }

    int result = longestValidParentheses(inputString);
    std::cout << "������� ��������� ������ ����� �������: " << result << std::endl;
}

void Lab_4_Stack() {
    std::vector<std::string> menuItems = {
        "1. ����� �����\n",
        "2. ����� �������� ������ � �������\n",
        "3. ̳�������� ����\n",
        "4. ��������� ����� �������������� �����\n",
        "5. ���������� �����\n",
        "6. ������ �������� �������� �������\n",
        "7. �������� ���� �����\n",
       "0. ����� � ����\n"
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