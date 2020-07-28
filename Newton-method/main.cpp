//Monika Wielgus
#include <iostream>
#include "source.cpp"

void implicitCurve(const double* x, double* y, double* Df){
    //f(a,b,c)=(1-a^2-b^2-c^2,(a+b+c)/(a^2+b^2+c^2)-1)

    const double n=x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
    const double s=x[0]+x[1]+x[2];

    y[0]=1.-n;
    y[1]=s/n-1.;

    Df[0]=-2.*x[0];
    Df[1]=-2.*x[1];
    Df[2]=-2.*x[2];

    const double r=1./n;
    const double r2=2.*y[1]*r;
    Df[3]=r-x[0]*r2;
    Df[4]=r-x[1]*r2;
    Df[5]=r-x[2]*r2;
}
void implicitSurface(const double* x, double* y, double* Df){
    //f(a,b,c)=(a+b+c)/(a^2+b^2+c^2)-1

    const double n=x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
    const double s=x[0]+x[1]+x[2];

    *y=s/n-1.;

    const double r=1./n;
    const double r2=2.*(*y)*r;
    Df[0]=r-x[0]*r2;
    Df[1]=r-x[1]*r2;
    Df[2]=r-x[2]*r2;
}
void henon(const double* x, double* y, double* Df){
    //henon(x,y,a,b)=(1+y-a*x^2,b*x)
    const double x2=x[0]*x[0];

    y[0]=1+x[1]-x[2]*x2;
    y[1]=x[3]*x[0];

    Df[0]=-2*x[2]*x[0];
    Df[1]=1.;
    Df[2]=-x2;
    Df[3]=0.;

    Df[4]=x[3];
    Df[5]=0.;
    Df[6]=0.;
    Df[7]=x[0];
}

int main(){
    double x[3]={0.25*(1.+sqrt(5.)),0.25*(1.-sqrt(5.)),0.5};
    findCurve(implicitCurve,x,10,1./128);
    printf("\n");
    double x2[3]={0.25*(1.-sqrt(5.)),0.25*(1.+sqrt(5.)),0.5};
    int i=findCurve(implicitCurve,x2,10,3./32);
    printf("%d",i);

    double y[3]={0.25*(1.+sqrt(5.)),0.25*(1.-sqrt(5.)),0.5};
    findSurface(implicitSurface,y,4,4,1./32,1./32);

    double z[4]={-1.2807764064044151, -0.6403882032022076, 1.0000000000000000, 0.50000000000000000};
    findFixedPoints(henon,z,4,4,1./16,1./16);

}
