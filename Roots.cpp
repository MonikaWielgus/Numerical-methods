//Monika Wielgus
#include <iostream>
#include <cmath>
using namespace std;

int sgn(double x){
    if(x>0)
        return 1;
    else
        return -1;
}

double findRoot( //bisection method with Euler's method
        double (*f)(double),  // function
        double a,             // beginning of interval
        double b,             // end of interval
        int M,                // maximum number of function repetition
        double eps,           // zero accuracy expected
        double delta          // sufficient absolute error of the result
){
    double fa=f(a);
    double fb=f(b);
    double fc=0;
    double c=0;
    int count=M-2;

    if(abs(fa)<=eps)
        return a;
    if(abs(fb)<=eps)
        return b;

    while(sgn(fa)==sgn(fb)){
        c=b-((fb*(b-a))/(fb-fa));
        fc=f(c);
        count--;
        if(abs(c-a)<=delta||abs(c-b)<=delta||abs(fc)<=eps)
            return c;
        a=b;
        fa=fb;
        b=c;
        fb=fc;
    }

    double e=b-a;
    for(int k=1; k<=M-2; k++) {
        e=e/2;
        c=a+e;
        fc=f(c);
        count--;
        if(abs(e)<=delta||abs(fc)<=eps){
            return c;
        }
        if(abs(e)<0.05){
            break;
        }
        if(sgn(fc)!=sgn(fa)){
            b=c;
            fb=fc;
        }
        else{
            a=c;
            fa=fc;
        }
    }
    while(count>0){
        c=b-((fb*(b-a))/(fb-fa));
        fc=f(c);
        count--;
        if(abs(c-a)<=delta||abs(c-b)<=delta||abs(fc)<=eps)
            return c;
        a=b;
        fa=fb;
        b=c;
        fb=fc;
    }
    return c;
}

double polynomial(double x){
    return (((x-6)*x+11)*x)-6;
}
double polynomialSinExp(double x){
    return ((((x-6)*x+11)*x)-4 + sin(15*x))*exp(-x*x);
}
double square(double x){
    return (x*x-2);
}
double square100(double x){
    return 1e100*(x*x-2);
}
double square_10(double x){
    return 1e-10*(x*x-2);
}

int main(){
	cout.precision(17);
	cout << findRoot(polynomial, 0, 4, 20, 1e-15, 1e-14) << endl;
	cout << findRoot(polynomial, 0, 40, 20, 1e-15, 1e-14) << endl;
	cout << findRoot(polynomial, 1, 2, 2, 1e-15, 1e-14) << endl;
	cout << findRoot(polynomial, -150, 1.9, 20, 1e-15, 1e-14) << endl;
	cout << findRoot(polynomial, 1.5, 2.99, 20, 1e-15, 1e-14) << endl;
	cout << findRoot(polynomial, 2.01, 40, 20, 1e-15, 1e-14) << endl;
	cout << findRoot(polynomial, 1.5, 6, 20, 1e-15, 1e-14) << endl;

	cout << findRoot(polynomialSinExp, -1, 3, 60, 1e-60, 1e-14) << endl;
	cout << findRoot(polynomialSinExp, -3, 3, 60, 1e-160, 1e-14) << endl;

	cout << findRoot(square, 0, 4, 15, 1e-11, 1e-14) << endl;
	cout << findRoot(square100, 0, 4, 15, 1e-11, 1e-14) << endl;
	cout << findRoot(square_10, 0, 4, 10, 1e-10, 1e-14) << endl;
 	cout << findRoot(square_10, 0, 4, 15, 1e-160, 1e-14) << endl;
 	return 0;
}
