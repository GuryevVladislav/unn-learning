#ifndef TESTTASK_H
#define TESTTASK_H
#include "dataTask.h"
#include "task.h"
#include <cmath>

class TestTask {
private:
    double k1 = 0.5;                        // x <= xi
    double k2 = 1.25;                       // x >= xi
    double f1 = 1.;                         // x <= xi
    double f2 = 2.5;                        // x >= xi
    double q1 = 1.;                         // x <= xi
    double q2 = 0.0625;                     // x => xi
    double ksi = 0.25;                       // Кси
    double mu1 = 0.;                        // Левая граница
    double mu2 = 1.;                        // Правая граница
    int nodes;


    // double a(double x, double h);
    // double d(double x, double h);
    // double phi(double x, double h);
    double a(double x, double h)
{
    if (ksi >= x)
    {
        return k1;
    }
    if (ksi <= (x - h))
    {
        return k2;
    }
    return 1. / (1. / h * ((ksi - x + h) / k1 + (x - ksi) / k2));
}

double d(double x, double h)
{
    if (ksi >= (x + h / 2.))
    {
        return q1;
    }
    if (ksi <= (x - h / 2.))
    {
        return q2;
    }
    return 1. / h * (q1 * (ksi - (x - h / 2.)) + q2 * (x + h / 2 - ksi));
}

double phi(double x, double h)
{
    if (ksi >= (x + h / 2.))
    {
        return f1;
    }
    if (ksi <= (x - h / 2.))
    {
        return f2;
    }
    return 1. / h * (f1 * (ksi - (x - h / 2.)) + f2 * (x + h / 2 - ksi));
}



public:
    explicit TestTask(const int nodes): nodes(nodes) {};
    ~TestTask() = default;
    TaskData calculate()
{
    double x = 0.;
    double h = 1. / (nodes - 1);

    std::vector<double> A(nodes);
    std::vector<double> B(nodes);
    std::vector<double> C(nodes);
    std::vector<double> Phi(nodes);
    std::vector<double> V(nodes);

    C[0] = 1.;
    A[0] = 0.;
    B[0] = 0.;
    Phi[0] = mu1;
    Phi[nodes - 1] = mu2;
    C[nodes - 1] = 1.;
    A[nodes - 1] = 0.;
    B[nodes - 1] = 0.;

    for (int i = 1; i < (nodes - 1); i++)
    {
        x += h;
        A[i] = a(x, h) / (h * h);
        C[i] = -((a(x, h) + a(x + h, h)) / (h * h) + d(x, h));
        B[i] = a(x + h, h) / (h * h);
        Phi[i] = -phi(x, h);
    }
    TaskData data(nodes);
    Task task1(nodes);
    task1.setProgonka(A, B, C, Phi);
    task1.progonka();
    V = task1.getV();

    data.push(TaskData::DataType::I, 0.);
    data.push(TaskData::DataType::X, 0.);
    data.push(TaskData::DataType::U, 0.);
    data.push(TaskData::DataType::V, 0.);
    data.push(TaskData::DataType::DIFF, 0.);



    x = 0.0;
    double u;
    double C1 = 0.58744204;
    double C2 = -1.58744204;
    double C3 = -16.23731987;
    double C4 = -23.37825944;

    for (int i = 1; i < nodes; i++)
    {
        x += h;
        data.push(TaskData::DataType::I, i);
        data.push(TaskData::DataType::X, x);
        data.push(TaskData::DataType::V, V[i]);

        if (i == nodes) u = 0.;
        else if (x < ksi)
            u = C1*pow( M_E, sqrt(2.)*x)+C2*pow( M_E, -sqrt(2.)*x)+1.;
        else
            u = C3*pow( M_E, sqrt(0.05)*x)+C4*pow( M_E, -sqrt(0.05)*x)+40.;

            data.push(TaskData::DataType::U, u);
            data.push(TaskData::DataType::DIFF, std::abs(u - V[i]));
    }

    return data;
}
};
#endif