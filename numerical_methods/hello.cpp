#include <iostream>
#include <string>  // Для работы со строками

int main() {
    // Ввод строки
    std::string userString;
    std::cout << "Введите строку: ";
    std::getline(std::cin, userString);  // Читаем строку, включая пробелы

    // Ввод числа
    int userNumber;
    std::cout << "Введите целое число: ";
    std::cin >> userNumber;

    // Ввод массива
    const int arraySize = 5;  // Размер массива
    int userArray[arraySize];

    std::cout << "Введите " << arraySize << " целых чисел:\n";
    for (int i = 0; i < arraySize; ++i) {
        std::cout << "Число " << (i + 1) << ": ";
        std::cin >> userArray[i];
    }

    // Вывод введенных данных
    std::cout << "\nВы ввели:\n";
    std::cout << "Строка: " << userString << "\n";
    std::cout << "Число: " << userNumber << "\n";
    std::cout << "Массив: ";
    for (int i = 0; i < arraySize; ++i) {
        std::cout << userArray[i] << (i < arraySize - 1 ? ", " : "");
    }
    std::cout << std::endl;

    return 0;
}
