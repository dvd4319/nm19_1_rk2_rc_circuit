#define R         1000.0    // resistance R [Ohms]
#define C            0.001  // capacitance C [F]
#define E            5.0    // constant input voltage E [V] 
#define DT           0.1   // time step delta  
#define NUM_STEPS  500      // number of steps 

// Function to calculate the derivative (du/dt)
double derivative(double u) {
    return (E - u) / (R * C);
}