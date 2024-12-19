#include "testTask.h"
#include <vector>
#include <tuple>
#include <cmath>
#include <stdexcept>

//double TestTask::a(double x, double h)
//{
//    if (xi >= x)
//    {
//        return k1;
//    }
//    else if (xi <= (x - h))
//    {
//        return k2;
//    }
//    else
//    {
//        return 1. / (1. / h * ((xi - x + h) / k1 + (x - xi) / k2));
//    }
//}
//
//double TestTask::d(double x, double h)
//{
//    if (xi >= (x + h / 2.))
//    {
//        return q1;
//    }
//    else if (xi <= (x - h / 2.))
//    {
//        return q2;
//    }
//    else
//    {
//        return 1. / h * (q1 * (xi - (x - h / 2.)) + q2 * (x + h / 2 - xi));
//    }
//}
//
//double TestTask::phi(double x, double h)
//{
//    if (xi >= (x + h / 2.))
//    {
//        return f1;
//    }
//    else if (xi <= (x - h / 2.))
//    {
//        return f2;
//    }
//    else
//    {
//        return 1. / h * (f1 * (xi - (x - h / 2.)) + f2 * (x + h / 2 - xi));
//    }
//}
//
//TaskData TestTask::calculate()
//{
//    double x = 0.;
//    double h = 1. / (nodes - 1);
//
//    std::vector<double> A(nodes);
//    std::vector<double> B(nodes);
//    std::vector<double> C(nodes);
//    std::vector<double> Phi(nodes);
//    std::vector<double> V(nodes);
//
//    C[0] = 1.;
//    A[0] = 0.;
//    B[0] = 0.;
//    Phi[0] = mu1;
//    Phi[nodes - 1] = mu2;
//    C[nodes - 1] = 1.;
//    A[nodes - 1] = 0.;
//    B[nodes - 1] = 0.;
//
//    //table->setRowCount(nodes);
//
//    for (int i = 1; i < (nodes - 1); i++)
//    {
//        x += h;
//        A[i] = a(x, h) / (h * h);
//        C[i] = -((a(x, h) + a(x + h, h)) / (h * h) + d(x, h));
//        B[i] = a(x + h, h) / (h * h);
//        Phi[i] = -phi(x, h);
//    }
//    TaskData data(nodes);
//    Task task1(nodes);
//    task1.setProgonka(A, B, C, Phi);
//    task1.progonka();
//    V = task1.getV();
//
////    *series << QPointF(0., 1.);
////    *seriesTrue << QPointF(0., 1.);
////    *raz << QPointF(0., 0.);
////    table->setItem(0, 0, new QTableWidgetItem(QString::number(0.)));
////    table->setItem(0, 1, new QTableWidgetItem(QString::number(0.)));
////    table->setItem(0, 2, new QTableWidgetItem(QString::number(1.)));
////    table->setItem(0, 3, new QTableWidgetItem(QString::number(1.)));
////    table->setItem(0, 4, new QTableWidgetItem(QString::number(1. - 1.)));
//    data.push(TaskData::DataType::I, 0.);
//    data.push(TaskData::DataType::X, 0.);
//    data.push(TaskData::DataType::U, 1.);
//    data.push(TaskData::DataType::V, 1.);
//    data.push(TaskData::DataType::DIFF, 1.-1.);
//
//
//
//    x = 0.0;
//    double u;
//    double C1 = -8.9594;
//    double C2 = -7.9594;
//    double C3 = -0.1171;
//    double C4 = -48.9557;
//
//    for (int i = 1; i < nodes; i++)
//    {
//        x += h;
////        *series << QPointF(x, V[i]);
//        data.push(TaskData::DataType::I, i);
//        data.push(TaskData::DataType::X, x);
//        data.push(TaskData::DataType::V, V[i]);
////        table->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
////        table->setItem(i, 1, new QTableWidgetItem(QString::number(x)));
////        table->setItem(i, 3, new QTableWidgetItem(QString::number(V[i])));
//
//        if (i == nodes - 1) u = 0.;
//        else if (x < xi)
//            u = C1*pow( M_E, sqrt(2.)*x)+C2*pow( M_E, -sqrt(2.)*x)+1.;
//        else
//            u = C3*pow( M_E, sqrt(0.05)*x)-C4*pow( M_E, -sqrt(0.05)*x)+40.;
//
////        *seriesTrue << QPointF(x, u);
////
////        table->setItem(i, 2, new QTableWidgetItem(QString::number(u)));
////        table->setItem(i, 4, new QTableWidgetItem(QString::number(abs(u - V[i]))));
////        *raz << QPointF(x, fabs(u - V[i]) * 1e10);
//            data.push(TaskData::DataType::U, u);
//            data.push(TaskData::DataType::DIFF, std::abs(u - V[i]));
//    }
//
//    return data;
//}
