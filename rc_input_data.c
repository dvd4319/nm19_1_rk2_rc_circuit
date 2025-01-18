#include <stdio.h>
#include "rc_input_data.h"
#include "rc_constants.h"

double derivative(double u) {
    double tau = R*C; 
    return (E - u) / tau; 
}

// ===================== EULER METHOD ================= //
void euler(double t[], double u[]){
    FILE *fp_euler = NULL;
    fp_euler = fopen("d1_euler_output_data.txt","w");
    if(fp_euler == NULL){

        printf("Error opening the file");
        return; 
    }

    for (int i = 0; i < NUM_STEPS; i++){
        printf("t_eu[ %d] = %lf, u_eu[%d] = %lf \n", i, t[i], i, u[i]);
        fprintf(fp_euler, "%lf\t%lf\n", t[i], u[i]);
        u[i+1] = u[i] + DT*derivative(u[i]);
        t[i+1] = t[i] + DT; 
    }
}

void gnu_plot1(){
    // ======== GNU PLOT ======================== // 

    FILE  *gnuplotPipe = NULL; 
    // Șterge fișierul .png existent înainte de a crea unul nou
    remove("d1_euler_plot.png");
    gnuplotPipe = popen("gnuplot -persist", "w");

    if(gnuplotPipe == NULL){
        printf("Error opening GNUPLOT");
        return; 
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'd1_euler_plot.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Behaviour of voltage across the capacitor '\n");
    fprintf(gnuplotPipe, "set xlabel 't [s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C [V]'\n");
    fprintf(gnuplotPipe, "set label 'Euler method' at 3, 3\n");

    fprintf(gnuplotPipe, "plot 'd1_euler_output_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'red'\n"); 

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);
}

// ===================== RUNGE KUTTA 2 METHOD ================= //
void runge_kutta2(double t[], double u[]){

    FILE *fp = NULL; 
    remove("d1_euler_plot.png");
    fp = fopen("d2_rk2_output_data.txt", "w");
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

void gnu_plot2(){
    // ======== GNU PLOT ======================== // 

    FILE  *gnuplotPipe = NULL; 
    remove("d2_rk2_plot.png");
    gnuplotPipe = popen("gnuplot -persist", "w");

    if(gnuplotPipe == NULL){
        printf("Error opening GNUPLOT");
        return; 
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'd2_rk2_plot.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Behaviour of voltage across the capacitor '\n");
    fprintf(gnuplotPipe, "set xlabel 't [s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C [V]'\n");
    fprintf(gnuplotPipe, "set label 'RK2 method' at 3, 3\n");

    fprintf(gnuplotPipe, "plot 'd2_rk2_output_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'red'\n"); 

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);
}

// ===================== RUNGE KUTTA 3 METHOD ================= //
void runge_kutta3(double t[], double u[]){
    double u_next; 
    FILE *fp3 = NULL; 
    remove("d1_euler_plot.png");
    fp3 = fopen("d3_rk3_output_data.txt", "w");
    if(fp3 == NULL){

        printf("Error opening the file RK 3");
        return ; 
    }

    for(int i = 0; i < NUM_STEPS; i++){

        printf("t[%d] = %lf, u[%d] = %lf \n", i, t[i], i, u[i]);
        fprintf(fp3, "%lf \t %lf \n", t[i], u[i]);

        double k1 = derivative(u[i]);
        double k2 = derivative(u[i]+0.5*DT*k1);
        double k3 = derivative(u[i]-DT*k1+2*DT*k2);

        u_next = u[i] + (DT/6)*(k1+4*k2+k3);
        t[i+1] = t[i] + DT; 
        u[i+1] = u_next;  
    }


    fclose(fp3);
}

void gnu_plot3(){
    // ============= GNU PLOT  ============== // 

    FILE  *gnuplotPipe = NULL; 
    remove("d3_rk3_plot.png");
    gnuplotPipe = popen("gnuplot -persist","w");

    if(gnuplotPipe == NULL){
        printf("Error opening GNU PLOT");
        return;
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'd3_rk3_plot.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Behaviour of voltage across the capacitor '\n");
    fprintf(gnuplotPipe, "set xlabel 't[s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C[V]'\n");
    fprintf(gnuplotPipe, "set label 'RK3 method' at 3, 3\n");


    fprintf(gnuplotPipe, "plot 'd3_rk3_output_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'red'\n");

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);
}

// ===================== RUNE KUTTA 4 METHOD ================= //
void runge_kutta4(double t[], double u[]){
    double u_next; 
    FILE *fp = NULL; 
        fp = fopen("d4_rk4_output_data.txt", "w");
        if(fp == NULL){

            printf("Error opening the file");
            return; 
        }

        for(int i = 0; i < NUM_STEPS; i++){

            printf("t[%d] = %lf, u[%d] = %lf \n", i, t[i], i, u[i]);
            fprintf(fp, "%lf \t %lf \n", t[i], u[i]);

            double k1 = DT*derivative(u[i]);
            double k2 = DT*derivative(u[i]+0.5*k1);
            double k3 = DT*derivative(u[i]+0.5*k2);
            double k4 = DT*derivative(u[i]+k3); 

            u_next = u[i] + (1.0/6.0)*(k1+2*k2+2*k3+k4);
            t[i+1] = t[i] + DT; 
            u[i+1] = u_next;  
        }


        fclose(fp);
}

void gnu_plot4(){
    // ======== GNU PLOT ======================== // 

    FILE  *gnuplotPipe = NULL; 
    remove("d4_rk4_plot.png");
    gnuplotPipe = popen("gnuplot -persist", "w");

    if(gnuplotPipe == NULL){
        printf("Error opening GNUPLOT");
        return; 
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'd4_rk4_plot.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Behaviour of voltage across the capacitor '\n");
    fprintf(gnuplotPipe, "set xlabel 't [s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C [V]'\n");
    fprintf(gnuplotPipe, "set label 'RK4 method' at 3, 3\n");

    fprintf(gnuplotPipe, "plot 'd4_rk4_output_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'magenta'\n"); 

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);
}