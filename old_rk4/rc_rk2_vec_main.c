#include <stdio.h>
#include "rc_input_data.h"
#include "rc_input_data.c"

int main(){

    double t[NUM_STEPS]; // array for time
    double u[NUM_STEPS]; // array for voltage

    t[0] = 0.0;  // initial time
    u[0] = 0.0;  // initial voltage across the capacitor

    printf("Applying the Runge-Kutta method to the RC circuit with constant input voltage E = %.2f V\n", E);

    runge_kutta_2(t,u); 
    gnu_plot2(); 

    return 0; 
}

