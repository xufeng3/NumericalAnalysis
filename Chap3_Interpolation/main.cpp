#include <iostream>
#include <vector>
#include <ctime>
#include "test3.h"
#include "interpolation.h"
#include <functional>
#include <algorithm>
using std::vector, std::cout, std::cin, std::exp, std::sort;

template<typename F>
double recordTime(F f, int repeat = 1){
    std::clock_t t;
    t = std::clock();
    for (int repeat_ = 0; repeat_ < repeat; repeat_++){
        auto&& res = f();
    }
    t = std::clock() - t;
    cout<<(double)(t)/CLOCKS_PER_SEC<<",";
    return (double)(t)/CLOCKS_PER_SEC;
}

static double f(double x) { return exp(x); }
static double f1(double x) { return exp(x); }

int main() {

    // generate random data to test efficiency
    for(int len=100; len<=100; len+=20){
        cout << len << ",";
        vector<double> xList4;
        vector<double> yList4;
        vector<double> deList4;
        for (int i=0; i<len; i++){
            xList4.push_back(((double) rand() / (RAND_MAX)));
            sort(xList4.begin(), xList4.end());
            xList4.erase(unique(xList4.begin(), xList4.end()), xList4.end());
        }

        cout << xList4.size() << ",";

        for (int i=0; i<xList4.size(); i++){
            yList4.push_back(((double) rand() / (RAND_MAX)));
            deList4.push_back(((double) rand() / (RAND_MAX)));
        }
        int repeat = 50;
        recordTime([xList4, yList4]{return Interpolation::lagrange(xList4, yList4);}, repeat);
        recordTime([xList4, yList4]{return Interpolation::neville(xList4, yList4);}, repeat);
        recordTime([xList4, yList4]{return Interpolation::newton(xList4, yList4);}, repeat);
        recordTime([xList4, yList4, deList4]{return Interpolation::hermite(xList4, yList4, deList4);}, repeat);
        cout << endl;
    }


//    vector<double> xList = {1., 2., 3., 4.};
//    vector<double> yList = {1., 4., 9., 16.};
//    vector<double> deList = {2., 4., 6., 8.};

//    vector<double> xList = {1., 2., 3., 4.,};
//    vector<double> yList = {f(1.), f(2.), f(3.), f(4.)};
//    vector<double> deList = {f1(1.), f1(2.), f1(3.), f1(4.)};

    // p119 3c
//    vector<double> xList = {0.1, 0.2, 0.3, 0.4};
//    vector<double> yList = {0.62049958, -0.28398668, 0.00660095, 0.24842440};

//    // p139 1d
//    vector<double> xList = {0.1, 0.2, 0.3, 0.4};
//    vector<double> yList = {-0.62049958, 0.28398668, 0.00660095, 0.24842440};
//    vector<double> deList = {3.58502082, 3.14033271, 2.66668043, 2.16529366};
//
//    Poly p0 = Interpolation::lagrange(xList,yList);
//    Poly p1 = Interpolation::neville(xList, yList);
//    Poly p2 = Interpolation::newton(xList, yList);
//    Poly p3 = Interpolation::hermite(xList, yList, deList);
//
//    p0.print();
//    p1.print();
//    p2.print();
//    p3.print();

//    cout << p0.getValue(6) << endl;
//    cout << p0.getValue(2.5) << endl;
//    cout << p3.getValue(6) << endl;
//    cout << p3.getValue(2.5) << endl;
//    cout << f(6) << endl;
//    cout << f(2.5) << endl;

//    cout << p0.getValue(0.25) << endl;
//    cout << p3.getValue(0.25) << endl;




}
