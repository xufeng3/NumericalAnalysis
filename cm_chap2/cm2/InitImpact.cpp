#include <iostream>
#include <functional>
#include "ComputationMethod.h"
#include <cmath>
#include <fstream>
using std::cin, std::cout, std::endl, std::function, std::sqrt;
namespace cm = computationMethod;

int main(){
    function<double(double)> f = cm::Function::f;
    function<double(double)> f1 = cm::Function::f1;
//
//    for (double a=0; a<1.2; a+=0.05){
//        cout << "a=" << a << endl;
//        for (double b=3; b>1.5; b-=0.05){
//            cout << cm::RootFinding::bisection(a, b, f).getIterNum() << " ";
//        }
//        cout << endl;
//    }


//    cm::RootFinding::bisection(1., 2., f);
//    cm::RootFinding::fixedPoint(3., f);

    // newton
    double p0 = 10000.;
    while( p0 > 1.5){
        cout << cm::RootFinding::newton(p0, f, f1).getIterNum() << " ";
        p0 -= 1;
    }


    return 0;
}
