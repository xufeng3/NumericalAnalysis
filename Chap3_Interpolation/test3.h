#ifndef CM3_TEST3_H
#define CM3_TEST3_H

#include <iostream>
#include "poly.h"
#include <vector>
using std::vector, std::cout, std::cin;

class UnitTest {
public:
    static void test(){
        Poly p0 = Poly(vector<double>{1., 2., 4});
        Poly p1 = Poly(vector<double>{3.});
        p0.print();
        p1.print();
        Poly p2 = p0 * p1;
        p2.print();
        p2 = p2/10;
        Poly p3 = p2*10;
//        Poly p3 = p1*(2.);
        p3.print();
    }
};

#endif //CM3_TEST3_H
