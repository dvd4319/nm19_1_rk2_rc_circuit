#include <stdio.h>
#include "rc_input_data.h"
#include "rc_input_data.c"

int main(){

    double t[NUM_STEPS];
    double u[NUM_STEPS];

    t[0] = 0.0; 
    u[0] = 0.0; 

    runge_kutta3(t, u);
    gnu_plot3();

    return 0; 
}