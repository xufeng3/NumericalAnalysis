#include <iostream>
#include <functional>
#include "ComputationMethod.h"
#include <cmath>
#include <ctime>
#include <fstream>
using std::cin, std::cout, std::endl, std::function, std::sqrt;
namespace cm = computationMethod;

template<typename F>
double recordTime(F f, int repeat = 1){
    std::clock_t t;
    t = std::clock();
    for (int repeat_ = 0; repeat_ < repeat; repeat_++){
        auto&& res = f();
//        cm::Result res = f();
//        cout << res.getIterNum();
    }
    t = std::clock() - t;
//    cout<<"Time: "<<(double)(t)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<(double)(t)/CLOCKS_PER_SEC<<", ";
    return (double)(t)/CLOCKS_PER_SEC;
}

int main(){

    // define functions
    function<double(double)> f = cm::Function::f;
    function<double(double)> f1 = cm::Function::f1;
    function<double(double)> f2 = cm::Function::f2;
    function<double(double)> f3 = cm::Function::f3;
    function<double(double)> g = cm::Function::g;

//    function<double(double)> f4 = cm::Function::f4;
//    function<double(double)> f5 = cm::Function::f5;
//    double a1=1., a2 = 1.5 - 1e-20;
//    cm::RootFinding::bisection(a1, a2, f4);
//    cm::RootFinding::newton(a2, f4, f5);

//    // single time
//    cm::RootFinding::bisection(3., 5., f2);
//    cm::RootFinding::fixedPoint(3., g);
//    cm::RootFinding::newton(15., f2, f3);
//    cm::RootFinding::secant(3., 5., f2);
//    cm::RootFinding::falsePosition(3., 5., f2);
//    cm::RootFinding::steffensen();
//    cm::RootFinding::horner();
//    cm::RootFinding::muller(3., 5., 4., f2);


    // repeat and record time
    int repeat = 10000;
    recordTime([f2]{return cm::RootFinding::bisection(2., 5., f2);}, repeat);
    recordTime([g] {return cm::RootFinding::fixedPoint(3., g);}, repeat);
    recordTime([f2, f3]{return cm::RootFinding::newton(10, f2, f3);}, repeat);
    recordTime([f2]{return cm::RootFinding::secant(3, 5., f2);}, repeat);
    recordTime([f2]{return cm::RootFinding::falsePosition(3., 5., f2);}, repeat);
    recordTime([]{return cm::RootFinding::horner();}, repeat);
    recordTime([g] {return cm::RootFinding::steffensen(2.5, g);}, repeat);


//    // initial values
//    vector<double> timeRecord;
//    vector<int> iterRecord;
//
//    for (double a=2; a<3; a+=0.1){
////        cout << "a=" << a << endl;
//        for (double b=4e5; b>5; b/=10){
//            recordTime([a, b, f2]{return cm::RootFinding::bisection(a, b, f2);}, 10000);
//        }
//    }
//
//    for (double a = 1.; a< 10; a+=1.){
//        cout << "a=" << a << endl;
//        recordTime([a, f2, f3]{return cm::RootFinding::newton(std::pow(4., a), f2, f3);}, repeat);
//    }



//    // test input and output
//    std::ifstream inFile("../inFileTest", std::ios::in);
//    int ina;
//    while(inFile >> ina){
//        cout << ina << endl;
//    }
//    inFile.close();
//
//    std::ofstream outFile("../outFileTest", std::ios::out);
//    outFile << "a" << endl;
//    outFile.close();

    return 0;
}