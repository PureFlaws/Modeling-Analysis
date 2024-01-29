#include "classes.h"
#include "Menu.h"

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
bool isValid(const std::string& s);
//2 ����� �������� ������ � ������� (Inorder Traversal)

// �������� ������� ��� ������������ ������
void inorderTraversalHelper(TreeNode* root, std::vector<int>& result);

// ������� ��� ��������� ������
void inorderTraversal(TreeNode* root, std::vector<int>& result);
TreeNode* insertLevelOrder(const std::vector<int>& values, int i);


//3 ̳�������� ����
class MinStack {
private:
    std::stack<int> s1; // �������� ���� ��� ��������� ��������
    std::stack<int> s2; // ��������� ���� ��� ��������� ��������� �������

public:
    MinStack() {}

    void push(int val) {
        s1.push(val);
        if (s2.empty() || val <= getMin()) s2.push(val);
    }

    void pop() {
        if (s1.top() == getMin()) s2.pop();
        s1.pop();
    }

    int top() {
        return s1.top();
    }

    int getMin() {
        return s2.top();
    }
    // ������ ����� ����� empty
    bool empty() {
        return s1.empty();
    }
};

//4 ��������� ����� �������������� �����
class MyQueue {
private:
    std::stack<int> stack1;
    std::stack<int> stack2;

    // ������� �������� � stack1 �� stack2
    void transferStack() {
        while (!stack1.empty()) {
            stack2.push(stack1.top());
            stack1.pop();
        }
    }

public:
    MyQueue() {}

    void push(int x) {
        stack1.push(x);
    }

    int pop() {
        if (stack2.empty()) {
            transferStack();
        }
        int top = stack2.top();
        stack2.pop();
        return top;
    }

    int peek() {
        if (stack2.empty()) {
            transferStack();
        }
        return stack2.top();
    }

    bool empty() {
        return stack1.empty() && stack2.empty();
    }
};

//5 ���������� �����
std::string decodeString(const std::string& s);

//6 ������ �������� �������� �������
int evalRPN(const std::vector<std::string>& tokens);

//7 �������� ���� �����
int longestValidParentheses(const std::string& s);

//������� ����
//////////////////////////////////////////////////////////////////////////////////////////
//1 ����
void caseOneLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//2 ����
void caseTwoLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//3 ����
void minStackPush(MinStack& minStack);
void minStackPop(MinStack& minStack);
void minStackTop(MinStack& minStack);
void minStackGetMin(MinStack& minStack);
void caseThreeLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//4 ����
void queuePush(MyQueue& myQueue);
void queuePop(MyQueue& myQueue);
void queuePeek(MyQueue& myQueue);
void queueEmpty(MyQueue& myQueue);

void caseFourLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//5 ����
void caseFiveLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//6 ����
void caseSixLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//7 ����
void caseSevenLab4();

void Lab_4_Stack();