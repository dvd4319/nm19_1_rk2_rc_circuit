#include <stdio.h>
#include "rc_input_data.h"


double derivative(double u) {
    double tau = R*C; 
    return (E - u) / tau; // differential equation of the RC circuit
}

// Runge-Kutta method of second order for solving the differential equation
void runge_kutta_2(double t[], double u[]){

    FILE *fp = NULL; 
    fp = fopen("runge_kutta_2_data.txt", "w");
    if (fp == NULL){
        printf("Error opening the file");
        return; 
    }

    double u_next; 
    double k1, k2; 

    for (int i = 0; i < NUM_STEPS; i++){

        printf("t[%d] = %lf, u[%d] = %lf \n", i, t[i], i, u[i]);
        fprintf(fp, "%lf \t %lf \n", t[i], u[i]); 

        k1 = DT*derivative(u[i]);
        k2 = DT*derivative(u[i]+k1); // in derivative function  there are no h in this particular

        u_next = u[i] + 0.5*(k1+k2);
        t[i+1] = t[i]+ DT;
        u[i+1] = u_next;   
    }

    fclose(fp);
}

void gnu_plot(){
    // ======== GNU PLOT ======================== // 

    FILE  *gnuplotPipe = NULL; 
    gnuplotPipe = popen("gnuplot -persist", "w");

    if(gnuplotPipe == NULL){
        printf("Error opening GNUPLOT");
        return; 
    }



    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'rc_rk2_plot_x.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Behaviour of voltage across the capacitor '\n");
    fprintf(gnuplotPipe, "set xlabel 't [s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C [V]'\n");
    fprintf(gnuplotPipe, "set label 'RK2 method' at 3, 3\n");

    fprintf(gnuplotPipe, "plot 'runge_kutta_2_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'green'\n"); 

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);
}