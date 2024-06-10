#include <stdio.h>
#define R         1000.0    // resistance R [Ohms]
#define C         0.001     // capacitance C [F]
#define E         5.0       // constant input voltage E [V] 
#define DT        0.01      // time step
#define NUM_STEPS 500       // number of steps

// Function to calculate the derivative (rate of change of voltage across the capacitor)
double derivative(double u) {
    double tau = R*C; 
    return (E - u) / tau; // differential equation of the RC circuit
}

// Runge-Kutta method of second order for solving the differential equation
void runge_kutta(double t[], double u[]) {
    for (int i = 0; i < NUM_STEPS - 1; i++) {
        double k1 = DT * derivative(u[i]);
        double k2 = DT * derivative(u[i] + k1 / 2.0);
        u[i + 1] = u[i] + k2; // update capacitor voltage for the next step
        t[i + 1] = t[i] + DT; // update time for the next step
    }
}

int main() {
    double t[NUM_STEPS]; // array for time
    double u[NUM_STEPS]; // array for voltage

    t[0] = 0.0;  // initial time
    u[0] = 0.0;  // initial voltage across the capacitor

    printf("Applying the Runge-Kutta method to the RC circuit with constant input voltage E = %.2f V\n", E);

    FILE *fp = NULL; 
    fp = fopen("rc_rk2_output_data.txt", "w");

    if(fp == NULL){
        printf("Error opening the file");
        return 1;
    }

    runge_kutta(t, u);

    // Displaying the values of time and voltage
    for (int i = 0; i < NUM_STEPS; i++) {
        printf("Time: %.2f, Voltage: %.4f V\n", t[i], u[i]);
        fprintf(fp, "%lf\t %lf\n", t[i],u[i]);
    }

        // ================= GNU PLOT =========================== // 

    FILE *gnuplotPipe = NULL; 
    gnuplotPipe = popen("gnuplot -persist", "w");

    if (gnuplotPipe == NULL){
        printf("Error opening Gnuplot");
        return 1;
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'rc_rk2_plot.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Behaviour of voltage across the capacitor '\n");
    fprintf(gnuplotPipe, "set xlabel 't [s]'\n");
    fprintf(gnuplotPipe, "set ylabel 'u_C [V]'\n");
    fprintf(gnuplotPipe, "set label 'RK2 method' at 3, 3\n");


    fprintf(gnuplotPipe, "plot 'rc_rk2_output_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'red'\n");

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);

    return 0;
}

