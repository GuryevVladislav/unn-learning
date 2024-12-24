#ifndef MAIN_TASK_H
#define MAIN_TASK_H
#include "task.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "../ui/dataTask.h"
#include <string>
using namespace std;

class MainTask {
private:
    double xi = 0.25;                                       // Кси
    double mu1 = 0.;                                       // Левая граница
    double mu2 = 1.;                                       // Правая граница
    int nodes;                                             // Число узлов

    // double k1(double x);                                   // k1, x <= xi
    // double k2(double x);                                   // k2, x >= xi
    // double q1(double x);                                   // q1, x >= xi
    // double q2(double x);                                   // q2, x <= xi
    // double f1(double x);                                   // f1, x >= xi
    // double f2(double x);                                   // f2, x <= xi
    //
    // double a(double x, double h);
    // double d(double x, double h);
    // double phi(double x, double h);
    double k1(double x)
    {
        return sqrt(x);
    }

    double k2(double x)
    {
        return x+1.;
    }

    double q1(double x)
    {
        return 1.;
    }

    double q2(double x)
    {
        return pow(x,2.);
    }

    double f1(double x)
    {
        return 1.;
    }

    double f2(double x)
    {
        return 2.+sqrt(x);
    }

    double a(double x, double h)
    {
        if (xi >= x)
        {
            return k1(x - h / 2.);
        }
        if (xi <= (x - h))
        {
            return k2(x - h / 2.);
        }
        return 1. / (1. / h * ((xi - x + h) / (k1((x - h + xi) / 2.)) + (x - xi) / (k2((xi + x) / 2.))));
    }

    double d(double x, double h)
    {
        if (xi >= (x + h / 2.))
        {
            return q1(x);
        }
        if (xi <= (x - h / 2.))
        {
            return q2(x);
        }
        return 1. / h * (q1((xi + (x - h / 2.)) / 2.) * (xi - (x - h / 2.)) + q2((xi + x + h / 2.) / 2.) * (x + h / 2 - xi));
    }

    double phi(double x, double h)
    {
        if (xi >= (x + h / 2.))
        {
            return f1(x);
        }
        if (xi <= (x - h / 2.))
        {
            return f2(x);
        }
        return 1. / h * (f1((xi + (x - h / 2.)) / 2.) * (xi - (x - h / 2.)) + f2((xi + x + h / 2.) / 2.) * (x + h / 2 - xi));
    }

public:
    // MainTask(int);
    ~MainTask() = default;

    // void calculate();
    explicit MainTask(int _nodes) : nodes(_nodes){}

TaskData calculate()
{
   vector<double> A(nodes);
    vector<double> B(nodes);
    vector<double> C(nodes);
    vector<double> Phi(nodes);
    vector<double> V(nodes);

    int nodes2 = nodes * 2 - 1;

    vector<double> A2(nodes2);
    vector<double> B2(nodes2);
    vector<double> C2(nodes2);
    vector<double> Phi2(nodes2);
    vector<double> V2(nodes2);

    double x = 0.;
    double h = 1. / (nodes - 1);
    double x2 = 0.;
    double h2 = 1. / (nodes2 - 1);

    C[0] = 1.;
    C2[0] = 1.;

    A[0] = 0.;
    A2[0] = 0.;

    B[0] = 0.;
    B2[0] = 0.;

    Phi[0] = mu1;
    Phi2[0] = mu1;

    Phi[nodes - 1] = mu2;
    Phi2[nodes2 - 1] = mu2;

    B[nodes - 1] = 0.;
    B2[nodes2 - 1] = 0.;

    A[nodes - 1] = 0.;
    A2[nodes2 - 1] = 0.;

    C[nodes - 1] = 1.;
    C2[nodes2 - 1] = 1.;

    for (int i = 1; i < (nodes - 1); i++)
    {
        x += h;
        A[i] = a(x, h) / (h * h);
        C[i] = -((a(x, h) + a(x + h, h)) / (h * h) + d(x, h));
        B[i] = a(x + h, h) / (h * h);
        Phi[i] = -phi(x, h);
    }

    for (int i = 1; i < (nodes2 - 1); i++)
    {
        x2 += h2;
        A2[i] = a(x2, h2) / (h2 * h2);
        C2[i] = -((a(x2, h2) + a(x2 + h2, h2)) / (h2 * h2) + d(x2, h2));
        B2[i] = a(x2 + h2, h2) / (h2 * h2);
        Phi2[i] = -phi(x2, h2);
    }
        TaskData data(nodes);
        Task task1(nodes);
        Task task2(nodes2);

    task1.setProgonka(A, B, C, Phi);
    task1.progonka();
    V = task1.getV();
    task2.setProgonka(A2, B2, C2, Phi2);
    task2.progonka();
    V2 = task2.getV();

    x = 0.;
        data.push(TaskData::DataType::I, 0.);
        data.push(TaskData::DataType::X, 0.);
        data.push(TaskData::DataType::X2, 0.);
        data.push(TaskData::DataType::V2, 0.);
        data.push(TaskData::DataType::V, 0.);
        data.push(TaskData::DataType::DIFF, 0.);

    for (int i = 1; i < nodes; i++)
    {
        x += h;
        data.push(TaskData::DataType::I, i);
        data.push(TaskData::DataType::X, x);
        data.push(TaskData::DataType::V, V[i]);
    }

    x2 = 0.;

    for (int i = 2; i < nodes2; i += 2)
    {
        x2 = static_cast<double>(i) * (h2);
        data.push(TaskData::DataType::X2, x2);
        data.push(TaskData::DataType::V2, V2[i]);
    }

    for (int i = 1; i < nodes; i++)
    {
        data.push(TaskData::DataType::DIFF, std::abs(V2[2 * i] - V[i]));
    }

    return data;


}
};

#endif

