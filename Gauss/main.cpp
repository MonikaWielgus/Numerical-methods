//Monika Wielgus
#include <iostream>
#include "source.cpp"
#include "vectalg.h"
using namespace std;

int main(){
    cout.precision(17);
    int n=0;
    double eps=0;

    cin >> n;
    Matrix a(n);
    Vector b(n);
    cin >> a >> b >> eps;

    Vector x=solveEquations(a, b, eps);

    auto residual=residual_vector(a, b, x);
    cout << "solution = " << x << endl;
    cout << "residual = " << residual << endl;
    cout << "error = " << residual.max_norm()
         << " limit = " << eps << endl ;
    cout << "Test " << (residual.max_norm() < eps ? "":"not ") << "passed" << endl;
    return 0;
}
