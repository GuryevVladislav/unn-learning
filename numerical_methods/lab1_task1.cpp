#include <iostream>
#include "calculateF.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <filesystem>
using namespace std;



int main() {
    int n,count=0;
    double v2, x2, b, e, h, olp,s, vCheck, a;
    string name;
    vector<double> k(5);
    vector<double> k2(5);
    Result result0,result,result05, result2;;
result0.x=0;

    cout << "Введите количество шагов: ";
    cin >> n;
    
    cout<< "Введите e: ";
    cin >> e;
    cout << "Введите правую границу: ";
    cin >> b;
    cout << "Введите начальное условие: ";
    cin >> result0.v;
    a=result0.v;
    cout<<"Введите название задачи: \n Тестовая задача - test\n Основная задача №1 - task1\n";
    cin >> name;

    h = (b - result0.x) / n;
    n++;

    string path="D:\\unn-learning\\";
    filesystem::remove(path+"results.txt");
    ofstream outputFile(path+"results.txt");
    outputFile << count << " "<< result0.x << " " << result0.v << " " << 0 << " "<< 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 <<" " << 0 <<endl;
        

    for (int i = 1; i < n; i++) {
        int c1=0, c2=0;
        bool ok= false;
        while (!ok) {
            result=calculate_result(name,result0, h);
            result05=calculate_result(name,result0, h/2);
            result2=calculate_result(name, result05, h/2);

            s=(result2.v-result05.v)/15;

            if ((e/31<abs(s)) && (abs(s)<e)) {
                ok=true;  
                result0=result;
            }
            if (abs(s)<e/32) {
                h=2*h;
                c2++;
                ok=true;
                result0=result;
            }
            if (abs(s)>e) {
                c1++;
                ok=false;
                h=h/2;
            }
        }
        olp= 16*s;
        count++;
        
        outputFile << count << " "<< result0.x << " " << result0.v << " " << result2.v << " "<<  result0.v-result2.v << " " << olp << " " << h << " " << c1 << " " << c2 <<" " << calculate_exp(a, result0.x) << " " << abs(calculate_exp(a, result0.x) - result0.v) << " " << endl;
    }

    

    outputFile.close();
    cout << "Данные записаны в файл results.txt" << endl;

    return 0;
}
