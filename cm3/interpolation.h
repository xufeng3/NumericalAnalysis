#ifndef CM3_INTERPOLATION_H
#define CM3_INTERPOLATION_H

#include "poly.h"
#include <vector>
#include <iostream>
using std::vector, std::cout, std::cin, std::endl;


class LengthMatch : std::exception {
public:
    [[nodiscard]] const char * what () const noexcept override {
        return "Length does not match!";
    }
};

class Interpolation {
public:
    static Poly lagrange(vector<double> xList, vector<double> yList){
        try{
            if (xList.size() != yList.size()) throw LengthMatch();
            int n = xList.size()-1;
            Poly p = vector<double> {0.};
            for (int k=0; k<=n; k++){
                Poly lnk = vector<double> {1.};
                for (int i=0; i<=n; i++){
                    if (i != k){
                        Poly x = vector<double> {-xList[i], 1.};
                        Poly tmp =  x / (xList[k] - xList[i]);
                        lnk = lnk * tmp;
                    }
                }
                Poly tmp = lnk * yList[k];
                p = p + tmp;
            }
            return p;
        }
        catch (LengthMatch& lengthMatch){
            cout << lengthMatch.what() << endl;
        }
    }

    static Poly neville(vector<double> xList, vector<double> yList){
        try{
            const int n = xList.size()-1;
            Poly Q[n+1][n+1];
            for(int i=0; i<=n; i++){
                Q[i][0] = Poly(vector<double>{yList[i]});
            }

            for(int i=1; i<=n; i++){
                for(int j=1; j<=i; j++){
                    Q[i][j] = (Poly(vector<double>{-xList[i-j], 1.}) * Q[i][j-1]
                            + Poly(vector<double>{-xList[i], 1.}) * Q[i-1][j-1] * (-1.))
                                    /(xList[i]-xList[i-j]) ;
                }
            }
            return Q[n][n];
        }
        catch (LengthMatch& lengthMatch){
            cout << lengthMatch.what() << endl;
        }
    }

    static Poly newton(vector<double> xList, vector<double> yList){
        try{
            const int n = xList.size()-1;
            double F[n+1][n+1];

            for(int i=0; i<=n; i++){
                F[i][0] = yList[i];
            }

            for(int i=1; i<=n; i++){
                for(int j=1; j<=i; j++){
                    F[i][j] = (F[i][j-1]-F[i-1][j-1])/(xList[i]-xList[i-j]);
                }
            }

            Poly p = Poly(F[0][0]);

            Poly tmp;
            for(int i=1; i<=n; i++){
                tmp = Poly(1.);
                for(int j=0; j<=i-1; j++){
                    tmp = tmp * Poly(vector<double>{-xList[j], 1.});
                }
                tmp = tmp * F[i][i];
                p = p + tmp;
            }
            return p;
        }
        catch (LengthMatch& lengthMatch){
            cout << lengthMatch.what() << endl;
        }
    }

    static Poly hermite(vector<double> xList, vector<double> yList, vector<double> deList){
        try {
            const int n = xList.size()-1;
            double z[2*n+2];
            double Q[2*n+2][2*n+2];

            for (int i = 0; i <= n; i++) {
                z[2*i] = xList[i];
                z[2*i+1] = xList[i];
                Q[2*i][0] = yList[i];
                Q[2*i+1][0] = yList[i];
                Q[2*i+1][1] = deList[i];

                if(i != 0){
                    Q[2*i][1] = (Q[2*i][0]-Q[2*i-1][0])/(z[2*i]-z[2*i-1]);
                }
            }

            for(int i=2; i<=2*n+1; i++){
                for(int j=2; j<=i; j++){
                    Q[i][j] = (Q[i][j-1]-Q[i-1][j-1])/(z[i]-z[i-j]);
                }
            }

            Poly h = Poly(Q[0][0]);
            Poly tmp = Poly(1.);
            for(int i=1; i<=n; i++){
                tmp = tmp * Poly(vector<double>{-xList[i-1], 1.});
                h = h + tmp * Q[2*i-1][2*i-1];
                tmp = tmp * Poly(vector<double>{-xList[i-1], 1.});
                h = h + tmp * Q[2*i][2*i];
            }
            tmp = tmp * Poly(vector<double>{-xList[n], 1.});
            h = h + tmp * Q[2*n+1][2*n+1];
            return h;

        }
        catch (LengthMatch& lengthMatch){
            cout << lengthMatch.what() << endl;
        }
    }

};

#endif //CM3_INTERPOLATION_H
