#include <stdio.h>
#include "rc_input_data.h"


int main() {
    double u[NUM_STEPS]; // Array to store voltage values
    double t[NUM_STEPS]; // Array to store time values

    u[0] = 0.0; // Initialize capacitor voltage
    t[0] = 0.0; // Initialize time


    FILE *fp = NULL; 
    fp = fopen("rc_euler_output_data.txt", "w");

    if(fp == NULL){
        printf("Error opening the file");
        return 1;
    }

    // Iterate for a number of steps
    for (int i = 0; i < NUM_STEPS; i++) {
        printf("Time: %.2f, Voltage: %.4f\n", t[i], u[i]);
        fprintf(fp, "%lf \t %lf\n", t[i], u[i]);

        double u_next = u[i] + DT * derivative(u[i]);       // Calculate the next voltage value using the explicit Euler method

        t[i+1] = t[i] + DT;                                 // Update time and voltage for the next step
        u[i+1] = u_next;
        
    }

    fclose(fp);
    // ================= GNU PLOT =========================== // 

    FILE *gnuplotPipe = NULL; 
    gnuplotPipe = popen("gnuplot -persist", "w");

    if (gnuplotPipe == NULL){
        printf("Error opening Gnuplot");
        return 1;
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'rc_euler_plot.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Behaviour of voltage across the capacitor '\n");
    fprintf(gnuplotPipe, "set xlabel 't [s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C [V]'\n");
    fprintf(gnuplotPipe, "set label 'Euler method' at 3, 3\n");

    fprintf(gnuplotPipe, "plot 'rc_euler_output_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'blue'\n");

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);

    return 0;
}