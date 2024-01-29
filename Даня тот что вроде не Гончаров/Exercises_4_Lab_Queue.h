#pragma once
#include "classes.h"
#include "Menu.h"

//Завдання 1: Перший унікальний символ у рядку
int firstUniqChar(string s);

//Завдання 2: Реалізація стека за допомогою черг
class MyStack {
private:
    queue<int> q1, q2;

    void shiftQueue() {
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }
    }

public:
    void push(int x) {
        q1.push(x);
    }

    int pop() {
        shiftQueue();
        int top = q1.front();
        q1.pop();
        swap(q1, q2);
        return top;
    }

    int top() {
        shiftQueue();
        int top = q1.front();
        q2.push(top);
        swap(q1, q2);
        return top;
    }

    bool empty() {
        return q1.empty() && q2.empty();
    }
};
//Завдання 3.1: Кількість останніх викликів
class RecentCounter {
private:
    queue<int> requests;

public:
    int ping(int t) {
        requests.push(t);
        while (!requests.empty() && requests.front() < t - 3000) {
            requests.pop();
        }
        return requests.size();
    }
};
//Завдання 3.2: Дизайн замкнутої двубічної черги (Deque)
class MyCircularDeque {
private:
    vector<int> deque;
    int front, rear, capacity;

public:
    MyCircularDeque(int k) : capacity(k), deque(k), front(k - 1), rear(0) {}

    bool insertFront(int value) {
        if (isFull()) return false;
        deque[front] = value;
        front = (front - 1 + capacity) % capacity;
        return true;
    }

    bool insertLast(int value) {
        if (isFull()) return false;
        deque[rear] = value;
        rear = (rear + 1) % capacity;
        return true;
    }

    bool deleteFront() {
        if (isEmpty()) return false;
        front = (front + 1) % capacity;
        return true;
    }

    bool deleteLast() {
        if (isEmpty()) return false;
        rear = (rear - 1 + capacity) % capacity;
        return true;
    }

    int getFront() {
        if (isEmpty()) return -1;
        return deque[(front + 1) % capacity];
    }

    int getRear() {
        if (isEmpty()) return -1;
        return deque[(rear - 1 + capacity) % capacity];
    }

    bool isEmpty() {
        return (rear - front + capacity) % capacity == 1;
    }

    bool isFull() {
        return (rear - front + capacity) % capacity == 0;
    }
};
//Завдання 4: Реалізація циклічної черги
class MyCircularQueue {
private:
    vector<int> data;
    int head;
    int tail;
    int size;

public:
    MyCircularQueue(int k) : data(k), head(-1), tail(-1), size(k) {}

    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        if (isEmpty()) {
            head = 0;
        }
        tail = (tail + 1) % size;
        data[tail] = value;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        if (head == tail) {
            head = -1;
            tail = -1;
            return true;
        }
        head = (head + 1) % size;
        return true;
    }

    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return data[head];
    }

    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return data[tail];
    }

    bool isEmpty() {
        return head == -1;
    }

    bool isFull() {
        return ((tail + 1) % size) == head;
    }
};

//Завдання 5: Штампування послідовності
bool canStamp(const string& target, int pos, const string& stamp);
void doStamp(string& target, int pos, int len, int& stars);

vector<int> movesToStamp(string stamp, string target);
//Завдання 6: Максимум плаваючого вікна
vector<int> maxSlidingWindow(vector<int>& nums, int k);
//Завдання 7: Обмежена сума підпослідовності
int constrainedSubsetSum(vector<int>& nums, int k);

//Функції меню
void caseOneLab4_Queue();
void caseTwoLab4_Queue();
void caseThreeLab4_Queue();
void caseFourLab4_Queue();
void caseFiveLab4_Queue();
void caseSixLab4_Queue();
void caseSevenLab4_Queue();
void caseEightLab4_Queue();

void Lab_4_Queue();
