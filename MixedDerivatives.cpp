//Monika Wielgus
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

template <typename T>
T func(const T & x, const T & y){
    T w = sin(x*x - 2*(y+1))/exp(-y*y+cos(x*y));
    return w;
}
class Jet{
public:
    double u;
    double ux;
    double uy;
    double uxx;
    double uxy;
    double uyy;

    Jet(): u(0),ux(0),uy(0),uxx(0),uxy(0),uyy(0){}
    Jet(double uArg, double uxArg, double uyArg, double uxxArg, double uxyArg, double uyyArg):
        u(uArg),ux(uxArg),uy(uyArg),uxx(uxxArg),uxy(uxyArg),uyy(uyyArg){}
    Jet(const Jet& jet):u(jet.u),ux(jet.ux),uy(jet.uy),uxx(jet.uxx),uxy(jet.uxy),uyy(jet.uyy){}

    Jet operator+(const Jet &j)const{
        Jet n;
        n.u=u+j.u;
        n.ux=ux+j.ux;
        n.uy=uy+j.uy;
        n.uxx=uxx+j.uxx;
        n.uxy=uxy+j.uxy;
        n.uyy=uyy+j.uyy;
        return n;
    }
    Jet operator-(const Jet &j)const{
        Jet n;
        n.u=u-j.u;
        n.ux=ux-j.ux;
        n.uy=uy-j.uy;
        n.uxx=uxx-j.uxx;
        n.uxy=uxy-j.uxy;
        n.uyy=uyy-j.uyy;
        return n;
    }
    Jet operator*(const Jet &j)const{
        Jet n;
        n.u=u*j.u;
        n.ux=ux*j.u+u*j.ux;
        n.uy=uy*j.u+u*j.uy;
        n.uxx=uxx*j.u+2*ux*j.ux+u*j.uxx;
        n.uxy=uxy*j.u+uy*j.ux+ux*j.uy+j.uxy*u;
        n.uyy=uyy*j.u+2*uy*j.uy+u*j.uyy;
        return n;
    }
    Jet operator/(const Jet &j)const{
        Jet n;
        n.u=u/j.u;
        n.ux=(ux*j.u-u*j.ux)/(j.u*j.u);
        n.uy=(uy*j.u-u*j.uy)/(j.u*j.u);
        n.uxx=(uxx-2*j.ux*n.ux-n.u*j.uxx)/j.u;
        n.uxy=((uxy*j.u+uy*j.ux-ux*j.uy-u*j.uxy)*j.u*j.u-(uy*j.u-u*j.uy)*2*j.ux*j.u)/(j.u*j.u*j.u*j.u);
        n.uyy=(uyy-2*j.uy*n.uy-n.u*j.uyy)/j.u;
        return n;
    }
    Jet operator+(const double s)const{
        Jet n(u,ux,uy,uxx,uxy,uyy);
        n.u+=s;
        return n;
    }
    Jet operator-(const double s)const{
        Jet n(u,ux,uy,uxx,uxy,uyy);
        n.u-=s;
        return n;
    }
    Jet operator*(const double s)const{
        Jet n(u,ux,uy,uxx,uxy,uyy);
        Jet n2(s,0,0,0,0,0);
        return n*n2;
    }
    Jet operator/(const double s)const{
        Jet n(u,ux,uy,uxx,uxy,uyy);
        Jet n2(s,0,0,0,0,0);
        return n/n2;
    }
    Jet operator-()const{
        Jet n;
        n.u=-u;
        n.ux=-ux;
        n.uy=-uy;
        n.uxx=-uxx;
        n.uxy=-uxy;
        n.uyy=-uyy;
        return n;
    }
    Jet operator=(const Jet& j){
        u=j.u;
        ux=j.ux;
        uy=j.uy;
        uxx=j.uxx;
        uxy=j.uxy;
        uyy=j.uyy;
        return *this;
    }
    friend Jet operator+(const double s, const Jet& j){
        return j+s;
    }
    friend Jet operator-(const double s, const Jet& j){
        Jet n(s,0,0,0,0,0);
        return n-j;
    }
    friend Jet operator/(const double s, const Jet j){
        Jet n(s,0,0,0,0,0);
        return n/j;
    }
    friend Jet operator*(const double s, const Jet& j){
        Jet n(s,0,0,0,0,0);
        return n*j;
    }
};
Jet sin(const Jet &j){
    Jet n;
    n.u=std::sin(j.u);
    n.ux=std::cos(j.u)*j.ux;
    n.uy=std::cos(j.u)*j.uy;
    n.uxx=-std::sin(j.u)*j.ux*j.ux+std::cos(j.u)*j.uxx;
    n.uxy=-std::sin(j.u)*j.ux*j.uy+std::cos(j.u)*j.uxy;
    n.uyy=-std::sin(j.u)*j.uy*j.uy+std::cos(j.u)*j.uyy;
    return n;
}
Jet cos(const Jet &j){
    Jet n;
    n.u=std::cos(j.u);
    n.ux=-std::sin(j.u)*j.ux;
    n.uy=-std::sin(j.u)*j.uy;
    n.uxx=-std::cos(j.u)*j.ux*j.ux-std::sin(j.u)*j.uxx;
    n.uxy=-std::cos(j.u)*j.ux*j.uy-std::sin(j.u)*j.uxy;
    n.uyy=-std::cos(j.u)*j.uy*j.uy-std::sin(j.u)*j.uyy;
    return n;
}
Jet exp(const Jet &j){
    Jet n;
    n.u=std::exp(j.u);
    n.ux=std::exp(j.u)*j.ux;
    n.uy=std::exp(j.u)*j.uy;
    n.uxx=std::exp(j.u)*j.ux*j.ux+std::exp(j.u)*j.uxx;
    n.uxy=std::exp(j.u)*j.ux*j.uy+std::exp(j.u)*j.uxy;
    n.uyy=std::exp(j.u)*j.uy*j.uy+std::exp(j.u)*j.uyy;
    return n;
}

int main() {
    int M;
    cin >> M; //number of points
    for (int i = 0; i < M; i++) {
        double x;
        double y;
        cin >> x >> y;
        cout << endl;
        Jet a(x, 1, 0, 0, 0, 0);
        Jet b(y, 0, 1, 0, 0, 0);
        Jet result = func(a, b);
        cout << setprecision(15);
        cout << result.u << " " << result.ux << " " << result.uy << " " << result.uxx << " " << result.uxy << " " << result.uyy << endl;
    }
}
