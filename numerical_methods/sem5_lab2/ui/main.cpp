#include "../task/mainTask.h"
#include "../task/testTask.h"
#include "dataTask.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main() {
    if (getenv("PATH_RESULTS")==""){
        cout << "PATH_RESULTS="<<getenv("PATH_RESULTS") << endl;
        return 0;
    }
    cout << "PATH_RESULTS="<<getenv("PATH_RESULTS") << endl;
    string path = getenv("PATH_RESULTS");
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
        }
    }
    return 0;
  }