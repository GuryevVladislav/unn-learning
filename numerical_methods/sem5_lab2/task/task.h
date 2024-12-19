#ifndef TASK_H
#define TASK_H

#include <cmath>
#include <vector>
class Task
{
protected:
    std::vector<double> A;                                 // Левый элемент от диагонали
    std::vector<double> C;                                 // Диагональ
    std::vector<double> B;                                 // Правый элемент от диагонали
    std::vector<double> V;                                 // Вектор приближенных решений краевой задачи
    std::vector<double> Phi;                               // Правая часть СЛАУ
    std::vector<double> alpha;                             // Вектор альф для метода прогонки
    std::vector<double> beta;                              // Вектор бет для метода прогонки
    int nodes;                                             // Количество участков сетки()

public:
    // Task(int);                         // Конструктор, принимающий количество узлов сетки, включая нулевой
    // ~Task() {}
    explicit Task(const int n) : nodes(n)
    {
        V.resize(nodes);
        Phi.resize(nodes);
        A.resize(nodes);
        B.resize(nodes);
        C.resize(nodes);
        alpha.resize(nodes, 0.);
        beta.resize(nodes, 0);

    }

private:
    // void normalization();              // Нормировка матрицы
    // void progonkaDirect();             // Прямой ход прогонки
    // void progonkaReverse();            // Обратный ход прогонки
    void normalization()
    {
        B[0] /= C[0];
        Phi[0] /= C[0];
        C[0] = 1.;

        A[nodes - 1] /= C[nodes - 1];
        Phi[nodes - 1] /= C[nodes - 1];
        C[nodes - 1] = 1.;
    }

    void progonkaDirect()
    {
        alpha[1] = -B[0];
        beta[1] = Phi[0];

        for (int i = 1; i < (nodes - 1); i++)
        {
            alpha[i + 1] = B[i] / (-C[i] - alpha[i] * A[i]);
            beta[i + 1] = (-Phi[i] + A[i] * beta[i]) / (-C[i] - alpha[i] * A[i]);
        }
    }

    void progonkaReverse()
    {
        V[nodes - 1] = (A[nodes - 1] * beta[nodes - 1] - Phi[nodes - 1]) / (-A[nodes - 1] * alpha[nodes - 1] - 1.);

        for (int i = nodes - 2; i >= 0; i--)
        {
            V[i] = alpha[i + 1] * V[i + 1] + beta[i + 1];
        }
    }

public:
//     void progonka();                   // Метод прогонки
//     void resize(int n);                // Изменение полей
//     void setProgonka(const std::vector<double>& _A, const std::vector<double>& _B,
//                      const std::vector<double>& _C, const std::vector<double>& _Phi);
//
//     std::vector<double> getV();
    void progonka()
    {
        progonkaDirect();
        progonkaReverse();
    }
    void resize(int n)
    {
        nodes = n;
        V.resize(nodes, 0.);
        Phi.resize(nodes, 0.);
        A.resize(nodes, 0.);
        B.resize(nodes, 0.);
        C.resize(nodes, 0.);
        alpha.resize(nodes, 0.);
        beta.resize(nodes, 0);
    }
    void setProgonka(const std::vector<double> &_A, const std::vector<double> &_B,
                       const std::vector<double> &_C, const std::vector<double> &_Phi)
    {
        A = _A;
        B = _B;
        C = _C;
        Phi = _Phi;
    }
    std::vector<double> getV()
    {
        return V;
    }
};
#endif









