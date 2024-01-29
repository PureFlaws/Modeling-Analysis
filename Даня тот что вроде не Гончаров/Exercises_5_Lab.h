#pragma once

#include "classes.h"
#include "Menu.h"

using namespace std;

//1. Те саме дерево
bool isSameTree(TreeNode* p, TreeNode* q);

// 2. Симетричне дерево
bool isMirror(TreeNode* left, TreeNode* right);
bool isSymmetric(TreeNode* root);

//3. Інвертувати бінарне дерево
TreeNode* invertTree(TreeNode* root);

//4. K-й найменший елемент у BST
void kthSmallestHelper(TreeNode* root, int& k, int& res);
int kthSmallest(TreeNode* root, int k);

//5. Серіалізація та десеріалізація бінарного дерева
void serializeHelper(TreeNode* root, ostringstream& out, bool isLastLevel, bool roottest);
string serialize(TreeNode* root);
TreeNode* deserializeHelper(istringstream& in);
TreeNode* deserialize(string data);

//6. Двійкове дерево Максимальна сума шляху
int maxPathSumHelper(TreeNode* root, int& maxSum);
int maxPathSum(TreeNode* root);

//7. Камери бінарного дерева
enum Camera { NOT_MONITORED, MONITORED_NOCAM, MONITORED_WITHCAM };
int minCameraCoverHelper(TreeNode* root, int& cameras);
int minCameraCover(TreeNode* root);

//8. Вертикальний обхід бінарного дерева
std::vector<std::vector<int>> verticalOrderTraversal(TreeNode* root);

//9. Відновити дерево після попереднього обходу (Preorder Traversal)
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
