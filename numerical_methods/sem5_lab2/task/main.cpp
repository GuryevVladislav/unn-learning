#include "mainTask.h"
#include "testTask.h"
#include "dataTask.h"
#include <filesystem>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string path="D:\\unn-learning\\numerical_methods\\sem5_lab2\\results\\";
    filesystem::remove(path+"results.txt");
    filesystem::remove(path+"input.txt");
    cout<< "Enter n"<<endl;
    int n;
    cin>>n;
    cout<<"Enter name task"<< endl;
    string name;
    cin>>name;
    if (name == "test") {
        TestTask test_task (n);
        TaskData data(n);
        data = test_task.calculate();
        ofstream inputFile(path+"input.txt");
        inputFile<<name<<" "<<n<<endl;
        ofstream results(path+"results.txt");
        for (int j = 0; j < n; j++) {
            results<<data.i[j]<<" "<<data.x[j]<<" "<<data.v[j]<<" "<<data.u[j]<<" "<<data.diff[j]<<endl;
        }
    }
    else {
        MainTask test_task (n);
        TaskData data(n);
        data = test_task.calculate();
        ofstream inputFile(path+"input.txt");
        inputFile<<name<<" "<<n<<endl;
        ofstream results(path+"results.txt");
        for (int j = 0; j < n; j++) {
            results<<data.i[j]<<" "<<data.x[j]<<" "<<data.v[j]<<" "<<data.x2[j]<<" "<<data.v2[j]<<" "<<data.diff[j]<<endl;
            cout<<data.i[j]<<" "<<data.x[j]<<" "<<data.v[j]<<" "<<data.x2[j]<<" "<<data.v2[j]<<" "<<data.diff[j]<<endl;
        }
    }





    return 0;
  }