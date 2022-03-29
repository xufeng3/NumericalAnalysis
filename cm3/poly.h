#ifndef CM3_POLY_H
#define CM3_POLY_H

#include <vector>
#include <cmath>
using std::vector, std::cin, std::cout, std::endl, std::pow;

class DivByZeroException : public std::exception{
public:
    [[nodiscard]] const char * what () const noexcept override {
        return "DivByZero";
    }
};

class Poly {
public:
    Poly(){
        this->deg = 0;
        this->coefs = vector<double>{1.};
    }
    Poly(double m){
        this->deg = 0;
        this->coefs = vector<double>{m};
    }
    Poly(vector<double> coefs){
        this->deg = coefs.size()-1;
        this->coefs = coefs;
    }
    int getDeg() const{
        return this->coefs.size()-1;
    }
    double getCoef(int i) const{
        return this->coefs[i];
    }
    vector<double> getCoefs() const{
        return this->coefs;
    }
    void print() const{
        cout << "(" << this->coefs[0] << ")";
        for(int i=1; i<this->coefs.size(); i++){
            cout << "+(" << this->coefs[i] << ")x^" << i;
        }
        cout << endl;
    }
    double getValue(double x){
        double res = 0.;
        for(int i=0; i<=getDeg(); i++){
            res += getCoef(i) * std::pow(x, i);
        }
        return res;
    }
private:
    int deg = -1;
    vector<double> coefs;
};


Poly operator+(Poly const& p0, Poly const& p1){
    vector<double> res;
    double tmp;
    int deg;
    for(int i=0; i<std::max(p0.getDeg(), p1.getDeg())+1; i++) {
        tmp = 0.;
        if (i <= p0.getDeg()) tmp += p0.getCoef(i);
        if (i <= p1.getDeg()) tmp += p1.getCoef(i);
        res.push_back(tmp);
        if (std::abs(tmp)>=1e-10) {deg = i;}
    }
    for(int i=deg+1; i<std::max(p0.getDeg(), p1.getDeg())+1; i++) {
        res.pop_back();
    }
    return {res};
}

Poly operator*(Poly const& p0, Poly const& p1){
    vector<double> res;
    double tmp = 0.;
    int deg;
    for(int i=0; i<=p0.getDeg()+p1.getDeg(); i++){
        tmp = 0.;
        for(int j=0; j<=i; j++){
            if (j<=p0.getDeg() && i-j<=p1.getDeg()) {
                tmp += p0.getCoef(j) * p1.getCoef(i - j);
            }
        }
        if (std::abs(tmp)>=1e-10) {deg = i;}
        res.push_back(tmp);
    }
    for(int i=deg+1; i<std::max(p0.getDeg(), p1.getDeg())+1; i++) {
        res.pop_back();
    }
    return {res};
}

Poly operator*(Poly const& p0, double m) {
    vector<double> res;
    for(int i=0; i<=p0.getDeg(); i++){
        res.push_back(p0.getCoef(i)*m);
    }
    return {res};
}


Poly operator/(Poly const& p0, double m){
    if (std::abs(m)<1e-20) throw DivByZeroException();
    vector<double> res;
    for(int i=0; i<=p0.getDeg(); i++){
        res.push_back(p0.getCoef(i)/m);
    }
    return {res};
}


Poly operator-(Poly& p0, double m){
    vector<double> res = p0.getCoefs();
    res[0] -= m;
    return {res};
}


Poly operator+(Poly& p0, double m){
    vector<double> res = p0.getCoefs();
    res[0] += m;
    return {res};
}

#endif //CM3_POLY_H