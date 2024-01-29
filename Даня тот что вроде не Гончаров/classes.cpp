#include "classes.h"

void printList(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << std::endl;
}

ListNode* createList(const std::vector<int>& vals) {
    ListNode* head = nullptr;
    ListNode* current = nullptr;
    for (int val : vals) {
        if (!head) {
            head = new ListNode(val);
            current = head;
        }
        else {
            current->next = new ListNode(val);
            current = current->next;
        }
    }
    return head;
}

void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void deleteNode(ListNode* node, ListNode* prevNode) {
    if (node == nullptr) return;

    // Якщо вузол не є останнім, копіюємо дані з наступного вузла
    if (node->next != nullptr) {
        ListNode* temp = node->next;
        node->val = temp->val;
        node->next = temp->next;
        delete temp;
    }
    else {
        // Якщо вузол останній, просто видаляємо його
        if (prevNode != nullptr) {
            prevNode->next = nullptr;
        }
        delete node;
    }
}

// Функція для перевертання списку
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head != nullptr) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

TreeNode* createTree(const string& data) {
    if (data.empty()) return nullptr;

    stringstream ss(data);
    string item;
    getline(ss, item, ' ');
    if (item == "null") return nullptr; // Якщо корінь дерева - null, повертаємо nullptr

    TreeNode* root = new TreeNode(stoi(item));

    queue<TreeNode**> nodeQueue; // Зберігаємо вказівники на вказівники вузлів
    nodeQueue.push(&root->left);
    nodeQueue.push(&root->right);

    while (!nodeQueue.empty() && getline(ss, item, ' ')) {
        TreeNode** ppNode = nodeQueue.front(); // Отримуємо вказівник на вказівник на вузол
        nodeQueue.pop();

        if (item != "null") {
            *ppNode = new TreeNode(stoi(item)); // Створюємо новий вузол
            nodeQueue.push(&((*ppNode)->left));
            nodeQueue.push(&((*ppNode)->right));
        }
    }
    return root;
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Допоміжна функція для виведення дерева в консоль
void printTree(TreeNode* root) {
    if (!root) {
        std::cout << "Дерево порожнє." << std::endl;
        return;
    }

    std::queue<TreeNode*> nodesQueue;
    std::queue<int> levelsQueue;
    nodesQueue.push(root);
    levelsQueue.push(0);
    int currentLevel = 0;
    bool allNullsOnLevel = true;

    while (!nodesQueue.empty()) {
        TreeNode* current = nodesQueue.front();
        int level = levelsQueue.front();
        nodesQueue.pop();
        levelsQueue.pop();

        if (level > currentLevel) {
            currentLevel = level;
            if (allNullsOnLevel) {
                break; // Break if the entire level has only nulls
            }
            allNullsOnLevel = true; // Reset for next level
        }

        if (current) {
            std::cout << current->val << " ";
            allNullsOnLevel = false; // We found a non-null node on this level
            nodesQueue.push(current->left);
            nodesQueue.push(current->right);
            levelsQueue.push(level + 1);
            levelsQueue.push(level + 1);
        }
        else if (!allNullsOnLevel) {
            // Only print nulls if there are non-null nodes on this level
            std::cout << "null ";
        }
    }
    std::cout << std::endl;
}


bool checkCin(bool pCheckCondition, string pErrorCout)
{
    if (pCheckCondition) {
        cin.clear(); // Очищуємо будь-які помилки вводу
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ігноруємо залишковий ввід
        cout << pErrorCout << endl;
        return true;
    }
    return false;
}

// Перевантажена версія функції з двома умовними перевіряннями
// Також для написананя можна використати параметризацыю за замовчуванням
// bool pCheckConditionSecond = false, const std::string& pErrorCoutSecond = "")
// В тому ж C# це все можна зробити за допомогою опціонального параметру "?"
// Проте в с++ нажаль його немає((((
bool checkCin(bool pCheckConditionFirst, const std::string& pErrorCoutFirst,
    bool pCheckConditionSecond, const std::string& pErrorCoutSecond) {
    if (pCheckConditionFirst) {
        std::cin.clear(); // Очищуємо будь-які помилки вводу
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ігноруємо залишковий ввід
        std::cout << pErrorCoutFirst << std::endl;
        return true;
    }
    else if (pCheckConditionSecond) {
        std::cin.clear(); // Очищуємо будь-які помилки вводу
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ігноруємо залишковий ввід
        std::cout << pErrorCoutSecond << std::endl;
        return true;
    }
    return false;
}