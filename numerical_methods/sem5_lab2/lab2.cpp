#include "lab2.h"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace std;

const double ξ =0.25;
const double μ1=0.0;
const double μ2=1.0;
const double ε=0.0000005;

int task() {
    double n,h;
    cout <<"Enter n :"<<endl;
    cin>>n;
    h=1/n;
    vector<double> a(n);
    vector<double> d(n-1);
    vector<double> φ(n);
    vector<double> α(n);
    vector<double> β(n);
    vector<double> v(n);
    vector<double> v2(2*n);

    X x (h);
    for (int i=1;i<=n;i++){
        if (x.get(i) < ξ) {
            a[i] = 1 / ((1 / h) * (2 * (sqrt(x.get(i)) - sqrt(x.get(i-1)))));
            d[i] = (1 / h) * (x.get(i+0.5) - x.get(i-0.5));//todo
            φ[i] = (1 / h) * (x.get(i+0.5) - x.get(i-0.5));
        } else {
            a[i] = 1 / ((1 / h) * (log(x.get(i) + 1) - log(x.get(i-1) + 1)));
            d[i] = (1 / h) * (pow(x.get(i+0.5), 3) / 3 - pow(x.get(i-0.5), 3) / 3);//todo
            φ[i] = (2 / h) * (pow(x.get(i+0.5), 3.0 / 2) / 3 + x.get(i+0.5) - pow(x.get(i-0.5), 3.0 / 2) / 3 - x.get(i-0.5));
        }
    }

    α[0] = 1;
    β[0] = 0;
    for (int i=0;i<n;i++){
        α[i+1] = (a[i+1]/pow(h,2))/((a[i]+a[i+1])/pow(h,2)+d[i]-a[i]/pow(h,2)*α[i]);
        β[i+1]= (φ[i]+a[i]*β[i]/pow(h,2))/((a[i]+a[i+1])/pow(h,2)+d[i]-a[i]/pow(h,2)*α[i]);
    }


    v[n]=(-β[n]-1)/α[n]-1;
    for (int i=n-1; i>0; i--){
        v[i] = α[i+1]+v[i+1]+β[i+1];
    }

    return 0;
  }

int test() {
    double n,h;
    cout <<"Enter n :"<<endl;
    cin>>n;
    h=1/n;
    vector<double> a(n);
    vector<double> d(n);
    vector<double> φ(n);
    vector<double> α(n);
    vector<double> β(n);
    vector<double> v(n);

    X x (h);

    for (int i=1;i<=n;i++){
        if (x.get(i) < ξ) {
            a[i] = 2;
            d[i] = 1;
            φ[i] = 1;
        } else {
            a[i] = 0.8;
            d[i] = 0.0625;
            φ[i] = 2.5;
        }
    }
    α[0] = 1;
    β[0] = 0;
    for (int i=0;i<n;i++){
        α[i+1] = (a[i+1]/pow(h,2))/((a[i]+a[i+1])/pow(h,2)+d[i]-a[i]/pow(h,2)*α[i]);
        β[i+1]= (φ[i]+a[i]*β[i]/pow(h,2))/((a[i]+a[i+1])/pow(h,2)+d[i]-a[i]/pow(h,2)*α[i]);
    }
    v[n]=(-β[n]-1)/α[n]-1;
    for (int i=n-1; i>0; i--){
        v[i] = α[i+1]+v[i+1]+β[i+1];
    }

    return 0;
}