//Monika Wielgus
#include "vectalg.h"

Vector solveEquations(const Matrix & A, const Vector & b, double  eps){

    int n=b.size();
    Vector scale(n);
    Vector b2(n);
    b2=b;
    Matrix A2(n);
    A2=A;

    for(int i=0; i<n; i++){
        scale[i]=std::abs(A2(i,0));
        for(int j=0; j<n; j++){
            if(std::abs(A2(i,j))>scale[i])
                scale[i]=std::abs(A2(i,j));
        }
    }
    for(int c=0; c<n; c++){ //columns
            int maxElement=c; //index of the biggest element
        for(int r=c; r<n; r++){ //rows
            if(std::abs(A2(r,c)/scale[r])>std::abs(A2(maxElement,c)/scale[maxElement]))
                maxElement=r;
        }
        if(maxElement!=c){
            for(int i=0; i<n; i++){
                double temp=A2(c,i);
                A2(c,i)=A2(maxElement,i);
                A2(maxElement,i)=temp;
            }
            double temp2=b2[c];
            b2[c]=b2[maxElement];
            b2[maxElement]=temp2;
        }

        //we have correct row on the top

        for(int r=c+1; r<n; r++){ //Gaussian elimination
            double div=A2(r,c)/A2(c,c);
            for(int k=0;k<n;k++){
                A2(r,k)=A2(r,k)-div*A2(c,k);
            }
            b2[r]=b2[r]-div*b2[c];
        }
    }
    Vector x(n);
    for(int i=n-1; i>=0; i--){
        for(int j=i; j<n; j++){
            if(j!=i)
                b2[i]-=A2(i,j)*x[j];
        }
        x[i]=b2[i]/A2(i,i);
    }
    Vector residual=residual_vector(A,b,x);
    while(residual.max_norm()>eps){
        Vector next=solveEquations(A,residual,eps);
        for(int i=0; i<n; i++)
            x[i]=x[i]+next[i];
        residual=residual_vector(A,b,x);
    }
    return x;
}

