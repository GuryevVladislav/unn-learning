#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "calculateF.h"
using namespace std;

int main() {
    string path="C:\\unn-learning\\numerical_methods\\sem5_lab1\\results\\";
    filesystem::remove(path+"results.txt");
    filesystem::remove(path+"initial_params.txt");

    cout<<"Enter name of task: \n Test - test\n Task 1 - task1\n Task 2 - task2\n";
    string name;
    cin >> name;
    if (name == "task1") {
        run_task1(path);
    } else if (name == "test") {
        run_test(path);
    } else if (name == "task2"){
        run_task2(path);
    } else {
         cout << "Task not found" << endl;
    }
    return 0;
}


