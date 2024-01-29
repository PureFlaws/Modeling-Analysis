#include "Exercises_5_Lab.h"
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

//1. �� ���� ������
bool isSameTree(TreeNode* p, TreeNode* q) {
    // ���� ������ ����� null, �� ���� �������
    if (p == nullptr && q == nullptr) return true;

    // ���� ���� � ����� null, � ����� �, �� ���� �� �������
    if (p == nullptr || q == nullptr) return false;

    // ���� �������� ����� �� �������, �� ������ �� �������
    if (p->val != q->val) return false;

    // ���������� ���������� �� �� ���� ��������
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
// 2. ���������� ������
bool isMirror(TreeNode* left, TreeNode* right) {
    if (left == nullptr && right == nullptr) return true;
    if (left == nullptr || right == nullptr) return false;
    if (left->val != right->val) return false;
    return isMirror(left->left, right->right) && isMirror(left->right, right->left);
}

bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    return isMirror(root->left, root->right);
}

//3. ����������� ������ ������
TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) return nullptr;
    TreeNode* temp = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(temp);
    return root;
}
//4. K-� ��������� ������� � BST
void kthSmallestHelper(TreeNode* root, int& k, int& res) {
    if (root == nullptr || k <= 0) return;
    kthSmallestHelper(root->left, k, res);
    if (--k == 0) res = root->val;
    kthSmallestHelper(root->right, k, res);
}

int kthSmallest(TreeNode* root, int k) {
    int res = -1;
    kthSmallestHelper(root, k, res);
    return res;
}
//5. ���������� �� ������������ �������� ������
void serializeHelper(TreeNode* root, ostringstream& out, bool isLastLevel, bool roottest) {
    if (!root)
        return;
    else if (!root->left && !root->right && root) {
        out << root->val << " ";
        if (!isLastLevel && !roottest) { // ��������, �� ����� �� � ������ ���������� ����
            out << "null ";
            out << "null ";
        }
    }
    else if (isLastLevel)
        return;
    else if (root)
    {
        out << root->val << " ";
        // ���������, �� � ��������� ����� �������
        bool nextLevelIsLast = !(root->left || root->right);
        bool roottest = root->right == nullptr;
        serializeHelper(root->left, out, nextLevelIsLast, roottest);
        nextLevelIsLast = root->right == nullptr;
        serializeHelper(root->right, out, nextLevelIsLast, roottest);
    }
}

string serialize(TreeNode* root) {
    ostringstream out;
    serializeHelper(root, out, false, false); // ��������� �� �� �����, �� �� ������� �����
    string result = out.str();
    if (!result.empty() && result[result.size() - 1] == ' ') {
        result.pop_back(); // ��������� ���������� ������
    }
    return result;
}

TreeNode* deserializeHelper(istringstream& in) {
    string val;
    in >> val;
    if (val == "null") return nullptr;

    TreeNode* root = nullptr;
    try {
        int num = stoi(val);
        root = new TreeNode(num);
    }
    catch (const std::invalid_argument& e) {
        // ������� �������, ���� val �� ���� ���� ����������� � �����
        //cout << "�������: ����������� �������� ����� \"" << val << "\"." << endl;
        return nullptr;
    }
    catch (const std::out_of_range& e) {
        // ������� �������, ���� ����� �������� �� ��� int
        cout << "�������: �������� ����� \"" << val << "\" �������� �� ��� �������� int." << endl;
        return nullptr;
    }

    root->left = deserializeHelper(in);
    root->right = deserializeHelper(in);
    return root;
}

TreeNode* deserialize(string data) {
    istringstream in(data);
    return deserializeHelper(in);
}
//6. ������� ������ ����������� ���� �����
int maxPathSumHelper(TreeNode* root, int& maxSum) {
    if (root == nullptr) return 0;
    int left = max(0, maxPathSumHelper(root->left, maxSum));
    int right = max(0, maxPathSumHelper(root->right, maxSum));
    maxSum = max(maxSum, left + right + root->val);
    return max(left, right) + root->val;
}

int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    maxPathSumHelper(root, maxSum);
    return maxSum;
}
//7. ������ �������� ������

int minCameraCoverHelper(TreeNode* root, int& cameras) {
    if (!root) return MONITORED_NOCAM;
    int left = minCameraCoverHelper(root->left, cameras);
    int right = minCameraCoverHelper(root->right, cameras);
    if (left == NOT_MONITORED || right == NOT_MONITORED) {
        cameras++;
        return MONITORED_WITHCAM;
    }
    return left == MONITORED_WITHCAM || right == MONITORED_WITHCAM ? MONITORED_NOCAM : NOT_MONITORED;
}

int minCameraCover(TreeNode* root) {
    int cameras = 0;
    if (minCameraCoverHelper(root, cameras) == NOT_MONITORED) cameras++;
    return cameras;
}
//8. ������������ ����� �������� ������
void verticalOrderTraversalHelper(TreeNode* root, int col, int row, map<int, map<int, vector<int>>>& nodes) {
    if (root == nullptr) return;
    nodes[col][row].push_back(root->val);
    verticalOrderTraversalHelper(root->left, col - 1, row + 1, nodes);
    verticalOrderTraversalHelper(root->right, col + 1, row + 1, nodes);
}

std::vector<std::vector<int>> verticalOrderTraversal(TreeNode* root) {
    std::map<int, std::map<int, std::vector<int>>> nodes;
    verticalOrderTraversalHelper(root, 0, 0, nodes);

    std::vector<std::vector<int>> result;
    for (auto& col : nodes) {
        std::vector<int> col_vals;
        for (auto& row : col.second) {
            std::sort(row.second.begin(), row.second.end());
            col_vals.insert(col_vals.end(), row.second.begin(), row.second.end());
        }
        result.push_back(col_vals);
    }
    return result;
}
//9. ³������� ������ ���� ������������ ������ (Preorder Traversal)
TreeNode* recoverFromPreorder(string S) {
    int pos = 0;
    return recover(S, pos, 0);
}

TreeNode* recover(const string& S, int& pos, int depth) {
    if (pos >= S.size()) {
        return nullptr;
    }

    int d = 0;
    while (pos + d < S.size() && S[pos + d] == '-') {
        d++;
    }
    if (d != depth) {
        return nullptr;
    }

    int nextPos = pos + d;
    while (nextPos < S.size() && S[nextPos] != '-') {
        nextPos++;
    }
    
    int val = stoi(S.substr(pos + d, nextPos - pos - d));
    pos = nextPos;

    TreeNode* node = new TreeNode(val);
    node->left = recover(S, pos, depth + 1);
    node->right = recover(S, pos, depth + 1);
    return node;
}

//������� ����
//////////////////////////////////////////////////////////////////////////////////////////
//1 ����
void caseOneLab5()
{
    cout << "������ �������� ������� �������� ������ (����� �����, �������������� 'null' ��� ������� �����): ";
    string tree1;
    getline(cin >> ws, tree1); // ws ��� �������� ������ �����

    cout << "������ �������� ������� �������� ������ (����� �����, �������������� 'null' ��� ������� �����): ";
    string tree2;
    getline(cin >> ws, tree2);

    // ���������: ������� ����� � ���� ������� ����������� � ������� [0, 100]
    int nodeCount1 = count(tree1.begin(), tree1.end(), ' ') + 1;
    int nodeCount2 = count(tree2.begin(), tree2.end(), ' ') + 1;

    if (nodeCount1 > 100 || nodeCount2 > 100) {
        cout << "�������: ������� ����� �������� ���������� ������� [0, 100]." << endl;
        return;
    }

    TreeNode* p = createTree(tree1); // ������� ��� ��������� ������ � �����
    TreeNode* q = createTree(tree2); // ���������

    bool result = isSameTree(p, q);
    cout << "������ �������: " << (result ? "���" : "ͳ") << endl;

    deleteTree(p); // ������� ��� ��������� ������
    deleteTree(q); // ���������
}
//////////////////////////////////////////////////////////////////////////////////////////
//2 ����
void caseTwoLab5()
{
    cout << "������ �������� �������� ������ (����� �����, �������������� 'null' ��� ������� �����): ";
    string treeData;
    getline(cin >> ws, treeData);

    // �������� ������� �����
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 ���� �� ������� ������� �� ������������ �������
    if (nodeCount > 1000) {
        cout << "�������: ʳ������ ����� �������� 1000." << endl;
        return;
    }

    // �������� �������� ������� �����
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null") {
            int val = stoi(value);
            if (val < -10000 || val > 10000) {
                cout << "�������: �������� ����� " << val << " ���� ��������� [-10000, 10000]." << endl;
                return;
            }
        }
    }

    TreeNode* root = createTree(treeData);
    bool result = isSymmetric(root);
    cout << "������ ����������: " << (result ? "���" : "ͳ") << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//3 ����
void caseThreeLab5()
{
    cout << "������ �������� �������� ������ ��� ������������ (����� �����, �������������� 'null' ��� ������� �����): ";
    string treeData;
    getline(cin >> ws, treeData);

    // �������� ������� �����
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 ���� �� ������� ������� �� ������������ �������
    if (nodeCount > 100) {
        cout << "�������: ʳ������ ����� �������� 100." << endl;
        return;
    }

    // �������� �������� ������� �����
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null") {
            int val = stoi(value);
            if (val < -100 || val > 100) {
                cout << "�������: �������� ����� " << val << " ���� ��������� [-100, 100]." << endl;
                return;
            }
        }
    }

    TreeNode* root = createTree(treeData);
    root = invertTree(root);
    cout << "����������� ������ ��������." << endl;
    printTree(root);
    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//4 ����
void caseFourLab5()
{
    cout << "������ �������� �������� ������ ������ (����� �����, �������������� 'null' ��� ������� �����): ";
    string treeData;
    getline(cin >> ws, treeData);

    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1;
    if (nodeCount > 10000) {
        cout << "�������: ʳ������ ����� �������� 10 000." << endl;
        return;
    }

    TreeNode* root = createTree(treeData);
    int k;
    cout << "������ k (1 <= k <= " << nodeCount << "): ";
    cin >> k;
    if (k < 1 || k > nodeCount) {
        cout << "�������: �������� k ���� ���������." << endl;
        deleteTree(root);
        return;
    }

    int res = kthSmallest(root, k);
    cout << k << "-� ��������� ������� � BST: " << res << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//5 ����
void caseFiveLab5()
{
    cout << "������ ����������� ������ ������ (����� �����, �������������� 'null' ��� ������� �����): ";
    string treeData;
    getline(cin >> ws, treeData);

    // �������� ������� �����
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 ���� �� ������� ������� �� ������������ �������
    if (nodeCount > 10000) {
        cout << "�������: ʳ������ ����� �������� 10 000." << endl;
        return;
    }

    // �������� �������� ������� �����
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null") {
            int val = stoi(value);
            if (val < -1000 || val > 1000) {
                cout << "�������: �������� ����� " << val << " ���� ��������� [-1000, 1000]." << endl;
                return;
            }
        }
    }

    TreeNode* root = deserialize(treeData);
    string serializedTree = serialize(root);
    cout << "����������� ������: " << serializedTree << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//6 ����
void caseSixLab5()
{
    cout << "������ ����������� ������ ������ (����� �����, �������������� 'null' ��� ������� �����): ";
    string treeData;
    getline(cin >> ws, treeData);

    // �������� ������� �����
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 ���� �� ������� ������� �� ������������ �������
    if (nodeCount > 30000) {
        cout << "�������: ʳ������ ����� �������� 30 000." << endl;
        return;
    }

    // �������� �������� ������� �����
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null") {
            int val = stoi(value);
            if (val < -1000 || val > 1000) {
                cout << "�������: �������� ����� " << val << " ���� ��������� [-1000, 1000]." << endl;
                return;
            }
        }
    }

    TreeNode* root = deserialize(treeData);
    int maxPathSumValue = maxPathSum(root);
    cout << "����������� ���� ����� � �������� �����: " << maxPathSumValue << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//7 ����
void caseSevenLab5() {
    cout << "������ ����������� ������ ������ (����� �����, �������������� 'null' ��� ������� �����): ";
    string treeData;
    getline(cin >> ws, treeData);

    // �������� ������� �����
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 ���� �� ������� ������� �� ������������ �������
    if (nodeCount > 1000) {
        cout << "�������: ʳ������ ����� �������� 1000." << endl;
        return;
    }

    // �������� ������� �����
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null" && stoi(value) != 0) {
            cout << "�������: �������� ����� �� ������� 0." << endl;
            return;
        }
    }

    TreeNode* root = deserialize(treeData);
    int cameraCount = minCameraCover(root);
    cout << "̳������� ������� ����� ��� ���������� ��� ����� ������: " << cameraCount << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//8 ����
void caseEightLab5() {
    cout << "������ �������� �������� ������ (����� �����, �������������� 'null' ��� ������� �����): ";
    string treeData;
    getline(cin >> ws, treeData);

    TreeNode* root = createTree(treeData);

    // �������� ������� �����
    if (!root || count(treeData.begin(), treeData.end(), ' ') + 1 > 1000) {
        cout << "�������: ʳ������ ����� �������� 1000 ��� ������ ������." << endl;
        // ���'������ �������� ���'���, ���� ������ ���� ��������
        deleteTree(root);
        return;
    }

    vector<vector<int>> result = verticalOrderTraversal(root);
    cout << "������������ ����� �������� ������: " << endl;
    for (const auto& col : result) {
        for (int val : col) {
            cout << val << " ";
        }
        cout << endl;
    }

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//9 ����
void caseNineLab5() {
    cout << "Enter the traversal of the tree in Preorder Traversal format: ";
    string traversal;
    getline(cin >> ws, traversal);

    int nodeCount = count(traversal.begin(), traversal.end(), '-') + 1;
    if (nodeCount > 1000) {
        cout << "Error: The number of nodes exceeds 1000." << endl;
        return;
    }

    TreeNode* root = recoverFromPreorder(traversal);
    cout << "The tree has been restored." << endl;

    string serialized = serialize(root);
    cout << "Serialized tree: " << serialized << endl;

    deleteTree(root);
}

void Lab_5() {
    SetConsoleOutputCP(1251); // ������������ ��������� ������� ��� ������
    SetConsoleCP(1251); // ������������ ��������� ������� ��� �����

    std::vector<std::string> menuItems = {
        "1. �� ���� ������",
        "2. ���������� ������",
        "3. ����������� ������ ������",
        "4. K-� ��������� ������� � BST",
        "5. ���������� �� ������������ �������� ������",
        "6. ������� ������ ����������� ���� �����",
        "7. ������ �������� ������",
        "8. ������������ ����� �������� ������",
        "9. ³������� ������ ���� ������������ ������",
        "0. ����� � ����"
    };

    std::vector<std::function<void()>> actions = {
        []() { caseOneLab5(); },
        []() { caseTwoLab5(); },
        []() { caseThreeLab5(); },
        []() { caseFourLab5(); },
        []() { caseFiveLab5(); },
        []() { caseSixLab5(); },
        []() { caseSevenLab5(); },
        []() { caseEightLab5(); },
        []() { caseNineLab5(); }
    };

    DisplayMenu(menuItems, actions);

    return;
}