#include <iostream>
#include <ctime>
#include <functional>//bind
using namespace std;
template<typename F>
void calTime(F f) {//作为模板类型传入
    clock_t t;
    t = clock();
    auto&& res = f();//调用函数
    t = clock() - t;
    printf("result=%ld,time=% lf s\n", res, ((float)t) / CLOCKS_PER_SEC);//统一输出
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
    calTime([] { return calculatePlanA(99999999); });//调用函数calculatePlanA，传入参数99999999
    calTime([] { return calculatePlanB(99999999); });//调用函数calculatePlanB，传入参数99999999
    return 0;
}

