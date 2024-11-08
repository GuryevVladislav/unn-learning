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

double calculate_exp(double a, double x) {
  return a * exp(x);
}