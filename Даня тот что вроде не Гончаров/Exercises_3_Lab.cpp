#include "Exercises_3_Lab.h"

#undef max
//1. Об'єднання двох відсортованих зв'язаних списків:
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    if (list1->val < list2->val) {
        list1->next = mergeTwoLists(list1->next, list2);
        return list1;
    }
    else {
        list2->next = mergeTwoLists(list1, list2->next);
        return list2;
    }
}
//2. Видалення дублікатів у відсортованому зв'язаному списку:
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* current = head;
    while (current && current->next) {
        if (current->val == current->next->val) {
            ListNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
        else {
            current = current->next;
        }
    }
    return head;
}
//3.Перевірка наявності циклу в зв'язаному списку:
bool hasCycle(ListNode* head) {
    ListNode* slow = head, * fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}
//4.Перестановка вузлів у зв'язаному списку:
void reorderList(ListNode* head) {
    if (!head || !head->next || !head->next->next) return;

    // Розділення списку на дві половини
    ListNode* slow = head, * fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Перевертання другої половини
    ListNode* prev = nullptr, * curr = slow->next, * temp;
    while (curr) {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    slow->next = nullptr;

    // Об'єднання двох половин
    ListNode* l1 = head, * l2 = prev;
    while (l2) {
        temp = l1->next;
        l1->next = l2;
        l1 = l2;
        l2 = temp;
    }
}
//5. Видалення вказаного вузла у зв'язаному списку:
void deleteNode(ListNode* node) {
    if (!node || !node->next) return;
    node->val = node->next->val;
    ListNode* temp = node->next;
    node->next = node->next->next;
    delete temp;
}
//6. Подвоєння числа, представленого зв'язаним списком:
ListNode* doubleLinkedList(ListNode* head) {
    // Створюємо зворотній список для зручності обчислень
    ListNode* reversed = reverseList(head);
    ListNode* current = reversed;
    ListNode dummyHead(0);
    ListNode* node = &dummyHead;
    int carry = 0;

    while (current != nullptr || carry > 0) {
        int sum = carry + (current != nullptr ? current->val * 2 : 0);
        carry = sum / 10;
        node->next = new ListNode(sum % 10);
        node = node->next;

        if (current != nullptr) current = current->next;
    }

    // Перевертаємо список назад
    ListNode* result = reverseList(dummyHead.next);

    // Очищуємо тимчасовий зворотній список
    deleteList(reversed);

    return result;
}
//7. Об'єднання декількох відсортованих зв'язаних списків:
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;

    while (lists.size() > 1) {
        lists.push_back(mergeTwoLists(lists[0], lists[1]));
        lists.erase(lists.begin());
        lists.erase(lists.begin());
    }

    return lists.front();
}
//8. Розвернути вузли в k-групі:
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* curr = head;
    int count = 0;
    while (curr && count != k) { // знайти k-й вузол
        curr = curr->next;
        count++;
    }

    if (count == k) {
        curr = reverseKGroup(curr, k); // звернути наступну частину
        while (count-- > 0) { // звернути поточну частину
            ListNode* temp = head->next;
            head->next = curr;
            curr = head;
            head = temp;
        }
        head = curr;
    }
    return head;
}
//9. Розділити список
ListNode* partition(ListNode* head, int x) {
    ListNode lessHead(0), greaterHead(0); // фіктивні вузли
    ListNode* lessTail = &lessHead, * greaterTail = &greaterHead;

    while (head) {
        if (head->val < x) {
            lessTail->next = head;
            lessTail = head;
        }
        else {
            greaterTail->next = head;
            greaterTail = head;
        }
        head = head->next;
    }

    lessTail->next = greaterHead.next; // об'єднання двох списків
    greaterTail->next = nullptr; // останній вузол має вказувати на nullptr

    return lessHead.next; // повернення вузла після фіктивного вузла
}

void caseOneLab3() {
    vector<int> list1Values, list2Values;
    int n1, n2, val;

    cout << "Введіть кількість елементів у першому списку (від 0 до 50): ";
    cin >> n1;

    if (checkCin((cin.fail() || n1 < 0 || n1 > 50),
        "Помилка: кількість елементів повинна бути від 0 до 50."))
        return;

    cout << "Введіть елементи першого списку (-100 <= Node.val <= 100): ";
    for (int i = 0; i < n1; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < -100 || val > 100),
            "Помилка: значення вузла повинне бути від -100 до 100."))
            return;
        list1Values.push_back(val);
    }

    cout << "Введіть кількість елементів у другому списку (від 0 до 50): ";
    cin >> n2;
    if (checkCin((cin.fail() || n2 < 0 || n2 > 50),
        "Помилка: кількість елементів повинна бути від 0 до 50."))
        return;

    cout << "Введіть елементи другого списку (-100 <= Node.val <= 100): ";
    for (int i = 0; i < n2; ++i) {
        cin >> val;
        if (checkCin((val < -100 || val > 100),
            "Помилка: значення вузла повинне бути від -100 до 100."))
            return;
        list2Values.push_back(val);
    }

    // Створення двох списків з введених значень
    ListNode* list1 = createList(list1Values);
    ListNode* list2 = createList(list2Values);

    // Об'єднання двох списків
    ListNode* mergedList = mergeTwoLists(list1, list2);
    cout << "Об'єднаний список: ";
    printList(mergedList);

    // Очищення пам'яті
    deleteList(list1);
    deleteList(list2);
}
void caseTwoLab3()
{
    vector<int> values;
    int n, val;

    cout << "Введіть кількість елементів у списку (від 0 до 300): ";
    cin >> n;
    if (checkCin((n < 0 || n > 300),
        "Кількість елементів повинна бути у діапазоні від 0 до 300."))
        return;

    cout << "Введіть елементи відсортованого списку (-100 <= значення <= 100): ";
    int lastVal = INT_MIN; // Використовуємо INT_MIN як початкове значення
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((val < -100 || val > 100), "Значення елемента повинно бути у діапазоні від -100 до 100",
                 (val < lastVal)          , "Список повинен бути відсортованим у порядку зростання."    ))
            return;
        lastVal = val;
        values.push_back(val);
    }

    ListNode* head = createList(values);
    ListNode* result = deleteDuplicates(head);

    cout << "Список без дублікатів: ";
    printList(result);

    deleteList(result); // Очищення пам'яті після використання списку
}
void caseThreeLab3()
{
    vector<int> values;
    int n, val, cycleIndex;

    cout << "Введіть кількість елементів у списку (0 - 10000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 0 || n > 10000),
        "Помилка: неправильна кількість вузлів."))
        return;

    cout << "Введіть елементи списку (-100000 <= Node.val <= 100000): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < -100000 || val > 100000),
            "Помилка: неправильне значення вузла."))
            return;
        values.push_back(val);
    }

    ListNode* head = createList(values);

    cout << "Введіть індекс вузла для створення циклу (-1 - без циклу): ";
    cin >> cycleIndex;

    ListNode* cycleNode = nullptr;
    ListNode* current = head;
    int currentIndex = 0;
    while (current) {
        if (currentIndex == cycleIndex) {
            cycleNode = current;
        }
        if (current->next == nullptr && cycleNode != nullptr) {
            current->next = cycleNode; // Створення циклу
            break;
        }
        current = current->next;
        ++currentIndex;
    }

    bool hasCycleResult = hasCycle(head);
    cout << "Наявність циклу у списку: " << (hasCycleResult ? "так" : "ні") << endl;

    if (cycleNode != nullptr) {
        // Розриваємо цикл для можливості видалення списку
        current = head;
        while (current->next != cycleNode) {
            current = current->next;
        }
        current->next = nullptr;
    }

    deleteList(head);

}
void caseFourLab3()
{
    vector<int> values;
    int n, val;

    cout << "Введіть кількість елементів у списку (від 1 до 50000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 1 || n > 50000),
        "Помилка: неправильна кількість елементів."))
        return;

    cout << "Введіть елементи списку (значення від 1 до 1000): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < 1 || val > 1000),
            "Помилка: неправильне значення елемента."))
            return;
        values.push_back(val);
    }

    ListNode* head = createList(values);
    reorderList(head);

    cout << "Переставлений список: ";
    printList(head);

    deleteList(head); // Очищення списку після завершення роботи з ним
}
void caseFiveLab3() {
    vector<int> values;
    int n, val, nodeValueToDelete;

    cout << "Введіть кількість елементів у списку (від 2 до 1000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 2 || n > 1000),
        "Помилка: неправильна кількість елементів."))
        return;

    cout << "Введіть елементи списку (-1000 <= значення <= 1000): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < -1000 || val > 1000),
            "Помилка: неправильне значення елемента."))
            return;
        
        values.push_back(val);
    }

    ListNode* head = createList(values);
    cout << "Введіть значення вузла для видалення (-1000 <= значення <= 1000): ";
    cin >> nodeValueToDelete;

    if (checkCin((cin.fail() || nodeValueToDelete < -1000 || nodeValueToDelete > 1000),
        "Помилка: неправильне значення вузла для видалення."))
        return;

    // Знаходимо і видаляємо вузол за значенням
    ListNode* current = head, * prev = nullptr;
    bool nodeFound = false;
    while (current != nullptr) {
        if (current->val == nodeValueToDelete) {
            nodeFound = true;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!nodeFound) {
        cout << "Вузол зі значенням " << nodeValueToDelete << " не знайдено." << endl;
    }
    else if (prev == nullptr) {
        // Вузол для видалення знаходиться на початку списку
        head = current->next;
        delete current;
        cout << "Список після видалення вузла: ";
        printList(head);
    }
    else {
        // Вузол для видалення знаходиться в середині або в кінці списку
        prev->next = current->next;
        delete current;
        cout << "Список після видалення вузла: ";
        printList(head);
    }

    deleteList(head); // Очищення списку після завершення роботи з ним
}
void caseSixLab3() {
    vector<int> values;
    int n, val;

    cout << "Введіть кількість елементів у списку (від 1 до 10000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 1 || n > 10000),
        "Помилка: неправильна кількість елементів."))
        return;

    cout << "Введіть цифри числа (від 0 до 9): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < 0 || val > 9),
            "Помилка: неправильне значення елемента. Введіть цифру від 0 до 9."))
            return;
        values.push_back(val);
    }

    ListNode* head = createList(values);
    ListNode* doubledList = doubleLinkedList(head);

    cout << "Список після подвоєння: ";
    printList(doubledList);

    deleteList(doubledList); // Очищення списку після завершення роботи з ним
}
void caseSevenLab3() {
    int k, n, val;
    cout << "Введіть кількість списків (від 0 до 10000): ";
    cin >> k;
    if (checkCin((cin.fail() || k < 0 || k > 10000),
        "Помилка: неправильна кількість списків."))
        return;

    vector<ListNode*> lists(k);
    int totalLength = 0;

    for (int i = 0; i < k; ++i) {
        cout << "Введіть кількість елементів у списку " << i + 1 << " (від 0 до 500): ";
        cin >> n;

        if (checkCin((cin.fail() || n < 0 || n > 500 || totalLength + n > 10000),
            "Помилка: неправильна кількість елементів у списку."))
            return;
        totalLength += n;

        vector<int> values;
        int lastVal = INT_MIN;
        cout << "Введіть елементи відсортованого списку (від -10000 до 10000): ";
        for (int j = 0; j < n; ++j) {
            cin >> val;
            if (checkCin((cin.fail() || val < -10000 || val > 10000 || val < lastVal),
                "Помилка: неправильне значення елемента або список не відсортований."))
                return;
            lastVal = val;
            values.push_back(val);
        }
        lists[i] = createList(values);
    }

    ListNode* mergedList = mergeKLists(lists);
    cout << "Об'єднаний список: ";
    printList(mergedList);

    // Після виконання mergeKLists, очищуємо лише оригінальні списки, якщо вони не були використані в mergedList
    for (ListNode* list : lists) {
        // Видаляємо лише вузли, які не були включені до mergedList так як якщо вузли переміщуються, 
        // видалення оригінальних списків може призвести до помилки, якщо ці вузли також зустрічаються у mergedList.
        if (list != nullptr && list != mergedList) {
            deleteList(list);
        }
    }

    // Тепер можемо безпечно видалити об'єднаний список
    deleteList(mergedList);
}
void caseEightLab3() {
    vector<int> values;
    int n, val, k;

    cout << "Введіть кількість елементів у списку (від 1 до 5000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 1 || n > 5000),
        "Помилка: неправильна кількість елементів."))
        return;

    cout << "Введіть елементи списку (значення від 0 до 1000): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < 0 || val > 1000),
            "Помилка: неправильне значення елемента."))
            return;
        values.push_back(val);
    }

    cout << "Введіть k (від 1 до " << n << "): ";
    cin >> k;
    if (checkCin((cin.fail() || k < 1 || k > n),
        "Помилка: неправильне значення k."))
        return;

    ListNode* head = createList(values);
    ListNode* reversedList = reverseKGroup(head, k);

    cout << "Список після звертання кожні " << k << " вузлів: ";
    printList(reversedList);

    deleteList(reversedList); // Очищення списку після завершення роботи з ним
}
void caseNineLab3() {
    vector<int> values;
    int n, val, x;

    cout << "Введіть кількість елементів у списку (від 0 до 200): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 0 || n > 200),
        "Помилка: неправильна кількість елементів."))
        return;

    cout << "Введіть елементи списку (-100 <= значення <= 100): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < -100 || val > 100),
            "Помилка: неправильне значення елемента."))
            return;
        values.push_back(val);
    }

    cout << "Введіть значення x (-200 <= x <= 200): ";
    cin >> x;
    if (checkCin((cin.fail() || x < -200 || x > 200),
        "Помилка: неправильне значення x."))
        return;

    ListNode* head = createList(values);
    ListNode* partitioned = partition(head, x);

    cout << "Розділений список: ";
    printList(partitioned);

    deleteList(partitioned); // Очищення списку після завершення роботи з ним
}


void Lab_3() {
    std::vector<std::string> menuItems = {
        "1. Об'єднання двох відсортованих зв'язаних списків\n",
        "2. Видалення дублікатів у відсортованому зв'язаному списку\n",
        "3. Перевірка наявності циклу в зв'язаному списку\n",
        "4. Перестановка вузлів у зв'язаному списку\n",
        "5. Видалення вказаного вузла у зв'язаному списку\n",
        "6. Подвоєння числа, представленого зв'язаним списком\n",
        "7. Об'єднання декількох відсортованих зв'язаних списків\n",
        "8. Розвернути вузли в k-групі\n",
        "9. Розділити список\n",
        "0. Вихід з меню\n"
    };


    std::vector<std::function<void()>> actions = {
        []() { caseOneLab3(); },
        []() { caseTwoLab3(); },
        []() { caseThreeLab3(); },
        []() { caseFourLab3(); },
        []() { caseFiveLab3(); },
        []() { caseSixLab3(); },
        []() { caseSevenLab3(); },
        []() { caseEightLab3(); },
        []() { caseNineLab3(); }
    };

    DisplayMenu(menuItems, actions);

    return;
}