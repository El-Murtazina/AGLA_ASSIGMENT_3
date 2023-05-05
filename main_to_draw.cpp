#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot -persist"
#endif


int main() {

#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME, "w");
#else
    FILE* pipe = popen(GNUPLOT_NAME, "w");
#endif

    double killInit, victInit, a1, a2, b1, b2, timeLim;
    int N;
    killInit = 15.65;
    victInit = 19.64;
    a1 = 0.65;
    a2 = 0.5;
    b1 = 0.06;
    b2 = 0.02;
    timeLim = 94.34;
    N = 200;


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
    }

    fprintf(pipe, "set yrange [0:50]\n");
    fprintf(pipe, "set xrange [0:%lf]\n", timeLim);

    fprintf(pipe, "set multiplot\n");
    fprintf(pipe, "set xlabel 'Time'\n");
    fprintf(pipe, "set ylabel 'Number of animals'\n");

    fprintf(pipe, "plot '-' lc 'orange' linewidth 2 title 'Victims' with lines\n");

    for (int i = 0; i <= N; i++) {
        fprintf(pipe, "%lf %lf\n", time[i], victims[i]);
    }

    fprintf(pipe, "e\n");
    fprintf(pipe, "set key spacing 2.5\n");

    fprintf(pipe, "plot '-' using 1:2 lc 'green' linewidth 2 title 'Killers' with lines\n");

    for (int i = 0; i <= N; i++) {
        fprintf(pipe, "%lf %lf\n", time[i], killers[i]);
    }

    fprintf(pipe, "e\n");
    fprintf(pipe, "unset multiplot\n");
    fflush(pipe);

    fprintf(pipe, "set term wxt 1\n");

    fprintf(pipe, "set xlabel 'Number of victims'\n");
    fprintf(pipe, "set ylabel 'Number of killers'\n");

    fprintf(pipe, "plot '-' using 1:2 lc 'dark-blue' linewidth 2 title 'k(v)' with lines\n");

    for (int i = 0; i <= N; i++) {
        fprintf(pipe, "%lf %lf\n", victims[i], killers[i]);
    }

    fprintf(pipe, "e\n");

    fflush(pipe);

#ifdef WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
    return 0;
}
