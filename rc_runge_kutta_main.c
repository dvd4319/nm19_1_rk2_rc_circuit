#include <stdio.h>
#include "rc_constants.h"
#include "rc_input_data.h"
//#include "rc_input_data.c"
void euler(double t[], double u[]);
void runge_kutta2(double t[], double u[]);
void runge_kutta3(double t[], double u[]);
void runge_kutta4(double t[], double u[]);
void gnu_plot1(void);
void gnu_plot2(void);
void gnu_plot3(void);
void gnu_plot4(void);
void gnu_plt();

int main(){

    double t1[NUM_STEPS];
    double u1[NUM_STEPS];
    double t2[NUM_STEPS];
    double u2[NUM_STEPS];
    double t3[NUM_STEPS];
    double u3[NUM_STEPS];
    double t4[NUM_STEPS];
    double u4[NUM_STEPS];

    t1[0] = 0.0; 
    u1[0] = 0.0; 
    t2[0] = 0.0; 
    u2[0] = 0.0; 
    t3[0] = 0.0; 
    u3[0] = 0.0; 
    t4[0] = 0.0; 
    u4[0] = 0.0; 
   

    euler(t1,u1);
    runge_kutta2(t2, u2);
    runge_kutta3(t3, u3);
    runge_kutta4(t4, u4); 

    gnu_plot1();
    gnu_plot2();
    gnu_plot3();
    gnu_plot4();

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