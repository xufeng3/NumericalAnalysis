#include <iostream>
#include <vector>
#include "test3.h"
using std::vector, std::cout, std::cin;
#include "interpolation.h"

int main() {
    vector<double> xList = {1., 2., 3., 4.};
    vector<double> yList = {1., 4., 9., 16.};
    vector<double> deList = {2., 4., 6., 8.};

    // p119 3c
    vector<double> xList2 = {0.1, 0.2, 0.3, 0.4};
    vector<double> yList2 = {0.62049958, -0.28398668, 0.00660095, 0.24842440};

    // p139 1d
    vector<double> xList3 = {0.1, 0.2, 0.3, 0.4};
    vector<double> yList3 = {-0.62049958, 0.28398668, 0.00660095, 0.24842440};
    vector<double> deList3 = {3.58502082, 3.14033271, 2.66668043, 2.16529366};


    Poly p0 = Interpolation::lagrange(xList2, yList2);
    Poly p1 = Interpolation::neville(xList2, yList2);
    Poly p2 = Interpolation::newton(xList2, yList2);
    Poly p3 = Interpolation::hermite(xList3, yList3, deList3);

    p0.print();
    p1.print();
    p2.print();
    p3.print();

    cout << p0.getValue(0.3) << endl;
    cout << p1.getValue(0.3) << endl;
    cout << p2.getValue(0.4) << endl;
    cout << p3.getValue(0.4) << endl;

}
