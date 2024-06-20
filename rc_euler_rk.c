#include <stdio.h>
#include "rc_input_data.h"
#include "rc_input_data.c"

void gnu_plt();

int main(){

    double t[NUM_STEPS];
    double u[NUM_STEPS];

    t[0] = 0.0; 
    u[0] = 0.0; 

    rk4(t, u); 

    euler(t,u);
    gnu_plt();

    return 0; 
}


void gnu_plt(){
    
    // ============= GNU PLOT  ============== // 

    FILE  *gnuplotPipe = NULL; 

    gnuplotPipe = popen("gnuplot -persist","w");

    if(gnuplotPipe == NULL){
        printf("Error opening GNU PLOT");
        return;
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'rc_rk4_plot_x.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Behaviour of voltage across the capacitor '\n");
    fprintf(gnuplotPipe, "set xlabel 't[s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C[V]'\n");
    fprintf(gnuplotPipe, "set label 'RK3 method' at 3, 3\n");


    // fprintf(gnuplotPipe, "plot 'runge_kutta_4_data_x.txt' using 1:2 with lines linewidth 4 linecolor rgb 'red'\n");
    fprintf(gnuplotPipe, "plot 'euler_data_x.txt' using 1:2 with lines linewidth 2 linecolor rgb 'blue'\n");

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);
}