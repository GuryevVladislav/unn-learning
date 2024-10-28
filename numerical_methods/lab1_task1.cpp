#include <iostream>
#include "calculateF.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <filesystem>
using namespace std;



int main() {
    int n;
    double h=0.1;
    string name;
    

    cout << "Введите количество шагов: ";
    cin >> n;
    n++;

    vector<double> x(n);
    vector<double> v(n);
    vector<vector<double>> k(n, vector<double>(5, 0));

    cout << "Введите начальное условие: ";
    cin >> v[0];

    cout<<"Введите название задачи: \n Тестовая задача - test\n Основная задача №1 - task1\n";
    cin >> name;
    x[0] = -h;

    string path="C:\\unn-learning\\";
    filesystem::remove(path+"results.txt");
    ofstream outputFile(path+"results.txt");

    for (int i = 1; i < x.size(); i++) {
        x[i] = x[i - 1] + h;
        k[i][1] = calculate_f(name, x[i], v[i-1]);
        k[i][2] = calculate_f(name, x[i] + (h/2), v[i-1] + (h/2) * k[i][1]);      
        k[i][3] = calculate_f(name, x[i] + (h/2), v[i-1] + (h/2) * k[i][2]);     
        k[i][4] = calculate_f(name, x[i] + h, v[i-1] + h * k[i][3]);        
        v[i] = v[i-1] + (h / 6) * (k[i][1] + 2 * k[i][2] + 2 * k[i][3] + k[i][4]);
        
        outputFile << x[i] << " " << v[i-1] << " " 
        << k[i][1] << " " << k[i][2] << " " << k[i][3] << " " << k[i][4] << endl;
    }

    outputFile.close();
    cout << "Данные записаны в файл results.txt" << endl;

    return 0;
}


