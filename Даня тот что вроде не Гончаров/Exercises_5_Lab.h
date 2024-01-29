#pragma once

#include "classes.h"
#include "Menu.h"

using namespace std;

//1. �� ���� ������
bool isSameTree(TreeNode* p, TreeNode* q);

// 2. ���������� ������
bool isMirror(TreeNode* left, TreeNode* right);
bool isSymmetric(TreeNode* root);

//3. ����������� ������ ������
TreeNode* invertTree(TreeNode* root);

//4. K-� ��������� ������� � BST
void kthSmallestHelper(TreeNode* root, int& k, int& res);
int kthSmallest(TreeNode* root, int k);

//5. ���������� �� ������������ �������� ������
void serializeHelper(TreeNode* root, ostringstream& out, bool isLastLevel, bool roottest);
string serialize(TreeNode* root);
TreeNode* deserializeHelper(istringstream& in);
TreeNode* deserialize(string data);

//6. ������� ������ ����������� ���� �����
int maxPathSumHelper(TreeNode* root, int& maxSum);
int maxPathSum(TreeNode* root);

//7. ������ �������� ������
enum Camera { NOT_MONITORED, MONITORED_NOCAM, MONITORED_WITHCAM };
int minCameraCoverHelper(TreeNode* root, int& cameras);
int minCameraCover(TreeNode* root);

//8. ������������ ����� �������� ������
std::vector<std::vector<int>> verticalOrderTraversal(TreeNode* root);

//9. ³������� ������ ���� ������������ ������ (Preorder Traversal)
TreeNode* recoverFromPreorder(std::string traversal);

TreeNode* recover(const std::string& S, int& pos, int depth);

void caseOneLab5();
void caseTwoLab5();
void caseThreeLab5();
void caseFourLab5();
void caseFiveLab5();
void caseSixLab5();
void caseSevenLab5();
void caseEightLab5();
void caseNineLab5();


void Lab_5();
