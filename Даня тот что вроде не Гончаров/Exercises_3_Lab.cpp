#include "Exercises_3_Lab.h"

#undef max
//1. ��'������� ���� ������������ ��'������ ������:
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
//2. ��������� �������� � ������������� ��'������� ������:
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
//3.�������� �������� ����� � ��'������� ������:
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
//4.������������ ����� � ��'������� ������:
void reorderList(ListNode* head) {
    if (!head || !head->next || !head->next->next) return;

    // ��������� ������ �� �� ��������
    ListNode* slow = head, * fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // ������������ ����� ��������
    ListNode* prev = nullptr, * curr = slow->next, * temp;
    while (curr) {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    slow->next = nullptr;

    // ��'������� ���� �������
    ListNode* l1 = head, * l2 = prev;
    while (l2) {
        temp = l1->next;
        l1->next = l2;
        l1 = l2;
        l2 = temp;
    }
}
//5. ��������� ��������� ����� � ��'������� ������:
void deleteNode(ListNode* node) {
    if (!node || !node->next) return;
    node->val = node->next->val;
    ListNode* temp = node->next;
    node->next = node->next->next;
    delete temp;
}
//6. �������� �����, �������������� ��'������ �������:
ListNode* doubleLinkedList(ListNode* head) {
    // ��������� �������� ������ ��� �������� ���������
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

    // ����������� ������ �����
    ListNode* result = reverseList(dummyHead.next);

    // ������� ���������� �������� ������
    deleteList(reversed);

    return result;
}
//7. ��'������� �������� ������������ ��'������ ������:
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;

    while (lists.size() > 1) {
        lists.push_back(mergeTwoLists(lists[0], lists[1]));
        lists.erase(lists.begin());
        lists.erase(lists.begin());
    }

    return lists.front();
}
//8. ���������� ����� � k-����:
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* curr = head;
    int count = 0;
    while (curr && count != k) { // ������ k-� �����
        curr = curr->next;
        count++;
    }

    if (count == k) {
        curr = reverseKGroup(curr, k); // �������� �������� �������
        while (count-- > 0) { // �������� ������� �������
            ListNode* temp = head->next;
            head->next = curr;
            curr = head;
            head = temp;
        }
        head = curr;
    }
    return head;
}
//9. �������� ������
ListNode* partition(ListNode* head, int x) {
    ListNode lessHead(0), greaterHead(0); // ������� �����
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

    lessTail->next = greaterHead.next; // ��'������� ���� ������
    greaterTail->next = nullptr; // ������� ����� �� ��������� �� nullptr

    return lessHead.next; // ���������� ����� ���� ���������� �����
}

void caseOneLab3() {
    vector<int> list1Values, list2Values;
    int n1, n2, val;

    cout << "������ ������� �������� � ������� ������ (�� 0 �� 50): ";
    cin >> n1;

    if (checkCin((cin.fail() || n1 < 0 || n1 > 50),
        "�������: ������� �������� ������� ���� �� 0 �� 50."))
        return;

    cout << "������ �������� ������� ������ (-100 <= Node.val <= 100): ";
    for (int i = 0; i < n1; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < -100 || val > 100),
            "�������: �������� ����� ������� ���� �� -100 �� 100."))
            return;
        list1Values.push_back(val);
    }

    cout << "������ ������� �������� � ������� ������ (�� 0 �� 50): ";
    cin >> n2;
    if (checkCin((cin.fail() || n2 < 0 || n2 > 50),
        "�������: ������� �������� ������� ���� �� 0 �� 50."))
        return;

    cout << "������ �������� ������� ������ (-100 <= Node.val <= 100): ";
    for (int i = 0; i < n2; ++i) {
        cin >> val;
        if (checkCin((val < -100 || val > 100),
            "�������: �������� ����� ������� ���� �� -100 �� 100."))
            return;
        list2Values.push_back(val);
    }

    // ��������� ���� ������ � �������� �������
    ListNode* list1 = createList(list1Values);
    ListNode* list2 = createList(list2Values);

    // ��'������� ���� ������
    ListNode* mergedList = mergeTwoLists(list1, list2);
    cout << "��'������� ������: ";
    printList(mergedList);

    // �������� ���'��
    deleteList(list1);
    deleteList(list2);
}
void caseTwoLab3()
{
    vector<int> values;
    int n, val;

    cout << "������ ������� �������� � ������ (�� 0 �� 300): ";
    cin >> n;
    if (checkCin((n < 0 || n > 300),
        "ʳ������ �������� ������� ���� � ������� �� 0 �� 300."))
        return;

    cout << "������ �������� ������������� ������ (-100 <= �������� <= 100): ";
    int lastVal = INT_MIN; // ������������� INT_MIN �� ��������� ��������
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((val < -100 || val > 100), "�������� �������� ������� ���� � ������� �� -100 �� 100",
                 (val < lastVal)          , "������ ������� ���� ������������ � ������� ���������."    ))
            return;
        lastVal = val;
        values.push_back(val);
    }

    ListNode* head = createList(values);
    ListNode* result = deleteDuplicates(head);

    cout << "������ ��� ��������: ";
    printList(result);

    deleteList(result); // �������� ���'�� ���� ������������ ������
}
void caseThreeLab3()
{
    vector<int> values;
    int n, val, cycleIndex;

    cout << "������ ������� �������� � ������ (0 - 10000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 0 || n > 10000),
        "�������: ����������� ������� �����."))
        return;

    cout << "������ �������� ������ (-100000 <= Node.val <= 100000): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < -100000 || val > 100000),
            "�������: ����������� �������� �����."))
            return;
        values.push_back(val);
    }

    ListNode* head = createList(values);

    cout << "������ ������ ����� ��� ��������� ����� (-1 - ��� �����): ";
    cin >> cycleIndex;

    ListNode* cycleNode = nullptr;
    ListNode* current = head;
    int currentIndex = 0;
    while (current) {
        if (currentIndex == cycleIndex) {
            cycleNode = current;
        }
        if (current->next == nullptr && cycleNode != nullptr) {
            current->next = cycleNode; // ��������� �����
            break;
        }
        current = current->next;
        ++currentIndex;
    }

    bool hasCycleResult = hasCycle(head);
    cout << "�������� ����� � ������: " << (hasCycleResult ? "���" : "�") << endl;

    if (cycleNode != nullptr) {
        // ��������� ���� ��� ��������� ��������� ������
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

    cout << "������ ������� �������� � ������ (�� 1 �� 50000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 1 || n > 50000),
        "�������: ����������� ������� ��������."))
        return;

    cout << "������ �������� ������ (�������� �� 1 �� 1000): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < 1 || val > 1000),
            "�������: ����������� �������� ��������."))
            return;
        values.push_back(val);
    }

    ListNode* head = createList(values);
    reorderList(head);

    cout << "������������� ������: ";
    printList(head);

    deleteList(head); // �������� ������ ���� ���������� ������ � ���
}
void caseFiveLab3() {
    vector<int> values;
    int n, val, nodeValueToDelete;

    cout << "������ ������� �������� � ������ (�� 2 �� 1000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 2 || n > 1000),
        "�������: ����������� ������� ��������."))
        return;

    cout << "������ �������� ������ (-1000 <= �������� <= 1000): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < -1000 || val > 1000),
            "�������: ����������� �������� ��������."))
            return;
        
        values.push_back(val);
    }

    ListNode* head = createList(values);
    cout << "������ �������� ����� ��� ��������� (-1000 <= �������� <= 1000): ";
    cin >> nodeValueToDelete;

    if (checkCin((cin.fail() || nodeValueToDelete < -1000 || nodeValueToDelete > 1000),
        "�������: ����������� �������� ����� ��� ���������."))
        return;

    // ��������� � ��������� ����� �� ���������
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
        cout << "����� � ��������� " << nodeValueToDelete << " �� ��������." << endl;
    }
    else if (prev == nullptr) {
        // ����� ��� ��������� ����������� �� ������� ������
        head = current->next;
        delete current;
        cout << "������ ���� ��������� �����: ";
        printList(head);
    }
    else {
        // ����� ��� ��������� ����������� � ������� ��� � ���� ������
        prev->next = current->next;
        delete current;
        cout << "������ ���� ��������� �����: ";
        printList(head);
    }

    deleteList(head); // �������� ������ ���� ���������� ������ � ���
}
void caseSixLab3() {
    vector<int> values;
    int n, val;

    cout << "������ ������� �������� � ������ (�� 1 �� 10000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 1 || n > 10000),
        "�������: ����������� ������� ��������."))
        return;

    cout << "������ ����� ����� (�� 0 �� 9): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < 0 || val > 9),
            "�������: ����������� �������� ��������. ������ ����� �� 0 �� 9."))
            return;
        values.push_back(val);
    }

    ListNode* head = createList(values);
    ListNode* doubledList = doubleLinkedList(head);

    cout << "������ ���� ��������: ";
    printList(doubledList);

    deleteList(doubledList); // �������� ������ ���� ���������� ������ � ���
}
void caseSevenLab3() {
    int k, n, val;
    cout << "������ ������� ������ (�� 0 �� 10000): ";
    cin >> k;
    if (checkCin((cin.fail() || k < 0 || k > 10000),
        "�������: ����������� ������� ������."))
        return;

    vector<ListNode*> lists(k);
    int totalLength = 0;

    for (int i = 0; i < k; ++i) {
        cout << "������ ������� �������� � ������ " << i + 1 << " (�� 0 �� 500): ";
        cin >> n;

        if (checkCin((cin.fail() || n < 0 || n > 500 || totalLength + n > 10000),
            "�������: ����������� ������� �������� � ������."))
            return;
        totalLength += n;

        vector<int> values;
        int lastVal = INT_MIN;
        cout << "������ �������� ������������� ������ (�� -10000 �� 10000): ";
        for (int j = 0; j < n; ++j) {
            cin >> val;
            if (checkCin((cin.fail() || val < -10000 || val > 10000 || val < lastVal),
                "�������: ����������� �������� �������� ��� ������ �� ������������."))
                return;
            lastVal = val;
            values.push_back(val);
        }
        lists[i] = createList(values);
    }

    ListNode* mergedList = mergeKLists(lists);
    cout << "��'������� ������: ";
    printList(mergedList);

    // ϳ��� ��������� mergeKLists, ������� ���� ��������� ������, ���� ���� �� ���� ���������� � mergedList
    for (ListNode* list : lists) {
        // ��������� ���� �����, �� �� ���� ������� �� mergedList ��� �� ���� ����� ������������, 
        // ��������� ����������� ������ ���� ��������� �� �������, ���� �� ����� ����� ������������ � mergedList.
        if (list != nullptr && list != mergedList) {
            deleteList(list);
        }
    }

    // ����� ������ �������� �������� ��'������� ������
    deleteList(mergedList);
}
void caseEightLab3() {
    vector<int> values;
    int n, val, k;

    cout << "������ ������� �������� � ������ (�� 1 �� 5000): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 1 || n > 5000),
        "�������: ����������� ������� ��������."))
        return;

    cout << "������ �������� ������ (�������� �� 0 �� 1000): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < 0 || val > 1000),
            "�������: ����������� �������� ��������."))
            return;
        values.push_back(val);
    }

    cout << "������ k (�� 1 �� " << n << "): ";
    cin >> k;
    if (checkCin((cin.fail() || k < 1 || k > n),
        "�������: ����������� �������� k."))
        return;

    ListNode* head = createList(values);
    ListNode* reversedList = reverseKGroup(head, k);

    cout << "������ ���� ��������� ���� " << k << " �����: ";
    printList(reversedList);

    deleteList(reversedList); // �������� ������ ���� ���������� ������ � ���
}
void caseNineLab3() {
    vector<int> values;
    int n, val, x;

    cout << "������ ������� �������� � ������ (�� 0 �� 200): ";
    cin >> n;
    if (checkCin((cin.fail() || n < 0 || n > 200),
        "�������: ����������� ������� ��������."))
        return;

    cout << "������ �������� ������ (-100 <= �������� <= 100): ";
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (checkCin((cin.fail() || val < -100 || val > 100),
            "�������: ����������� �������� ��������."))
            return;
        values.push_back(val);
    }

    cout << "������ �������� x (-200 <= x <= 200): ";
    cin >> x;
    if (checkCin((cin.fail() || x < -200 || x > 200),
        "�������: ����������� �������� x."))
        return;

    ListNode* head = createList(values);
    ListNode* partitioned = partition(head, x);

    cout << "��������� ������: ";
    printList(partitioned);

    deleteList(partitioned); // �������� ������ ���� ���������� ������ � ���
}


void Lab_3() {
    std::vector<std::string> menuItems = {
        "1. ��'������� ���� ������������ ��'������ ������\n",
        "2. ��������� �������� � ������������� ��'������� ������\n",
        "3. �������� �������� ����� � ��'������� ������\n",
        "4. ������������ ����� � ��'������� ������\n",
        "5. ��������� ��������� ����� � ��'������� ������\n",
        "6. �������� �����, �������������� ��'������ �������\n",
        "7. ��'������� �������� ������������ ��'������ ������\n",
        "8. ���������� ����� � k-����\n",
        "9. �������� ������\n",
        "0. ����� � ����\n"
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