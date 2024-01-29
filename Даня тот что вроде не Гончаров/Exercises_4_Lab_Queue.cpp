#include "Exercises_4_Lab_Queue.h"
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

//�������� 1: ������ ��������� ������ � �����
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

//�������� 5: ����������� �����������
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
//�������� 6: �������� ���������� ����
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
//�������� 7: �������� ���� �������������

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

//������� ����
//////////////////////////////////////////////////////////////////////////////////////////
//1 ����
void caseOneLab4_Queue()
{
    string s;
    cout << "������ �����: ";
    cin >> s;
    int index = firstUniqChar(s);
    if (index != -1) {
        cout << "������ ��������� ������ ����������� �� ������: " << index << endl;
    }
    else {
        cout << "��������� ������ �� ��������." << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//2 ����
void stackPush(MyStack& stack) {
    int value;
    cout << "������ ������� ��� ��������� (1 �� 9): ";
    cin >> value;
    if (value >= 1 && value <= 9) {
        stack.push(value);
        cout << "������� ������.\n";
    }
    else {
        cout << "����������� ��������. ��������� �� ���.\n";
    }
}
void stackPop(MyStack& stack) {
    if (!stack.empty()) {
        cout << "��������� �������: " << stack.pop() << endl;
    }
    else {
        cout << "���� �������. ��������� �������� �������.\n";
    }
}
void stackTop(MyStack& stack) {
    if (!stack.empty()) {
        cout << "������ ������� �����: " << stack.top() << endl;
    }
    else {
        cout << "���� �������.\n";
    }
}
void stackEmpty(MyStack& stack) {
    cout << "���� " << (stack.empty() ? "�������" : "�� �������") << ".\n";
}

void caseTwoLab4_Queue() {
    MyStack stack;
    std::vector<std::string> stackMenuItems = {
        "1. Push (������ �������)\n",
        "2. Pop (�������� �������)\n",
        "3. Top (�������� ������ �������)\n",
        "4. Empty (��������� �� ���� �������)\n",
        "0. �����\n"
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
//3 ����
void caseThreeLab4_Queue() {
    
    RecentCounter counter;
    int t, n;
    cout << "������ ������� ������: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cout << "������ ������ ���� ��� ������ " << i + 1 << " (1 <= t <= 1000000000): ";
        cin >> t;

        if (t < 1 || t > 1000000000) {
            cout << "����������� �������� 't'. ��������� �� ���.\n";
            --i; // �������� ��������, ��� ���������� �� ��������� ��������
            continue;
        }

        cout << "ʳ������ ������ �������� ������� 3000 ��������: " << counter.ping(t) << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//4 ����
void dequeInsertFront(MyCircularDeque& deque) {
    int value;
    cout << "������ �������� ��� ������� �� ������� ������� (0 �� 1000): ";
    cin >> value;
    if (value >= 0 && value <= 1000) {
        cout << (deque.insertFront(value) ? "���������." : "Deque �����.") << endl;
    }
    else {
        cout << "����������� ��������.\n";
    }
}
void dequeInsertLast(MyCircularDeque& deque) {
    int value;
    cout << "������ �������� ��� ������� � ����� ������� (0 �� 1000): ";
    cin >> value;
    if (value >= 0 && value <= 1000) {
        cout << (deque.insertLast(value) ? "���������." : "Deque �����.") << endl;
    }
    else {
        cout << "����������� ��������.\n";
    }
}
void dequeDeleteFront(MyCircularDeque& deque) {
    cout << (deque.deleteFront() ? "������� ������� ��������." : "Deque �������.") << endl;
}
void dequeDeleteLast(MyCircularDeque& deque) {
    cout << (deque.deleteLast() ? "����� ������� ��������." : "Deque �������.") << endl;
}
void dequeGetFront(MyCircularDeque& deque) {
    int front = deque.getFront();
    if (front != -1) {
        cout << "������� �������: " << front << endl;
    }
    else {
        cout << "Deque �������.\n";
    }
}
void dequeGetRear(MyCircularDeque& deque) {
    int rear = deque.getRear();
    if (rear != -1) {
        cout << "����� �������: " << rear << endl;
    }
    else {
        cout << "Deque �������.\n";
    }
}
void dequeCheckEmpty(MyCircularDeque& deque) {
    cout << "Deque " << (deque.isEmpty() ? "�������" : "�� �������") << ".\n";
}
void dequeCheckFull(MyCircularDeque& deque) {
    cout << "Deque " << (deque.isFull() ? "�����" : "�� �����") << ".\n";
}

void caseFourLab4_Queue() {
    int k;
    cout << "������ ������������ ����� Deque: ";
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
        "0. �����"
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
//5 ����
void queueEnqueue(MyCircularQueue& queue) {
    int value;
    cout << "������ �������� ��� ��������� (0 �� 1000): ";
    cin >> value;
    if (value >= 0 && value <= 1000) {
        cout << (queue.enQueue(value) ? "������� ������." : "����� �����.") << endl;
    }
    else {
        cout << "����������� ��������.\n";
    }
}
void queueDequeue(MyCircularQueue& queue) {
    cout << (queue.deQueue() ? "������� ��������." : "����� �������.") << endl;
}
void queueFront(MyCircularQueue& queue) {
    int front = queue.Front();
    if (front != -1) {
        cout << "������� �������: " << front << endl;
    }
    else {
        cout << "����� �������.\n";
    }
}
void queueRear(MyCircularQueue& queue) {
    int rear = queue.Rear();
    if (rear != -1) {
        cout << "����� �������: " << rear << endl;
    }
    else {
        cout << "����� �������.\n";
    }
}
void queueIsEmpty(MyCircularQueue& queue) {
    cout << "����� " << (queue.isEmpty() ? "�������" : "�� �������") << ".\n";
}
void queueIsFull(MyCircularQueue& queue) {
    cout << "����� " << (queue.isFull() ? "�����" : "�� �����") << ".\n";
}

void caseFiveLab4_Queue() {
    int k;
    cout << "������ ����� ������� ����� (1 �� 1000): ";
    cin >> k;
    MyCircularQueue queue(k);

    std::vector<std::string> queueMenuItems = {
        "1. Enqueue",
        "2. Dequeue",
        "3. Front",
        "4. Rear",
        "5. Check if Empty",
        "6. Check if Full",
        "0. �����"
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
//6 ����
void caseSixLab4_Queue() {
    string stamp, target;
    cout << "������ ����� (������� �� 1 �� 1000): ";
    cin >> stamp;
    cout << "������ �������� ����� (������� �� 1 �� 1000): ";
    cin >> target;

    if (stamp.length() > 1000 || target.length() > 1000 || stamp.length() > target.length()) {
        cout << "������������ ���. ������� ������ ��� ��������� ����� �������� �������� ���, ��� ������� ������ ����� �� ������� ��������� �����." << endl;
        return;
    }

    vector<int> result = movesToStamp(stamp, target);
    if (result.empty()) {
        cout << "��������� ����������� s � target �� ��������� ������� ����." << endl;
    }
    else {
        cout << "��������� �����������: ";
        for (int i : result) {
            cout << i << " ";
        }
        cout << endl;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
//7 ����
void caseSevenLab4_Queue() {
    int n, k;
    cout << "������ ������� �������� ������ (1 �� 100000): ";
    cin >> n;

    if (n < 1 || n > 100000) {
        cout << "������������ ����� ������." << endl;
        return;
    }

    vector<int> nums(n);
    cout << "������ �������� ������ (-10000 �� 10000): ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (nums[i] < -10000 || nums[i] > 10000) {
            cout << "����������� �������� �������� ������." << endl;
            --i;  // �������� �� ���
        }
    }

    cout << "������ ����� ���� k (1 �� " << n << "): ";
    cin >> k;
    if (k < 1 || k > n) {
        cout << "������������ ����� ����." << endl;
        return;
    }

    vector<int> result = maxSlidingWindow(nums, k);
    cout << "��������� ���������� ����: ";
    for (int r : result) {
        cout << r << " ";
    }
    cout << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////
//8 ����
void caseEightLab4_Queue()
{
    int n, k;
    cout << "������ ������� �������� ������ (1 �� 100000): ";
    cin >> n;

    if (n < 1 || n > 100000) {
        cout << "������������ ����� ������." << endl;
        return;
    }

    vector<int> nums(n);
    cout << "������ �������� ������ (-10000 �� 10000): ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (nums[i] < -10000 || nums[i] > 10000) {
            cout << "����������� �������� �������� ������." << endl;
            --i;  // �������� �� ���
        }
    }

    cout << "������ k (1 �� " << n << "): ";
    cin >> k;
    if (k < 1 || k > n) {
        cout << "������������ ����� k." << endl;
        return;
    }

    int result = constrainedSubsetSum(nums, k);
    cout << "����������� ���� �������������: " << result << endl;
    return;
}

void Lab_4_Queue() {
    std::vector<std::string> menuItems = {
        "1. ������ ��������� ������ � �����\n",
        "2. ��������� ����� �� ��������� ����\n",
        "3. ʳ������ ������� �������\n",
        "4. ������ �������� ������� ����� (Deque)\n",
        "5. ��������� ������� �����\n",
        "6. ����������� �����������\n",
        "7. �������� ���������� ����\n",
        "8. �������� ���� �������������\n",
        "0. ����� � ����\n"
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
