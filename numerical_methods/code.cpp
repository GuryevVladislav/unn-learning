
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <filesystem>
#include <fstream>
#include <limits> // for numeric_limits

using namespace std;

// --- Function definitions ---

double calculate_f_task1(double x, double u) {
    return (x / (1 + x * x) * u * u + u - u * u * u * sin(10 * x));
}

double calculate_f_test(double x, double u) {
    return u;
}

double calculate_exp(double v, double x) {
  return v * exp(x);
}

double calculate_f2_task2(double u, double u1, double a, double b) {
    return -a * u1 - b * sin(u);
}

// --- Helper functions ---

double calculate_f(const string& functionName, double x, double u) {
    if (functionName == "task1") {
        return calculate_f_task1(x, u);
    } else if (functionName == "test") {
        return calculate_f_test(x, u);
    } else {
        cerr << "Error: Invalid function name: " << functionName << endl;
        return numeric_limits<double>::quiet_NaN(); // Return NaN to indicate error
    }
}

// Use a struct instead of a class for Result and Result2. Structs are generally preferred for simple data containers.
struct Result {
  double x;
  double v;
};

struct Result2 {
  double u;
  double u1;
  double x;
};


// --- Runge-Kutta 4th order method ---
Result runge_kutta4(const string& functionName, const Result& initial, double h) {
    vector<double> k(4);
    double x = initial.x;
    double v = initial.v;

    k[0] = calculate_f(functionName, x, v);
    k[1] = calculate_f(functionName, x + h / 2.0, v + h / 2.0 * k[0]);
    k[2] = calculate_f(functionName, x + h / 2.0, v + h / 2.0 * k[1]);
    k[3] = calculate_f(functionName, x + h, v + h * k[2]);

    v += h / 6.0 * (k[0] + 2.0 * k[1] + 2.0 * k[2] + k[3]);
    x += h;

    return {x, v};
}


Result2 runge_kutta4_task2(const string& functionName, const Result2& initial, double h, double a, double b) {
    vector<double> k(4);
    vector<double> l(4);
    double u = initial.u;
    double u1 = initial.u1;
    double x = initial.x;

    k[0] = initial.u1;
    l[0] = calculate_f2_task2(u, u1, a, b);
    k[1] = initial.u1 + (h/2.0) * l[0];
    l[1] = calculate_f2_task2(u + (h/2.0) * k[0], k[1], a, b);
    k[2] = initial.u1 + (h/2.0) * l[1];
    l[2] = calculate_f2_task2(u + (h/2.0) * k[1], k[2], a, b);
    k[3] = initial.u1 + h * l[2];
    l[3] = calculate_f2_task2(u + h * k[2], k[3], a, b);


    u += h / 6.0 * (k[0] + 2.0 * k[1] + 2.0 * k[2] + k[3]);
    u1 += h / 6.0 * (l[0] + 2.0 * l[1] + 2.0 * l[2] + l[3]);
    x += h;

    return {u, u1, x};
}


// --- File I/O functions ---

bool write_params_to_file(const string& filepath, int n, double e, double b, double initialValue) {
    ofstream paramsFile(filepath);
    if (paramsFile.is_open()) {
        paramsFile << n << " " << e << " " << b << " " << initialValue << endl;
        return paramsFile.good();
    } else {
        cerr << "Error: Unable to open file for writing: " << filepath << endl;
        return false;
    }
}

bool write_results_to_file(const string& filepath, const vector<vector<double>>& results) {
    ofstream outputFile(filepath);
    if (outputFile.is_open()) {
        for (const auto& row : results) {
            for (double val : row) {
                outputFile << val << " ";
            }
            outputFile << endl;
        }
        return outputFile.good();
    } else {
        cerr << "Error: Unable to open file for writing: " << filepath << endl;
        return false;
    }
}


// --- Main simulation functions ---

bool run_simulation(const string& functionName, const string& path, int n, double e, double b, double initialValue) {
    double h = b / n; 
    Result currentResult = {0.0, initialValue};
    vector<vector<double>> results;
    results.push_back({0.0, currentResult.x, currentResult.v});

    for (int i = 1; i <= n; ++i) {
        int c1 = 0, c2 = 0;
        bool ok = false;
        Result result; // Объявление result здесь

        while (!ok) {
            result = runge_kutta4(functionName, currentResult, h);
            if (e != 0) {
                Result result05 = runge_kutta4(functionName, currentResult, h / 2.0);
                Result result2 = runge_kutta4(functionName, result05, h / 2.0);
                double s = (result2.v - result05.v) / 15.0;
                if ((e / 31.0 < abs(s)) && (abs(s) < e)) {
                    ok = true;
                    currentResult = result;
                } else if (abs(s) < e / 32.0) {
                    h *= 2.0;
                    c2++;
                    ok = true;
                    currentResult = result;
                } else {
                    c1++;
                    ok = false;
                    h /= 2.0;
                    if (c1 > 100 || c2 > 100) {
                        cerr << "Error: Too many iterations. c1: " << c1 << ", c2: " << c2 << endl;
                        return false;
                    }
                }
            } else {
                ok = true;
                currentResult = result;
            }
        }
        double olp = 16.0 * (result.v - currentResult.v) / 15.0; // Исправлено деление
        results.push_back({(double)i, currentResult.x, currentResult.v, olp, h, (double)c1, (double)c2});
    }
    return write_results_to_file(path + "results.txt", results);
}



bool run_simulation_task2(const string& functionName, const string& path, int n, double e, double r, double initialU, double initialU1, double a, double b) {
    double h = r / n;
    Result2 currentResult = {initialU, initialU1, 0.0};
    vector<vector<double>> results;
    results.push_back({0, currentResult.x, currentResult.u, currentResult.u1});

    for (int i = 1; i <= n; ++i) {
        int c1 = 0, c2 = 0;
        bool ok = false;
        while (!ok) {
            Result2 result = runge_kutta4_task2(functionName, currentResult, h, a, b);
            if (e != 0) {
                Result2 result05 = runge_kutta4_task2(functionName, currentResult, h / 2.0, a, b);
                Result2 result2 = runge_kutta4_task2(functionName, result05, h / 2.0, a, b);
                double s = (result2.u - result05.u) / 15.0;
                if ((e / 31.0 < abs(s)) && (abs(s) < e)) {
                    ok = true;
                    currentResult = result;
                } else if (abs(s) < e / 32.0) {
                    h *= 2.0;
                    c2++;
                    ok = true;
                    currentResult = result;
                } else {
                    c1++;
                    ok = false;
                    h /= 2.0;
                    if (c1 > 100 || c2 > 100) {
                        cerr << "Error: Too many iterations. c1: " << c1 << ", c2: " << c2 << endl;
                        return false;
                    }
                }
            } else {
                ok = true;
                currentResult = result;
            }
        }
        results.push_back({(double)i, currentResult.x, currentResult.u, currentResult.u1, (double)c1, (double)c2});
    }
    return write_results_to_file(path + "results.txt", results);
}

// --- Main function ---

int main() {
    string path = "D:\\unn-learning\\numerical_methods\\results\\";
    filesystem::remove_all(path); // Remove directory and its contents
    filesystem::create_directory(path); //Create empty directory

    cout << "Enter name of task: \n Test - test\n Task 1 - task1\n Task 2 - task2\n";
    string taskName;
    cin >> taskName;

    if (taskName == "task1") {
        int n;
        double e, b, v0;
        cout << "Enter number of steps (n): ";
        cin >> n;
        cout << "Enter e: ";
        cin >> e;
        cout << "Enter right boundary (b): ";
        cin >> b;
        cout << "Enter initial condition (v0): ";
        cin >> v0;
        if(!run_simulation("task1", path, n, e, b, v0)) return 1;
    } else if (taskName == "test") {
        int n;
        double e, b, v0;
        cout << "Enter number of steps (n): ";
        cin >> n;
        cout << "Enter e: ";
        cin >> e;
        cout << "Enter right boundary (b): ";
        cin >> b;
        cout << "Enter initial condition (v0): ";
        cin >> v0;
        if(!run_simulation("test", path, n, e, b, v0)) return 1;
    } else if (taskName == "task2") {
        int n;
        double e, r, initialU, initialU1, a, b;
        cout << "Enter number of steps (n): ";
        cin >> n;
        cout << "Enter e: ";
        cin >> e;
        cout << "Enter right boundary (r): ";
        cin >> r;
        cout << "Enter initial u(0): ";
        cin >> initialU;
        cout << "Enter initial u'(0): ";
        cin >> initialU1;
        cout << "Enter a: ";
        cin >> a;
        cout << "Enter b: ";
        cin >> b;
        if(!run_simulation_task2("task2", path, n, e, r, initialU, initialU1, a, b)) return 1;
    } else {
        cout << "Task not found" << endl;
    }
    cout << "Simulation complete." << endl;
    return 0;
}
