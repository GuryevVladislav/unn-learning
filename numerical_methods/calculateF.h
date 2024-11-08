#include <iostream>
#include <vector>
#include <cmath>
#include <string>
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