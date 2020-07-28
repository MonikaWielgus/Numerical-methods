//Monika Wielgus
#include <iostream>
#include <cmath>
#include <stdio.h>


void printVector(const double* x, unsigned N){
    for(unsigned i=0;i<N;++i)
        printf("%17.17f ",x[i]);
    printf("\n");
}
typedef void (*FuncPointer)(const double* x, double* y, double* Df);

int findCurve(FuncPointer f, double* x, unsigned k, double h){
    double y[2];
    double Df[6];

    for(int i=1; i<=k; i++){
        x[2]+=h;

        for(int j=0; j<64; j++){
            //Newton
            f(x,y,Df);

            if(std::abs(y[0])<1e-14&&std::abs(y[1])<1e-14)
                break;

            double det=(Df[0] * Df[4]) - (Df[1] * Df[3]);
            if(std::abs(det)<1e-14)
                 return i;

            double Df2[4];

            Df2[0]=Df[4];
            Df2[1]=-Df[3];
            Df2[2]=-Df[1];
            Df2[3]=Df[0];
            std::swap(Df2[1], Df2[2]);

            Df2[0]/=det;
            Df2[1]/=det;
            Df2[2]/=det;
            Df2[3]/=det;

            x[0]=x[0]-(Df2[0]*y[0]+Df2[1]*y[1]);
            x[1]=x[1]-(Df2[2]*y[0]+Df2[3]*y[1]);
        }
        f(x, y, Df);
        if(std::abs(y[0])>1e-14||std::abs(y[1])>1e-14){
            return i;
        }

        printVector(x,3);
    }
    return 0;
}
int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2){
    double y[1];
    double Df[3];
    double temp=x[2];

    for(int i=1; i<=k1; i++){
        x[1]+=h1;
        x[2]=temp;

        for(int j=1; j<=k2; j++){
            x[2]+=h2;

            for(int k=0; k<64; k++){
                f(x,y,Df);

                if(std::abs(y[0])<1e-14)
                    break;

                if(Df[0]<1e-14)
                    return i;

                x[0]=x[0]-(y[0]/Df[0]);
            }
            f(x,y,Df);

            if(std::abs(y[0])>1e-14){;
                return i*k1+j;
            }
            printVector(x,3);
        }
        std::cout << std::endl;
    }
    return 0;
}
int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2){
    double y[2];
    double Df[8];
    double temp=x[3];

    for(int i=1; i<=k1; i++){
        x[2]+=h1;
        x[3]=temp;

        for(int j=1; j<=k2; j++){
            x[3]+=h2;

            for(int k=0; k<64; k++){
                f(x,y,Df);

                if(std::abs(y[0]-x[0])<1e-14&&std::abs(y[1]-x[1])<1e-14)
                    break;

                y[0]-=x[0]; //this means that we can use Newton
                y[1]-=x[1];
                Df[0]-=1;
                Df[5]-=1;
                double det=(Df[0]*Df[5])-(Df[1]*Df[4]);
                if(std::abs(det)<1e-14)
                    return i;

                double Df2[4];

                Df2[0]=Df[5];
                Df2[1]=-Df[4];
                Df2[2]=-Df[1];
                Df2[3]=Df[0];

                std::swap(Df2[1], Df2[2]);

                Df2[0]/=det;
                Df2[1]/=det;
                Df2[2]/=det;
                Df2[3]/=det;

                x[0]=x[0]-(Df2[0]*y[0]+Df2[1]*y[1]);
                x[1]=x[1]-(Df2[2]*y[0]+Df2[3]*y[1]);

            }
            f(x,y,Df);
            if(std::abs(y[0]-x[0])>1e-14&&std::abs(y[1]-x[1])){;
                return i*k1+j;
            }
            printVector(x,4);
        }
        std::cout << std::endl;
    }
    return 0;
}
