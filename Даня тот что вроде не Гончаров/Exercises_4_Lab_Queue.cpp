#include "Exercises_4_Lab_Queue.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

//Завдання 1: Перший унікальний символ у рядку
int firstUniqChar(string s) {
    unordered_map<char, int> count;
    for (char c : s) {
        count[c]++;
    }

    for (int i = 0; i < s.length(); i++) {
        if (count[s[i]] == 1) {
            return i;
        }
    }
    return -1;
}

//Завдання 5: Штампування послідовності
bool canStamp(const string& target, int pos, const string& stamp) {
    for (int i = 0; i < stamp.size(); ++i) {
        if (target[pos + i] != '?' && target[pos + i] != stamp[i]) {
            return false;
        }
    }
    return true;
}

void doStamp(string& target, int pos, int len, int& stars) {
    for (int i = 0; i < len; ++i) {
        if (target[pos + i] != '?') {
            target[pos + i] = '?';
            stars++;
        }
    }
}

vector<int> movesToStamp(string stamp, string target) {
    int totalStars = 0;
    vector<int> result;
    vector<bool> visited(target.size(), false);
    bool replaced = true;

    while (totalStars < target.size()) {
        replaced = false;
        for (int i = 0; i <= target.size() - stamp.size(); ++i) {
            if (!visited[i] && canStamp(target, i, stamp)) {
                doStamp(target, i, stamp.size(), totalStars);
                visited[i] = true;
                replaced = true;
                result.push_back(i);
                if (totalStars == target.size()) {
                    break;
                }
            }
        }
        if (!replaced) {
            return vector<int>();
        }
    }

    reverse(result.begin(), result.end());
    return result;
}
//Завдання 6: Максимум плаваючого вікна
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> window;
    vector<int> result;

    for (int i = 0; i < nums.size(); i++) {
        while (!window.empty() && window.front() <= i - k) {
            window.pop_front();
        }
        while (!window.empty() && nums[window.back()] < nums[i]) {
            window.pop_back();
        }
        window.push_back(i);
        if (i >= k - 1) {
            result.push_back(nums[window.front()]);
        }
    }
    return result;
}
//Завдання 7: Обмежена сума підпослідовності

int constrainedSubsetSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    deque<int> q;

    int maxSum = nums[0];
    for (int i = 0; i < n; ++i) {
        if (!q.empty() && q.front() < i - k) {
            q.pop_front();
        }

        dp[i] = nums[i];
        if (!q.empty()) {
            dp[i] = max(dp[i], dp[q.front()] + nums[i]);
        }

        while (!q.empty() && dp[q.back()] < dp[i]) {
            q.pop_back();
        }
        q.push_back(i);

        maxSum = max(maxSum, dp[i]);
    }

    return maxSum;
}

//Функції меню
//////////////////////////////////////////////////////////////////////////////////////////
//1 кейс
void caseOneLab4_Queue()
{
    string s;
    cout << "Введіть рядок: ";
    cin >> s;
    int index = firstUniqChar(s);
    if (index != -1) {
        cout << "Перший унікальний символ знаходиться на індексі: " << index << endl;
    }
    else {
        cout << "Унікальний символ не знайдено." << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//2 кейс
void stackPush(MyStack& stack) {
    int value;
    cout << "Введіть елемент для додавання (1 до 9): ";
    cin >> value;
    if (value >= 1 && value <= 9) {
        stack.push(value);
        cout << "Елемент додано.\n";
    }
    else {
        cout << "Неправильне значення. Спробуйте ще раз.\n";
    }
}
void stackPop(MyStack& stack) {
    if (!stack.empty()) {
        cout << "Видалений елемент: " << stack.pop() << endl;
    }
    else {
        cout << "Стек порожній. Неможливо видалити елемент.\n";
    }
}
void stackTop(MyStack& stack) {
    if (!stack.empty()) {
        cout << "Верхній елемент стека: " << stack.top() << endl;
    }
    else {
        cout << "Стек порожній.\n";
    }
}
void stackEmpty(MyStack& stack) {
    cout << "Стек " << (stack.empty() ? "порожній" : "не порожній") << ".\n";
}

void caseTwoLab4_Queue() {
    MyStack stack;
    std::vector<std::string> stackMenuItems = {
        "1. Push (додати елемент)\n",
        "2. Pop (видалити елемент)\n",
        "3. Top (показати верхній елемент)\n",
        "4. Empty (перевірити чи стек порожній)\n",
        "0. Вихід\n"
    };

    std::vector<std::function<void()>> stackActions = {
        [&]() { stackPush(stack); },
        [&]() { stackPop(stack); },
        [&]() { stackTop(stack); },
        [&]() { stackEmpty(stack); }
    };

    DisplayMenu(stackMenuItems, stackActions);
}
//////////////////////////////////////////////////////////////////////////////////////////
//3 кейс
void caseThreeLab4_Queue() {
    
    RecentCounter counter;
    int t, n;
    cout << "Введіть кількість запитів: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "Введіть момент часу для запиту " << i + 1 << " (1 <= t <= 1000000000): ";
        cin >> t;

        if (t < 1 || t > 1000000000) {
            cout << "Неправильне значення 't'. Спробуйте ще раз.\n";
            --i; // зменшуємо ітератор, щоб користувач міг повторити введення
            continue;
        }

        cout << "Кількість запитів протягом останніх 3000 мілісекунд: " << counter.ping(t) << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//4 кейс
void dequeInsertFront(MyCircularDeque& deque) {
    int value;
    cout << "Введіть значення для вставки на передню позицію (0 до 1000): ";
    cin >> value;
    if (value >= 0 && value <= 1000) {
        cout << (deque.insertFront(value) ? "Вставлено." : "Deque повна.") << endl;
    }
    else {
        cout << "Неправильне значення.\n";
    }
}
void dequeInsertLast(MyCircularDeque& deque) {
    int value;
    cout << "Введіть значення для вставки у задню позицію (0 до 1000): ";
    cin >> value;
    if (value >= 0 && value <= 1000) {
        cout << (deque.insertLast(value) ? "Вставлено." : "Deque повна.") << endl;
    }
    else {
        cout << "Неправильне значення.\n";
    }
}
void dequeDeleteFront(MyCircularDeque& deque) {
    cout << (deque.deleteFront() ? "Передній елемент видалено." : "Deque порожня.") << endl;
}
void dequeDeleteLast(MyCircularDeque& deque) {
    cout << (deque.deleteLast() ? "Задній елемент видалено." : "Deque порожня.") << endl;
}
void dequeGetFront(MyCircularDeque& deque) {
    int front = deque.getFront();
    if (front != -1) {
        cout << "Передній елемент: " << front << endl;
    }
    else {
        cout << "Deque порожня.\n";
    }
}
void dequeGetRear(MyCircularDeque& deque) {
    int rear = deque.getRear();
    if (rear != -1) {
        cout << "Задній елемент: " << rear << endl;
    }
    else {
        cout << "Deque порожня.\n";
    }
}
void dequeCheckEmpty(MyCircularDeque& deque) {
    cout << "Deque " << (deque.isEmpty() ? "порожня" : "не порожня") << ".\n";
}
void dequeCheckFull(MyCircularDeque& deque) {
    cout << "Deque " << (deque.isFull() ? "повна" : "не повна") << ".\n";
}

void caseFourLab4_Queue() {
    int k;
    cout << "Введіть максимальний розмір Deque: ";
    cin >> k;
    MyCircularDeque deque(k);

    std::vector<std::string> dequeMenuItems = {
        "1. Insert Front",
        "2. Insert Last",
        "3. Delete Front",
        "4. Delete Last",
        "5. Get Front",
        "6. Get Rear",
        "7. Check if Empty",
        "8. Check if Full",
        "0. Вихід"
    };

    std::vector<std::function<void()>> dequeActions = {
    [&]() { dequeInsertFront(deque); },
    [&]() { dequeInsertLast(deque); },
    [&]() { dequeDeleteFront(deque); },
    [&]() { dequeDeleteLast(deque); },
    [&]() { dequeGetFront(deque); },
    [&]() { dequeGetRear(deque); },
    [&]() { dequeCheckEmpty(deque); },
    [&]() { dequeCheckFull(deque); }
    };

    DisplayMenu(dequeMenuItems, dequeActions);
}
//////////////////////////////////////////////////////////////////////////////////////////
//5 кейс
void queueEnqueue(MyCircularQueue& queue) {
    int value;
    cout << "Введіть значення для додавання (0 до 1000): ";
    cin >> value;
    if (value >= 0 && value <= 1000) {
        cout << (queue.enQueue(value) ? "Елемент додано." : "Черга повна.") << endl;
    }
    else {
        cout << "Неправильне значення.\n";
    }
}
void queueDequeue(MyCircularQueue& queue) {
    cout << (queue.deQueue() ? "Елемент видалено." : "Черга порожня.") << endl;
}
void queueFront(MyCircularQueue& queue) {
    int front = queue.Front();
    if (front != -1) {
        cout << "Передній елемент: " << front << endl;
    }
    else {
        cout << "Черга порожня.\n";
    }
}
void queueRear(MyCircularQueue& queue) {
    int rear = queue.Rear();
    if (rear != -1) {
        cout << "Задній елемент: " << rear << endl;
    }
    else {
        cout << "Черга порожня.\n";
    }
}
void queueIsEmpty(MyCircularQueue& queue) {
    cout << "Черга " << (queue.isEmpty() ? "порожня" : "не порожня") << ".\n";
}
void queueIsFull(MyCircularQueue& queue) {
    cout << "Черга " << (queue.isFull() ? "повна" : "не повна") << ".\n";
}

void caseFiveLab4_Queue() {
    int k;
    cout << "Введіть розмір циклічної черги (1 до 1000): ";
    cin >> k;
    MyCircularQueue queue(k);

    std::vector<std::string> queueMenuItems = {
        "1. Enqueue",
        "2. Dequeue",
        "3. Front",
        "4. Rear",
        "5. Check if Empty",
        "6. Check if Full",
        "0. Вихід"
    };

    std::vector<std::function<void()>> queueActions = {
        [&]() { queueEnqueue(queue); },
        [&]() { queueDequeue(queue); },
        [&]() { queueFront(queue); },
        [&]() { queueRear(queue); },
        [&]() { queueIsEmpty(queue); },
        [&]() { queueIsFull(queue); }
    };

    DisplayMenu(queueMenuItems, queueActions);
}
//////////////////////////////////////////////////////////////////////////////////////////
//6 кейс
void caseSixLab4_Queue() {
    string stamp, target;
    cout << "Введіть штамп (довжина від 1 до 1000): ";
    cin >> stamp;
    cout << "Введіть цільовий рядок (довжина від 1 до 1000): ";
    cin >> target;

    if (stamp.length() > 1000 || target.length() > 1000 || stamp.length() > target.length()) {
        cout << "Неправильний ввід. Довжина штампу або цільового рядка перевищує дозволені межі, або довжина штампу більша за довжину цільового рядка." << endl;
        return;
    }

    vector<int> result = movesToStamp(stamp, target);
    if (result.empty()) {
        cout << "Неможливо перетворити s в target за допустиму кількість ходів." << endl;
    }
    else {
        cout << "Результат штампування: ";
        for (int i : result) {
            cout << i << " ";
        }
        cout << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//7 кейс
void caseSevenLab4_Queue() {
    int n, k;
    cout << "Введіть кількість елементів масиву (1 до 100000): ";
    cin >> n;

    if (n < 1 || n > 100000) {
        cout << "Неправильний розмір масиву." << endl;
        return;
    }

    vector<int> nums(n);
    cout << "Введіть елементи масиву (-10000 до 10000): ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (nums[i] < -10000 || nums[i] > 10000) {
            cout << "Неправильне значення елементу масиву." << endl;
            --i;  // Запитати ще раз
        }
    }

    cout << "Введіть розмір вікна k (1 до " << n << "): ";
    cin >> k;
    if (k < 1 || k > n) {
        cout << "Неправильний розмір вікна." << endl;
        return;
    }

    vector<int> result = maxSlidingWindow(nums, k);
    cout << "Максимуми плаваючого вікна: ";
    for (int r : result) {
        cout << r << " ";
    }
    cout << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////
//8 кейс
void caseEightLab4_Queue()
{
    int n, k;
    cout << "Введіть кількість елементів масиву (1 до 100000): ";
    cin >> n;

    if (n < 1 || n > 100000) {
        cout << "Неправильний розмір масиву." << endl;
        return;
    }

    vector<int> nums(n);
    cout << "Введіть елементи масиву (-10000 до 10000): ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (nums[i] < -10000 || nums[i] > 10000) {
            cout << "Неправильне значення елементу масиву." << endl;
            --i;  // Запитати ще раз
        }
    }

    cout << "Введіть k (1 до " << n << "): ";
    cin >> k;
    if (k < 1 || k > n) {
        cout << "Неправильний розмір k." << endl;
        return;
    }

    int result = constrainedSubsetSum(nums, k);
    cout << "Максимальна сума підпослідовності: " << result << endl;
    return;
}

void Lab_4_Queue() {
    std::vector<std::string> menuItems = {
        "1. Перший унікальний символ у рядку\n",
        "2. Реалізація стека за допомогою черг\n",
        "3. Кількість останніх викликів\n",
        "4. Дизайн замкнутої двубічної черги (Deque)\n",
        "5. Реалізація циклічної черги\n",
        "6. Штампування послідовності\n",
        "7. Максимум плаваючого вікна\n",
        "8. Обмежена сума підпослідовності\n",
        "0. Вихід з меню\n"
    };


    std::vector<std::function<void()>> actions = {
        []() { caseOneLab4_Queue(); },
        []() { caseTwoLab4_Queue(); },
        []() { caseThreeLab4_Queue(); },
        []() { caseFourLab4_Queue(); },
        []() { caseFiveLab4_Queue(); },
        []() { caseSixLab4_Queue(); },
        []() { caseSevenLab4_Queue(); },
        []() { caseEightLab4_Queue(); }
    };

    DisplayMenu(menuItems, actions);

    return;
}
