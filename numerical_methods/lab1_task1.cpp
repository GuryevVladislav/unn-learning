#include <iostream>
#include "calculateF.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <locale>
using namespace std;

int main() {
    string path="D:\\unn-learning\\numerical_methods\\results\\";
    filesystem::remove(path+"results.txt");
    filesystem::remove(path+"initial_params.txt");

    cout<<"Enter name of task: \n Test - test\n Task №1 - task1\n";
    string name;
    cin >> name;
    if (name == "task1") {
        run_task1(path);
    } else if (name == "test") {
        run_test(path);
    } else {
        cout << "Такой задачи нет" << endl;
    }
    return 0;
}


