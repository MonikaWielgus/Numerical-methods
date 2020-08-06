//Monika Wielgus
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    int N;
    cin>>N;
    int M;
    cin>>M;
    double **matrix;
    matrix=new double*[N];
    for(int i=0;i<N;i++)
        matrix[i]=new double[M];

    int stop=N-M/2;
    for(int i=0; i<=M/2; i++){
        if(stop<=N){
            for(int j=0; j<stop; j++)
                cin>>matrix[j][i];
            for(int j=stop; j<N; j++)
                matrix[j][i]=0;
        }
        stop++;
    }
    stop-=2;
    for(int i=M/2+1; i<M; i++){
        if(stop<=N){
            for(int j=0; j<N-stop; j++)
                matrix[j][i]=0;
            for(int j=N-stop; j<N; j++)
                cin>>matrix[j][i];

        }
        stop--;
    }
    double *y;
    y=new double[N];
    for(int i=0; i<N; i++)
        cin>>y[i];
    double *x0;
    x0=new double[N];
    for(int i=0; i<N; i++)
        cin>>x0[i];
    double w;
    cin>>w;
    int iterations;
    cin>>iterations;

    auto newx0=new double[N];
    for(int i=0; i<N; i++)
        newx0[i]=x0[i];
    for(int iter=0; iter<iterations; iter++){
        for(int i=0; i<N; i++){
            auto s=y[i];
            int n=M/2+i;
            for(int j=0; j<M; j++){
                if(j!=M/2){
                    if (n>=0 && n<N)
                        s-=matrix[i][j]*newx0[n];
                }
                n--;
            }
            newx0[i] = ((1-w)*newx0[i])+w*s/matrix[i][M/2];
        }
    }
    cout << std::setprecision(16) << scientific;
    for(int i=0; i<N; i++){
        cout << newx0[i] << " ";
    }
    return 0;
}
