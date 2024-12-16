#include <iostream>
#include <vector>
#include <cmath>
#include <string>

class X {
private:
    double h;
public:
    // Конструктор (инициализирует h)
    X(double initialH) : h(initialH) {}

    // Метод для умножения h на i
    double get(double i) {
        return h * i;
    }
};

double k1(double x){
    return sqrt(x);
}

double k2(double x){
    return x+1;
}

double q1(double x){
    return 1;
}

double q2(double x){
    return x*x;
}

double f1(double x){
    return 1;
}

double f2(double x){
  return 2+sqrt(x);
}