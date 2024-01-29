#include "Exercises_5_Lab.h"
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

//1. Те саме дерево
bool isSameTree(TreeNode* p, TreeNode* q) {
    // Якщо обидва вузли null, то вони однакові
    if (p == nullptr && q == nullptr) return true;

    // Якщо один з вузлів null, а інший ні, то вони не однакові
    if (p == nullptr || q == nullptr) return false;

    // Якщо значення вузлів не однакові, то дерева не однакові
    if (p->val != q->val) return false;

    // Рекурсивно перевіряємо ліві та праві піддерева
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}
// 2. Симетричне дерево
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

//3. Інвертувати бінарне дерево
TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) return nullptr;
    TreeNode* temp = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(temp);
    return root;
}
//4. K-й найменший елемент у BST
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
//5. Серіалізація та десеріалізація бінарного дерева
void serializeHelper(TreeNode* root, ostringstream& out, bool isLastLevel, bool roottest) {
    if (!root)
        return;
    else if (!root->left && !root->right && root) {
        out << root->val << " ";
        if (!isLastLevel && !roottest) { // Перевірка, чи вузол не є вузлом останнього рівня
            out << "null ";
            out << "null ";
        }
    }
    else if (isLastLevel)
        return;
    else if (root)
    {
        out << root->val << " ";
        // Визначаємо, чи є наступний рівень останнім
        bool nextLevelIsLast = !(root->left || root->right);
        bool roottest = root->right == nullptr;
        serializeHelper(root->left, out, nextLevelIsLast, roottest);
        nextLevelIsLast = root->right == nullptr;
        serializeHelper(root->right, out, nextLevelIsLast, roottest);
    }
}

string serialize(TreeNode* root) {
    ostringstream out;
    serializeHelper(root, out, false, false); // Початково ми не знаємо, чи це останній рівень
    string result = out.str();
    if (!result.empty() && result[result.size() - 1] == ' ') {
        result.pop_back(); // Видалення останнього пробілу
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
        // Обробка випадку, коли val не може бути перетворено в число
        //cout << "Помилка: Неправильне значення вузла \"" << val << "\"." << endl;
        return nullptr;
    }
    catch (const std::out_of_range& e) {
        // Обробка випадку, коли число виходить за межі int
        cout << "Помилка: Значення вузла \"" << val << "\" виходить за межі діапазону int." << endl;
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
//6. Двійкове дерево Максимальна сума шляху
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
//7. Камери бінарного дерева

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
//8. Вертикальний обхід бінарного дерева
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
//9. Відновити дерево після попереднього обходу (Preorder Traversal)
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

//Функції меню
//////////////////////////////////////////////////////////////////////////////////////////
//1 кейс
void caseOneLab5()
{
    cout << "Введіть елементи першого бінарного дерева (через пробіл, використовуйте 'null' для відсутніх вузлів): ";
    string tree1;
    getline(cin >> ws, tree1); // ws для очищення буфера вводу

    cout << "Введіть елементи другого бінарного дерева (через пробіл, використовуйте 'null' для відсутніх вузлів): ";
    string tree2;
    getline(cin >> ws, tree2);

    // Обмеження: кількість вузлів в обох деревах знаходиться в діапазоні [0, 100]
    int nodeCount1 = count(tree1.begin(), tree1.end(), ' ') + 1;
    int nodeCount2 = count(tree2.begin(), tree2.end(), ' ') + 1;

    if (nodeCount1 > 100 || nodeCount2 > 100) {
        cout << "Помилка: кількість вузлів перевищує дозволений діапазон [0, 100]." << endl;
        return;
    }

    TreeNode* p = createTree(tree1); // Функція для створення дерева з рядка
    TreeNode* q = createTree(tree2); // Аналогічно

    bool result = isSameTree(p, q);
    cout << "Дерева однакові: " << (result ? "Так" : "Ні") << endl;

    deleteTree(p); // Функція для видалення дерева
    deleteTree(q); // Аналогічно
}
//////////////////////////////////////////////////////////////////////////////////////////
//2 кейс
void caseTwoLab5()
{
    cout << "Введіть елементи бінарного дерева (через пробіл, використовуйте 'null' для відсутніх вузлів): ";
    string treeData;
    getline(cin >> ws, treeData);

    // Перевірка кількості вузлів
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 тому що останній елемент не відокремлений пробілом
    if (nodeCount > 1000) {
        cout << "Помилка: Кількість вузлів перевищує 1000." << endl;
        return;
    }

    // Перевірка діапазону значень вузлів
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null") {
            int val = stoi(value);
            if (val < -10000 || val > 10000) {
                cout << "Помилка: Значення вузла " << val << " поза діапазоном [-10000, 10000]." << endl;
                return;
            }
        }
    }

    TreeNode* root = createTree(treeData);
    bool result = isSymmetric(root);
    cout << "Дерево симетричне: " << (result ? "Так" : "Ні") << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//3 кейс
void caseThreeLab5()
{
    cout << "Введіть елементи бінарного дерева для інвертування (через пробіл, використовуйте 'null' для відсутніх вузлів): ";
    string treeData;
    getline(cin >> ws, treeData);

    // Перевірка кількості вузлів
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 тому що останній елемент не відокремлений пробілом
    if (nodeCount > 100) {
        cout << "Помилка: Кількість вузлів перевищує 100." << endl;
        return;
    }

    // Перевірка діапазону значень вузлів
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null") {
            int val = stoi(value);
            if (val < -100 || val > 100) {
                cout << "Помилка: Значення вузла " << val << " поза діапазоном [-100, 100]." << endl;
                return;
            }
        }
    }

    TreeNode* root = createTree(treeData);
    root = invertTree(root);
    cout << "Інвертоване дерево створено." << endl;
    printTree(root);
    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//4 кейс
void caseFourLab5()
{
    cout << "Введіть елементи бінарного дерева пошуку (через пробіл, використовуйте 'null' для відсутніх вузлів): ";
    string treeData;
    getline(cin >> ws, treeData);

    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1;
    if (nodeCount > 10000) {
        cout << "Помилка: Кількість вузлів перевищує 10 000." << endl;
        return;
    }

    TreeNode* root = createTree(treeData);
    int k;
    cout << "Введіть k (1 <= k <= " << nodeCount << "): ";
    cin >> k;
    if (k < 1 || k > nodeCount) {
        cout << "Помилка: Значення k поза діапазоном." << endl;
        deleteTree(root);
        return;
    }

    int res = kthSmallest(root, k);
    cout << k << "-й найменший елемент у BST: " << res << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//5 кейс
void caseFiveLab5()
{
    cout << "Введіть серіалізоване бінарне дерево (через пробіл, використовуйте 'null' для відсутніх вузлів): ";
    string treeData;
    getline(cin >> ws, treeData);

    // Перевірка кількості вузлів
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 тому що останній елемент не відокремлений пробілом
    if (nodeCount > 10000) {
        cout << "Помилка: Кількість вузлів перевищує 10 000." << endl;
        return;
    }

    // Перевірка діапазону значень вузлів
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null") {
            int val = stoi(value);
            if (val < -1000 || val > 1000) {
                cout << "Помилка: Значення вузла " << val << " поза діапазоном [-1000, 1000]." << endl;
                return;
            }
        }
    }

    TreeNode* root = deserialize(treeData);
    string serializedTree = serialize(root);
    cout << "Серіалізоване дерево: " << serializedTree << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//6 кейс
void caseSixLab5()
{
    cout << "Введіть серіалізоване бінарне дерево (через пробіл, використовуйте 'null' для відсутніх вузлів): ";
    string treeData;
    getline(cin >> ws, treeData);

    // Перевірка кількості вузлів
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 тому що останній елемент не відокремлений пробілом
    if (nodeCount > 30000) {
        cout << "Помилка: Кількість вузлів перевищує 30 000." << endl;
        return;
    }

    // Перевірка діапазону значень вузлів
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null") {
            int val = stoi(value);
            if (val < -1000 || val > 1000) {
                cout << "Помилка: Значення вузла " << val << " поза діапазоном [-1000, 1000]." << endl;
                return;
            }
        }
    }

    TreeNode* root = deserialize(treeData);
    int maxPathSumValue = maxPathSum(root);
    cout << "Максимальна сума шляху у бінарному дереві: " << maxPathSumValue << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//7 кейс
void caseSevenLab5() {
    cout << "Введіть серіалізоване бінарне дерево (через пробіл, використовуйте 'null' для відсутніх вузлів): ";
    string treeData;
    getline(cin >> ws, treeData);

    // Перевірка кількості вузлів
    int nodeCount = count(treeData.begin(), treeData.end(), ' ') + 1; // +1 тому що останній елемент не відокремлений пробілом
    if (nodeCount > 1000) {
        cout << "Помилка: Кількість вузлів перевищує 1000." << endl;
        return;
    }

    // Перевірка значень вузлів
    stringstream ss(treeData);
    string value;
    while (getline(ss, value, ' ')) {
        if (value != "null" && stoi(value) != 0) {
            cout << "Помилка: Значення вузла не дорівнює 0." << endl;
            return;
        }
    }

    TreeNode* root = deserialize(treeData);
    int cameraCount = minCameraCover(root);
    cout << "Мінімальна кількість камер для моніторингу всіх вузлів дерева: " << cameraCount << endl;

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//8 кейс
void caseEightLab5() {
    cout << "Введіть елементи бінарного дерева (через пробіл, використовуйте 'null' для відсутніх вузлів): ";
    string treeData;
    getline(cin >> ws, treeData);

    TreeNode* root = createTree(treeData);

    // Перевірка кількості вузлів
    if (!root || count(treeData.begin(), treeData.end(), ' ') + 1 > 1000) {
        cout << "Помилка: Кількість вузлів перевищує 1000 або дерево порожнє." << endl;
        // Пам'ятайте очистити пам'ять, якщо дерево було створено
        deleteTree(root);
        return;
    }

    vector<vector<int>> result = verticalOrderTraversal(root);
    cout << "Вертикальний обхід бінарного дерева: " << endl;
    for (const auto& col : result) {
        for (int val : col) {
            cout << val << " ";
        }
        cout << endl;
    }

    deleteTree(root);
}
//////////////////////////////////////////////////////////////////////////////////////////
//9 кейс
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
    SetConsoleOutputCP(1251); // Встановлюємо кодування сторінки для виводу
    SetConsoleCP(1251); // Встановлюємо кодування сторінки для вводу

    std::vector<std::string> menuItems = {
        "1. Те саме дерево",
        "2. Симетричне дерево",
        "3. Інвертувати бінарне дерево",
        "4. K-й найменший елемент у BST",
        "5. Серіалізація та десеріалізація бінарного дерева",
        "6. Двійкове дерево Максимальна сума шляху",
        "7. Камери бінарного дерева",
        "8. Вертикальний обхід бінарного дерева",
        "9. Відновити дерево після попереднього обходу",
        "0. Вихід з меню"
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