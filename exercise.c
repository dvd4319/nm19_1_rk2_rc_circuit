#include <stdio.h>

#define E 5.0
#define C 0.001 
#define R 100.0 
#define DT 0.001
#define NUM_STEPS 500 

double derivative(double u);
void euler(double t[], double u[]);
void rk4(double t[], double u[]);
void gnu_plt();

int main(){

    double t_euler[NUM_STEPS];
    double u_euler[NUM_STEPS];

    double t_rk4[NUM_STEPS];
    double u_rk4[NUM_STEPS];

    t_euler[0] = t_rk4[0] = 0.0; 
    u_euler[0] = u_rk4[0] = 0.0; 

    rk4(t_rk4, u_rk4); 
    euler(t_euler, u_euler);
    gnu_plt();

    return 0; 
}

double derivative(double u){
    double tau = R*C; 
    return (E-u)/tau; 
}

void euler(double t[], double u[]){
    FILE *fp_euler = NULL;
    fp_euler = fopen("euler_data_x.txt","w");
    if(fp_euler == NULL){
        printf("Error opening the file");
        return; 
    }

    for (int i = 0; i < NUM_STEPS; i++){
        printf("t_eu[%d] = %lf, u_eu[%d] = %lf \n", i, t[i], i, u[i]);
        fprintf(fp_euler, "%lf\t%lf\n", t[i], u[i]);
        if (i < NUM_STEPS - 1) {
            u[i+1] = u[i] + DT*derivative(u[i]);
            t[i+1] = t[i] + DT; 
        }
    }

    fclose(fp_euler);
}

void rk4(double t[], double u[]){
    double u_next; 
    FILE *fp = NULL; 
    fp = fopen("runge_kutta_4_data_x.txt", "w");
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
        if (i < NUM_STEPS - 1) {
            t[i+1] = t[i] + DT; 
            u[i+1] = u_next;  
        }
    }

    fclose(fp);
}

void gnu_plt(){
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

    fprintf(gnuplotPipe, "plot 'euler_data_x.txt' using 1:2 with lines linewidth 2 linecolor rgb 'blue' title 'Euler Method',");
    fprintf(gnuplotPipe, "'runge_kutta_4_data_x.txt' using 1:2 with lines linewidth 2 linecolor rgb 'red' title 'RK4 Method'\n");

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);
}
