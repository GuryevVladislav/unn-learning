#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <filesystem>
#include <fstream>
using namespace std;

double calculate_f_task1(double x,double u) {
    return (x / (1 + x * x) * u * u + u - u * u * u * sin(10 * x));
}

double calculate_f_test(double x,double u) {
    return u;
}

double calculate_f(string name, double x, double u) {

    if (name == "task1") {
           return calculate_f_task1(x, u);
       } else if (name == "test") {
           return calculate_f_test(x, u);
       } else {
           cout << "Неверное имя функции" << endl;
           return 0;
       }
}

double calculate_exp(double v, double x) {
  return v * exp(x);
}

class Result {
public:
  double x;
  double v;
};

Result calculate_result(string name,Result result, double h) {
    vector<double> k(5);
    double x,v;
    x=result.x;
    v=result.v;

    k[1] = calculate_f(name, x, v);
    k[2] = calculate_f(name, x + (h/2), v + (h/2) * k[1]);      
    k[3] = calculate_f(name, x + (h/2), v + (h/2) * k[2]);     
    k[4] = calculate_f(name, x + h, v + h * k[3]);       
    v = v + (h / 6) * (k[1] + 2 * k[2] + 2 * k[3] + k[4]);
    x=x+h;

    result.x = x;
    result.v = v;

  return result;
}

int run_task1(string path) {
    int n,count=0;
    double v2, x2, b, e, h, olp,s, vCheck, a;
    string name;
    vector<double> k(5);
    vector<double> k2(5);
    Result result0,result,result05, result2;;
result0.x=0;

    cout << "Enter number of steps(n): ";
    cin >> n;
    
    cout<< "Enter e: ";
    cin >> e;
    cout << "Enter right boundary(b): ";
    cin >> b;
    cout << "Enter initial condition(v0): ";
    cin >> result0.v;
    a=result0.v;
    
    ofstream paramsFile(path+"initial_params.txt");
    paramsFile << n << " " << e << " " << b << " " << a << endl;
    paramsFile.close();

    name="task1";
    h = (b - result0.x) / n;
    n++;

    ofstream outputFile(path+"results.txt");
    outputFile << count << " "<< result0.x << " " << result0.v << " " << 0 << " "<< 0 << " " << 0 << " " << 0 << " " << 0 << " " << 0 << " " <<endl;
        

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
        
        outputFile << count << " "<< result0.x << " " << result0.v << " " << result2.v << " "<<  result0.v-result2.v << " " << olp << " " << h << " " << c1 << " " << c2  << " " << endl;
    }

    

    outputFile.close();
    cout << "Results saved in results.txt" << endl;

    return 0;
}

int run_test(string path) {
    int n,count=0;
    double v2, x2, b, e, h, olp,s, vCheck, a;
    string name;
    vector<double> k(5);
    vector<double> k2(5);
    Result result0,result,result05, result2;;
    result0.x=0;

    cout << "Enter number of steps(n): ";
    cin >> n;
    
    cout<< "Enter e: ";
    cin >> e;
    cout << "Enter right boundary(b): ";
    cin >> b;
    cout << "Enter initial condition(v0): ";
    cin >> result0.v;
    a=result0.v;
    ofstream paramsFile(path+"initial_params.txt");
    if (paramsFile.is_open()) {
        paramsFile << n << " " << e << " " << b << " " << a << endl;
        paramsFile.close();
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
    name="test";

    h = (b - result0.x) / n;
    n++;

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
    cout << "Results saved in results.txt" << endl;

    return 0;
}