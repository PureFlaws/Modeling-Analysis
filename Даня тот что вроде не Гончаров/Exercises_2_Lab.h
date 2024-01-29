#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>

#include"windows.h"
#include "classes.h"
#include "Menu.h"

using namespace std;
//1. Максимальна кількість повторень 1-ці у бінарному масиві:
int maxConsecutiveOnes(const vector<int>& nums);
//2. Кількість чисел з парною кількістю цифр:
int findNumbers(const vector<int>& nums);
//3. Масив квадратів відсортованих чисел:
vector<int> sortedSquares(vector<int>& nums);
//4. Дублювання нулів в масиві :
void duplicateZeros(vector<int>& arr);
//5. Об'єднання двох відсортованих масивів:
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);
//6. Видалення дублікатів зі впорядкованого масиву:
int removeDuplicates(vector<int>& nums);
//7. Перевірка на подвоєння значення в масиві:
bool checkIfExist(vector<int>& arr);
//8. Перевірка на гірський масив:
bool validMountainArray(vector<int>& arr);
//9. Заміна кожного елементу на найбільший праворуч:
vector<int> replaceElements(vector<int>& arr);
//10. Переміщення парних чисел на початок масиву:
void moveEvenToFront(vector<int>& nums);

//Функції меню
void caseOneLab2();
void caseTwoLab2();
void caseThreeLab2();
void caseFourLab2();
void caseFiveLab2();
void caseSixLab2();
void caseSevenLab2();
void caseEightLab2();
void caseNineLab2();
void caseTenLab2();

void Lab_2();