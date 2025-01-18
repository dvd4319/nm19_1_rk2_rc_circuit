#ifndef RC_INPUT_DATA_H
#define RC_INPUT_DATA_H

// Include constants header
#include "rc_constants.h"

// Function declarations
void runge_kutta3(double *t, double *u);
void runge_kutta4(double *t, double *u);
void gnu_plot2(void);
void gnu_plot3(void);
void gnu_plot4(void);
void gnu_plt(void);

#endif
