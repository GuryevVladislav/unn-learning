#include <iostream>
#include "calculateF.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <filesystem>
using namespace std;



int main() {
    int n,count=0;
    double v2, x2, x, v, b, e, h, olp,s, vCheck, a;
    string name;
    vector<double> k(5);
    vector<double> k2(5);

    cout << "Введите количество шагов: ";
    cin >> n;
    n++;
    cout<< "Введите e: ";
    cin >> e;
    cout << "Введите правую границу: ";
    cin >> b;
    cout << "Введите начальное условие: ";
    cin >> v;
    a=v;
    cout<<"Введите название задачи: \n Тестовая задача - test\n Основная задача №1 - task1\n";
    cin >> name;

    h = (b - x) / (n - 1);
    x = 0;

    string path="C:\\unn-learning\\";
    filesystem::remove(path+"results.txt");
    ofstream outputFile(path+"results.txt");
    outputFile << count << " "<< x << " " << v << " " << 0 << " "<< 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 <<" " << 0 <<endl;
        

    for (int i = 1; i < n; i++) {
        int c1=0, c2=0;
        bool ok= false;
        while (!ok) {
            k[1] = calculate_f(name, x, v);
            k[2] = calculate_f(name, x + (h/2), v + (h/2) * k[1]);      
            k[3] = calculate_f(name, x + (h/2), v + (h/2) * k[2]);     
            k[4] = calculate_f(name, x + h, v + h * k[3]);

            v2=v; 
            x2=x;       
            vCheck = v + (h / 6) * (k[1] + 2 * k[2] + 2 * k[3] + k[4]);
            h=h/2;
            
            for (int j = 1; j < 3;  j++) {
                k2[1] = calculate_f(name, x2, v2);
                k2[2] = calculate_f(name, x2 + (h/2), v2 + (h/2) * k2[1]);      
                k2[3] = calculate_f(name, x2 + (h/2), v2 + (h/2) * k2[2]);     
                k2[4] = calculate_f(name, x2 + h, v2 + h * k[3]);        
                v2 = v2 + (h / 6) * (k2[1] + 2 * k2[2] + 2 * k2[3] + k2[4]);
                x2 = x2 + h;
            }

            s=(v2-vCheck)/15;

            if ((e/31<abs(s)) && (abs(s)<e)) {
                ok=true;  
                v= vCheck;
                h=2*h;
            }
            if (abs(s)<e/32) {
                h=4*h;
                c2++;
                ok=true;
                v=vCheck;
            }
            if (abs(s)>e) {
                c1++;
                ok=false;
            }
        }
        olp= 16*s;
        count++;
        
        outputFile << count << " "<< x << " " << v << " " << v2 << " "<< v-v2 << " " << olp << " " << h << " " << c1 << " " << c2 << calculate_exp(a, x) << " " << abs(calculate_exp(a, x) - v) << " " << endl;
        x =x + h;
    }

    

    outputFile.close();
    cout << "Данные записаны в файл results.txt" << endl;

    return 0;
}
