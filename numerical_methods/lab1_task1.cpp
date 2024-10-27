#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <filesystem>
using namespace std;

double calculate_f(double x,double u) {
    return (x / (1 + x * x) * u * u + u - u * u * u * sin(10 * x));
}

int main() {
    int n;
    double h=0;
    
    
    cout << "Введите количество шагов: ";
    cin >> n;
    n++;
    vector<double> x(n);
    vector<double> v(n);
    vector<vector<double>> k(n, vector<double>(5, 0));
    cout << "Введите начальное условие: ";
    cin >> v[0];
    x[0] = 0;
    ofstream outputFile("D:\\unn-learning\\numerical_methods\\results.txt");
    
    

    for (int i = 1; i < x.size(); i++) {
        x[i] = x[i - 1] + h;
        h=h+0.1;
        k[i][1] = calculate_f(x[i] + (h/2), v[i-1]);
        k[i][2] = calculate_f(x[i] + (h/2), v[i-1] + (h/2) * k[i][1]);      
        k[i][3] = calculate_f(x[i] + h, v[i-1] + (h/2) * k[i][2]);     
        k[i][4] = calculate_f(x[i], v[i-1] + h * k[i][3]);        
        v[i] = v[i-1] + (h / 6) * (k[i][1] + 2 * k[i][2] + 2 * k[i][3] + k[i][4]);
        
        outputFile << x[i] << " " << k[i][1] << " " << k[i][2] << " " << k[i][3] << " " << k[i][4] << " " << v[i] << endl;
    }


    outputFile.close();
    cout << "Данные записаны в файл results.txt" << endl;

    return 0;
}


