#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double killInit, victInit, a1, a2, b1, b2, timeLim;
    int N;
    cin >> victInit >> killInit >> a1 >> b1 >> a2 >> b2 >> timeLim;
    cin >> N;

    vector<double> time(N+1);
    vector<double> victims(N+1);
    vector<double> killers(N+1);

    double tempCos, tempSin;
    double deltaT = timeLim / N;

    time[0] = 0;
    victims[0] = victInit;
    killers[0] = killInit;

    for (int i = 1; i <= N; i++) {
        time[i] = time[i-1] + deltaT;
        tempCos = cos(sqrt(a1 * a2) * time[i]);
        tempSin = sin(sqrt(a1 * a2) * time[i]);
        victims[i] = (victInit - a2/b2) * tempCos - (killInit - a1/b1) * sqrt(a2/a1) * b1/b2 * tempSin + (a2/b2);
        killers[i] = (victInit - a2/b2) * tempSin * sqrt(a1/a2) * b2/b1 + (killInit - a1/b1) * tempCos + (a1/b1);
        /*victims[i] = (victInit - a2/b2) * cos(sqrt(a1 * a2) * time[i]) - (killInit - a1/b2) *
                                                                         sqrt(a2/a1) * b2/b2 * sin(sqrt(a1 * a2) * time[i]) + (a2/b2);
        killers[i] = (victInit - a2/b2) * sqrt(a1/a2) * b2/b2 * sin(sqrt(a1 * a2) * time[i])
               + (killInit - a1/b2) * cos(sqrt(a1 * a2) * time[i]) + (a1/b2);*/
    }
    cout << fixed << setprecision(2);
    cout << "t:" << endl;
    for (int  i = 0; i <= N; i++){
        if (i == N){
            cout <<time[i] << endl;
        } else{
            cout << time[i] << " ";
        }
    }
    cout << "v:" << endl;
    for (int  i = 0; i <= N; i++){

        if (i == N){
            cout << victims[i] << endl;
        } else{
            cout << victims[i] << " ";
        }
    }
    cout << "k:" << endl;
    for (int  i = 0; i <= N; i++){
        if (i == N){
            cout <<  killers[i] << endl;
        } else{
            cout << killers[i] << " ";
        }
    }
    return 0;
}
