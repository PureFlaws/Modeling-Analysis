#include "classes.h"
#include "Menu.h"

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

//1 Âàë³äí³ äóæêè
bool isValid(const std::string& s);
//2 Îáõ³ä á³íàðíîãî äåðåâà â ïîðÿäêó (Inorder Traversal)

// Äîïîì³æíà ôóíêö³ÿ äëÿ ðåêóðñèâíîãî îáõîäó
void inorderTraversalHelper(TreeNode* root, std::vector<int>& result);

// Ôóíêö³ÿ äëÿ âèêîíàííÿ îáõîäó
void inorderTraversal(TreeNode* root, std::vector<int>& result);
TreeNode* insertLevelOrder(const std::vector<int>& values, int i);


//3 Ì³í³ìàëüíèé ñòåê
class MinStack {
private:
    std::stack<int> s1; // îñíîâíèé ñòåê äëÿ çáåð³ãàííÿ åëåìåíò³â
    std::stack<int> s2; // äîïîì³æíèé ñòåê äëÿ çáåð³ãàííÿ ì³í³ìàëüíèõ çíà÷åíü

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
    // Äîäàºìî íîâèé ìåòîä empty
    bool empty() {
        return s1.empty();
    }
};

//4 Ðåàë³çóéòå ÷åðãó âèêîðèñòîâóþ÷è ñòåêè
class MyQueue {
private:
    std::stack<int> stack1;
    std::stack<int> stack2;

    // Ïåðåì³ùàº åëåìåíòè ç stack1 äî stack2
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

//5 Äåêîäóâàòè ðÿäîê
std::string decodeString(const std::string& s);

//6 Îö³í³òü çâîðîòíó ïîëüñüêó íîòàö³þ
int evalRPN(const std::vector<std::string>& tokens);

//7 Íàéäîâø³ ä³éñí³ äóæêè
int longestValidParentheses(const std::string& s);

//Ôóíêö³¿ ìåíþ
//////////////////////////////////////////////////////////////////////////////////////////
//1 êåéñ
void caseOneLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//2 êåéñ
void caseTwoLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//3 êåéñ
void minStackPush(MinStack& minStack);
void minStackPop(MinStack& minStack);
void minStackTop(MinStack& minStack);
void minStackGetMin(MinStack& minStack);
void caseThreeLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//4 êåéñ
void queuePush(MyQueue& myQueue);
void queuePop(MyQueue& myQueue);
void queuePeek(MyQueue& myQueue);
void queueEmpty(MyQueue& myQueue);

void caseFourLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//5 êåéñ
void caseFiveLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//6 êåéñ
void caseSixLab4();
//////////////////////////////////////////////////////////////////////////////////////////
//7 êåéñ
void caseSevenLab4();

void Lab_4_Stack();
