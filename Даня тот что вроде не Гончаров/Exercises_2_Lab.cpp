#include "Exercises_2_Lab.h"

//1. Максимальна кількість повторень 1-ці у бінарному масиві:
int maxConsecutiveOnes(const vector<int>& nums) {
    int maxCount = 0;
    int currentCount = 0;
    for (int num : nums) {
        if (num == 1) {
            currentCount++;
            maxCount = max(maxCount, currentCount);
        }
        else {
            currentCount = 0;
        }
    }
    return maxCount;
}
//2. Кількість чисел з парною кількістю цифр:
int findNumbers(const vector<int>& nums) {
    auto countDigits = [](int num) {
        int count = 0;
        while (num) {
            count++;
            num /= 10;
        }
        return count;
        };

    int evenCount = 0;
    for (int num : nums) {
        if (countDigits(num) % 2 == 0) {
            evenCount++;
        }
    }
    return evenCount;
}
//3. Масив квадратів відсортованих чисел:
vector<int> sortedSquares(vector<int>& nums) {
    vector<int> result(nums.size());
    int l = 0;
    int r = nums.size() - 1;
    int pos = r;

    while (l <= r) {
        if (abs(nums[l]) > abs(nums[r])) {
            result[pos--] = nums[l] * nums[l];
            l++;
        }
        else {
            result[pos--] = nums[r] * nums[r];
            r--;
        }
    }
    return result;
}
//4. Дублювання нулів в масиві :
void duplicateZeros(vector<int>& arr) {
    int countZero = count(arr.begin(), arr.end(), 0);
    int n = arr.size();
    for (int i = n - 1, j = n + countZero - 1; i < j; i--, j--) {
        if (j < n) arr[j] = arr[i];
        if (arr[i] == 0 && --j < n) arr[j] = 0;
    }
}
//5. Об'єднання двох відсортованих масивів:
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;

    while (j >= 0) {
        if (i >= 0 && nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        }
        else {
            nums1[k--] = nums2[j--];
        }
    }
}
//6. Видалення дублікатів зі впорядкованого масиву:
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int k = 0;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[k]) {
            nums[++k] = nums[i];
        }
    }
    return k + 1;
}
//7. Перевірка на подвоєння значення в масиві:
bool checkIfExist(vector<int>& arr) {
    unordered_set<int> seen;
    for (int num : arr) {
        if (seen.count(num * 2) || (num % 2 == 0 && seen.count(num / 2))) {
            return true;
        }
        seen.insert(num);
    }
    return false;
}
//8. Перевірка на гірський масив:
bool validMountainArray(vector<int>& arr) {
    int i = 0, n = arr.size();
    while (i + 1 < n && arr[i] < arr[i + 1]) i++;
    if (i == 0 || i == n - 1) return false;
    while (i + 1 < n && arr[i] > arr[i + 1]) i++;
    return i == n - 1;
}
//9. Заміна кожного елементу на найбільший праворуч:
vector<int> replaceElements(vector<int>& arr) {
    int n = arr.size(), mx = -1, temp;
    for (int i = n - 1; i >= 0; --i) {
        temp = arr[i];
        arr[i] = mx;
        mx = max(mx, temp);
    }
    return arr;
}
//10. Переміщення парних чисел на початок масиву:
void moveEvenToFront(vector<int>& nums) {
    int j = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] % 2 == 0) {
            swap(nums[i], nums[j++]);
        }
    }
}


//Функції меню
void caseOneLab2()
{
    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Введіть масив 0 та 1 розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        if (nums[i] != 0 && nums[i] != 1) {
            cout << "Помилка: введені неправильні значення." << endl;
            break;
        }
    }
    int result = maxConsecutiveOnes(nums);
    cout << "Максимальна кількість повторень 1-ці: " << result << endl;
    return;
}
void caseTwoLab2()
{
    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Введіть масив чисел розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int result = findNumbers(nums);
    cout << "Кількість чисел з парною кількістю цифр: " << result << endl;
    return;
}
void caseThreeLab2()
{
    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Введіть масив чисел розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    vector<int> result = sortedSquares(nums);
    cout << "Масив квадратів відсортованих чисел: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    return;
}
void caseFourLab2()
{
    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Введіть масив чисел розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    duplicateZeros(arr);
    cout << "Дублювання нулів в масиві: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    return;
}
void caseFiveLab2()
{
    int m, n;
    cout << "Введіть розмір першого масиву: ";
    cin >> m;
    vector<int> nums1(m);
    cout << "Введіть перший масив чисел розділених пробілами: ";
    for (int i = 0; i < m; i++) {
        cin >> nums1[i];
    }
    cout << "Введіть розмір другого масиву: ";
    cin >> n;
    vector<int> nums2(n);
    cout << "Введіть другий масив чисел розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> nums2[i];
    }
    merge(nums1, m, nums2, n);
    cout << "Об'єднання двох відсортованих масивів: ";
    for (int num : nums1) {
        cout << num << " ";
    }
    cout << endl;
    return;
}
void caseSixLab2()
{
    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Введіть масив чисел розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int k = removeDuplicates(nums);
    cout << "Кількість унікальних елементів: " << k << ", nums = ";
    for (int i = 0; i < k; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;
    return;
}
void caseSevenLab2()
{
    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Введіть масив чисел розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    bool result = checkIfExist(arr);
    cout << "Чи існують два індекси i та j: " << (result ? "true" : "false") << endl;
    return;
}
void caseEightLab2()
{
    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Введіть масив чисел розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    bool result = validMountainArray(arr);
    cout << "Чи це дійсний гірський масив: " << (result ? "true" : "false") << endl;
    return;
}
void caseNineLab2()
{
    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Введіть масив чисел розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> result = replaceElements(arr);
    cout << "Заміна кожного елементу на найбільший праворуч: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    return;
}
void caseTenLab2()
{
    int n;
    cout << "Введіть розмір масиву: ";
    cin >> n;
    vector<int> nums(n);
    cout << "Введіть масив чисел розділених пробілами: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    moveEvenToFront(nums);
    cout << "Парні числа на початку масиву: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;
    return;
}


void Lab_2() {
    std::vector<std::string> menuItems = {
        "1. Максимальна кількість повторень\n",
        "2. Кількість чисел з парною кількістю цифр\n",
        "3. Масив квадратів відсортованих чисел\n",
        "4. Дублювання нулів в масиві\n",
        "5. Об'єднання двох відсортованих масивів\n",
        "6. Видалення дублікатів зі впорядкованого масиву\n",
        "7. Перевірка на подвоєння значення в масиві\n",
        "8. Перевірка на гірський масив\n",
        "9. Заміна елементів на найбільший праворуч\n",
        "10. Переміщення парних чисел на початок масиву\n",
        "0. Вихід з меню\n"
    };


    std::vector<std::function<void()>> actions = {
        []() { caseOneLab2(); },
        []() { caseTwoLab2(); },
        []() { caseThreeLab2(); },
        []() { caseFourLab2(); },
        []() { caseFiveLab2(); },
        []() { caseSixLab2(); },
        []() { caseSevenLab2(); },
        []() { caseEightLab2(); },
        []() { caseNineLab2(); },
        []() { caseTenLab2(); }
    };

    DisplayMenu(menuItems, actions);

    return;
}