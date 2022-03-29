#include <iostream>
#include <ctime>
#include <functional>//bind
using namespace std;
template<typename F>
void calTime(F f) {
    clock_t t;
    t = clock();
    auto&& res = f();
    t = clock() - t;
    printf("result=%ld,time=% lf s\n", res, ((float)t) / CLOCKS_PER_SEC);//Í³Ò»Êä³ö
}

int calculatePlanA(int b){
    cout << "a";
    return 0;
}

int calculatePlanB(int b){
    cout << "b";
    return 1;
}
int main() {
    calTime([] { return calculatePlanA(99999999); });
    calTime([] { return calculatePlanB(99999999); });
    return 0;
}

