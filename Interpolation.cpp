//Monika Wielgus
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
int factorial(int n){
    int result=1;
    for(int i=1;i<=n;i++)
        result*=i;
    return result;
}
int main(){
    int M,N;
    cin >> M >> N;
    double X[M];
    double Y[M];
    double T[N];
    for(int i=0; i<M; i++)
        cin >> X[i];
    for(int i=0; i<M; i++)
        cin >> Y[i];
    for(int i=0; i<N; i++)
        cin >> T[i];

    vector<double> result;
    result.push_back(Y[0]);
    double temp[M-1];

    int repeat=0;
    for(int i=0; i<M-1; i++){
        if(X[i]==X[i+1]){
            temp[i]=Y[i+1-repeat];
            repeat++;
        }
        else{
            temp[i]=(Y[i+1]-Y[i-repeat])/(X[i+1]-X[i]);
            repeat=0;
        }
    }
    result.push_back(temp[0]);
    int count=M-2;
    int br=2;

    for(int i=0; i<M-2; i++){
        repeat=0;
        for(int j=0; j<count; j++){
            if(X[j]==X[j+br]){
                temp[j]=Y[j+br-repeat]/factorial(br);
                repeat++;
            }
            else{
                temp[j]=(temp[j+1]-temp[j])/(X[j+br]-X[j]);
                repeat=0;
            }
        }
        result.push_back(temp[0]);
        count--;
        br++;
    }
    cout << std::setprecision(17) << fixed;
    for(int i=0; i<M;i++)
        cout << result[i] << " ";
    cout << endl;
    for(int i=0; i<N; i++){
        double res=result[0];
        double help=1;
        for(int j=1; j<M; j++){
            help*=(T[i]-X[j-1]);
            res+=result[j]*help;
        }
        cout << res << " ";
    }
}