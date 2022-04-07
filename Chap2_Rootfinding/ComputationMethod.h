#include <iostream>
#include <functional>
#include <cmath>
#include <exception>
#include <utility>
#include <vector>

using std::cin, std::cout, std::endl,
std::function, std::abs, std::exception, std::vector, std::sqrt;

namespace computationMethod{

    class Result {
    public:
        int getIterNum() const{
            return this->iterNum;
        }
        Result(double p, vector<double> pVector, int iterNum, std::string methodName, int state=1){
            this->state = state;
            this->equationSolution = p;
            this->pVector = std::move(pVector);
            this->iterNum = iterNum;
            this->methodName = std::move(methodName);
            printResult();
        }
        Result(int state=0){
            this->state = state;
            this->equationSolution = 0.;
            printResult();
        }
        void printResult(){
            switch (this->state) {
                case 1:
//                    cout << "Method: " << this->methodName << endl;
//                    cout << "Success! Answer: " << this->equationSolution << "." <<  endl;
//                    cout << "The number of iterations is " << this->iterNum << "." << endl;
//                    for (double i : pVector) { cout << i << " "; }
//                    cout << endl << endl;
                    break;
                case 0:
                    cout << "Fail!" << endl << endl;
                    break;
                default :
                    cout << "Error!" << endl << endl;
                    break;
            }
        }

    private:
        double equationSolution;
        int state = -1, iterNum = -1; // -1 denotes unreachable
        std::string methodName = "NULL";
        vector<double> pVector;
    };

    class IterException : public exception{
    public:
        [[nodiscard]] const char * what () const noexcept override {
            return "Fail! Exceed the number of iterations.";
        }
    };

    class ComplexException : public exception{
    public:
        [[nodiscard]] const char * what () const noexcept override {
            return "Fail! May require complex arithmetic.";
        }
    };

    class ConditionException : public exception{
    public:
        [[nodiscard]] const char * what () const noexcept override {
            return "Fail! not meet the requirements.";
        }
    };


    class Function {
    public:
        static double f(double x) { return x*x-2; }
        static double f1(double x) { return x*2; }

        static double f2(double x) { return std::log(x)*2 - x + 1; }
        static double f3(double x) { return 2/x - 1; }

        static double g(double x) { return 2* std::log(x) + 1;}

        static double f4(double x) { return std::tan(std::exp(x))-1;}
        static double f5(double x) { return std::exp(x)/std::pow(std::cos(std::exp(x)), 2);}
    };


    class RootFinding {
    private:
        const double TOL = 1e-10, eps = 1e-10;
        const int N = 1000;


    public:
        static Result bisection(double a=1., double b=2.,
                                const function<double(double)>& f = Function::f){
            try{
                int i=0;
                vector<double> pVector;
                double fa = f(a), fp, p;

                // check condition
                double fb = f(b);
                if (fb * fa > 0 ) throw ConditionException();

                while(i<RootFinding().N){
                    p = (a+b)/2;
                    fp = f(p);
                    pVector.push_back(p);
                    if ((abs(fp)<RootFinding().eps) | (b-a < RootFinding().TOL))
                        return {p, pVector, i, "bisection"};
                    i++;
                    if (fa * fp > RootFinding().eps) a = p;
                    else b = p;
                }
                throw IterException();
            }
            catch (IterException& iterException){
                cout << iterException.what();
                return {0};
            }
            catch (ConditionException& conditionException){
                cout << conditionException.what();
                return {0};
            }
        }

        static Result fixedPoint(double p0=3., function<double(double)> f = Function::f){
            try{
                vector<double> pVector;
                int i=0;
                double p;
                while(i<RootFinding().N){
                    p = f(p0);
                    pVector.push_back(p);
                    if (abs(p-p0)<RootFinding().TOL){
                        return {p, pVector, i, "fixedPoint", 1};
                    }
                    i++; p0 = p;
                }
                throw IterException();
            }
            catch(IterException& iterException){
                cout << iterException.what() << endl;
            }
            return {0};
        }

        static Result newton(double p0=1.5, const function<double(double)>& f = Function::f,
                            const function<double(double)>& f1 = Function::f1) {
            try{
                int i=0;
                double p;
                vector<double> pVector;
                while(i<RootFinding().N){
                    p = p0 - f(p0)/f1(p0);
                    pVector.push_back(p0);
                    if (abs(p-p0)<RootFinding().TOL) return {p0, pVector, i, "newton"};
                    i++, p0=p;
                }
                throw IterException();
            }
            catch (IterException& iterException){
                cout << iterException.what();
            }
            return {0};
        }

        static Result secant(double p0=1, double p1=2, function<double(double)> f = Function::f){
            try{
                int i = 0;
                double p;
                double q0 = f(p0), q1 = f(p1);
                vector<double> pVector;
                while(i<RootFinding().N){
                    p = p1 - q1*(p1-p0)/(q1-q0);
                    pVector.push_back(p);
                    if (abs(p-p1)<RootFinding().TOL) return {p, pVector, i, "secant"};
                    i++, p0=p1, q0=q1, p1=p, q1=f(p);
                }
                throw IterException();
            }
            catch (IterException& iterException){
                cout << iterException.what() << endl;
            }
            return {0};
        }

        static Result falsePosition(double p0=1., double p1=2.,
                                    function<double(double)> f = Function::f){
            try{
                int i = 0;
                double p;
                vector<double> pVector;
                double q0 = f(p0), q1 = f(p1), q;
                while(i<RootFinding().N){
                    p = p1 - q1*(p1-p0)/(q1-q0);
                    pVector.push_back(p);
                    if (abs(p-p1)<RootFinding().TOL) return {p, pVector, i, "falsePosition"};
                    i++, q=f(p);
                    if (q*q1<0) {
                        p0 = p1;
                        q0 = q1;
                    }
                    p1 = p;
                    q1 = q;
                }
                throw IterException();
            }
            catch (IterException& iterException){
                cout << iterException.what() << endl;
            }
            return {0};
        }

        static Result steffensen(double p0=4., function<double(double)> f = Function::f){
            try{
                int i = 0;
                double p, p1, p2;
                vector<double> pVector;
                while(i<RootFinding().N){
                    p1 = f(p0);
                    p2 = f(p1);
                    pVector.push_back(p);
                    p = p0 - (p1-p0)*(p1-p0)/(p2-2*p1+p0);
                    if (abs(p-p0)<RootFinding().TOL) return {p, pVector, i, "steffensen"};
                    i++; p0=p;
                }
                throw IterException();
            }
            catch (IterException& iterException){
                cout << iterException.what() << endl;
            }
            return {0};
        }

        // cal the specified values of polynomials
        static Result horner(int n = 3, vector<double> coe = {2., 1., 3., 7.},
                             double x0 = 2.) {
            try{
                double y = coe[n], z=coe[n];
                for(int j = n-1; j>0; j--){
                    y = x0 * y + coe[j];
                    z = x0 * z + y;
                }
                y = x0 * y + coe[0];
//                cout << y << " " << z << endl;
                return {1};
            }
            catch (IterException& iterException){
                cout << iterException.what() << endl;
            }
            return {0};
        }

        static Result muller(double p0=2.5, double p1=1., double p2=2.,
                             function<double(double)> f = Function::f){
            try{
                double h1 = p1 - p0, h2 = p2 - p1;
                int i = 0;
                double delta1 = (f(p1) - f(p0))/h1;
                double delta2 = (f(p2) - f(p1))/h2;
                double d = (delta2 - delta1)/(h2+h1);
                double b, D, E, h, p, tmp;
                vector<double> pVector;
                while(i<RootFinding().N){
                    b = delta2 + h2 * d;
                    tmp = b*b-4*f(p2)*d;
                    if (tmp < 0) throw ComplexException();
                    D = sqrt(tmp);
                    // todo: complex exception
                    E = (abs(b-D) < abs(b+D))? b+D : b-D;
                    h = -2 * f(p2) / E;
                    p = p2 + h;
                    pVector.push_back(p);
                    if (abs(h) < RootFinding().TOL) return Result{p, pVector, i, "muller"};
                    p0 = p1; p1 = p2; p2 = p; h1 = p1 - p0; h2 = p2 - p1;
                    delta1 = (f(p1) - f(p0))/h1;
                    delta2 = (f(p2) - f(p1))/h2;
                    d = (delta2 - delta1)/(h2+h1);
                    i++;
                }
            }
            catch (IterException& iterException){
                cout << iterException.what() << endl;
            }
            catch (ComplexException& complexException){
                cout << complexException.what() << endl;
            }
            return {0};
        }

    };
}
