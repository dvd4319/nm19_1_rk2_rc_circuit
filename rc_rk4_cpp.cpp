#include <iostream>
#include <cstdio>
class RungeKuttaMethods{
public: 
    double E; 
    double C;
    double R; 
    double DT; 
    int NUM_STEPS;

    RungeKuttaMethods(double e, double c, double r, double dt, int num_steps){
        E = e; 
        C = c; 
        R = r; 
        DT = dt; 
        NUM_STEPS = num_steps; 
    }


    double derivative(double u){
        double tau = R*C;
        return (E-u)/tau;  
    }

    void euler1(){
        double* t = new double[NUM_STEPS];
        double* u = new double[NUM_STEPS];
        double u_next; 

        t[0] = 0.0;
        u[0] = 0.0;

        FILE *fpEulerCpp = NULL;
        fpEulerCpp = fopen("rc_euler_output_cpp.txt", "w");
        if(fpEulerCpp == NULL){
            std::cout << "Error opening the file." << std::endl;
            delete[] t;
            delete[] u; 
            return;  
        }

        for(int i = 0; i < NUM_STEPS; i++){
            // std::cout << "t[" << i << "] = " << t[i] << ", u[" << i << "] = " << u[i] << ". " << std::endl; 
            printf("t[%d] = %lf, u[%d] = %lf\n", i, t[i], i, u[i]);
            fprintf(fpEulerCpp, "%lf\t%lf\n", t[i], u[i]);
            u_next = u[i] + DT*derivative(u[i]);
            t[i+1] = t[i] + DT; 
            u[i+1] = u_next;
        }

        fclose(fpEulerCpp);
        delete[] t; 
        delete[] u; 
    }

    void graficEuler(){
        // ================= GNU PLOT ================== //
        FILE  *gnuplotPipe = NULL;

        gnuplotPipe = popen("gnuplot -persist","w");

        if(gnuplotPipe == NULL){
            std::cout << "Error opening GNUPLOT" << std::endl; 
            return; 
        } 

        fprintf(gnuplotPipe, "set terminal png\n");
        fprintf(gnuplotPipe, "set output 'euler_plot_cpp.png'\n");
        fprintf(gnuplotPipe, "set xlabel 't[s]'\n");
        fprintf(gnuplotPipe, "set ylabel 'u[V]'\n");
        fprintf(gnuplotPipe, "set title 'EULER METHOD IN C++ '\n");
        fprintf(gnuplotPipe, "set grid\n");

        fprintf(gnuplotPipe, "plot 'rc_euler_output_cpp.txt' using 1:2 with lines linewidth 2 linecolor rgb 'black'\n");

        fflush(gnuplotPipe);
        fprintf(gnuplotPipe, "exit\n");
        pclose(gnuplotPipe);

    }
};


int main(){

    double E = 5.0;
    double R = 100.0; 
    double C = 0.001; 
    double DT = 0.001; 
    int NUM_STEPS = 500;

    // RungeKuttaMethods(e,c,r,dt,num_steps)
    RungeKuttaMethods rk1x(E,C,R,DT, NUM_STEPS);  

    rk1x.euler1();
    rk1x.graficEuler(); 

    return 0; 
}