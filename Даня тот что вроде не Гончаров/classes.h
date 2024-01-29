#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <queue>

#include"windows.h"

using namespace std;

#undef max

//��������(���������� ���������) ����� �����
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void printList(ListNode* head);
ListNode* createList(const std::vector<int>& vals);
void deleteList(ListNode* head);
void deleteNode(ListNode* node, ListNode* prevNode);
// ������� ��� ������������ ������
ListNode* reverseList(ListNode* head);

// ���������� ��������� ����� �������� ������
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
TreeNode* createTree(const string& data);
void deleteTree(TreeNode* root);
void printTree(TreeNode* root);

bool checkCin(bool pCheckCondition, string pErrorCout);
// ������������� ����� ������� � ����� �������� ������������
bool checkCin(bool pCheckConditionFirst, const std::string& pErrorCoutFirst,
    bool pCheckConditionSecond, const std::string& pErrorCoutSecond);