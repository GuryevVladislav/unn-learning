#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Ввод строки
    string userString;
    cout << "Enter the line: ";
    getline(cin, userString);

    // Ввод числа
    int userNumber;
    cout << "Enter an integer: ";
    cin >> userNumber;

    // Ввод массива
    int arraySize;
    cout << "Enter the size of the array: ";
    cin >> arraySize;

    vector<int> userArray(arraySize); // Используем вектор для динамического массива

    cout << "Enter  " << arraySize << " integers:\n";
    for (int i = 0; i < arraySize; ++i) {
        cout << "Number " << (i + 1) << ": ";
        cin >> userArray[i];
    }

    // Вывод введенных данных
    cout << "\nYou have entered:\n";
    cout << "Line: " << userString << "\n";
    cout << "Number: " << userNumber << "\n";
    cout << "Array: ";
    for (int i = 0; i < arraySize; ++i) {
        cout << userArray[i] << (i < arraySize - 1 ? ", " : "");
    }
    cout << endl;

    return 0;
}
