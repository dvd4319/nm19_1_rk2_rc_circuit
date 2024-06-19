#include <stdio.h>
#include <stdlib.h>

#define NUM_STEPS 500 // Assuming 500 steps as in your previous example

void read_column(const char *filename, double *column_data) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    double temp;
    for (int i = 0; i < NUM_STEPS; i++) {
        fscanf(file, "%lf %lf", &temp, &column_data[i]);
    }

    fclose(file);
}

void calculate_error(const double *data1, const double *data2, double *error) {
    for (int i = 0; i < NUM_STEPS; i++) {
        error[i] = data1[i] - data2[i];
    }
}

void write_error_to_file(const char *filename, const double *error) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < NUM_STEPS; i++) {
        fprintf(file, "%d %lf\n", i, error[i]);
    }

    fclose(file);
}

int main() {
    double data1[NUM_STEPS], data2[NUM_STEPS], error[NUM_STEPS];

    // Read column 2 from two files
    read_column("euler_data_x.txt", data1);
    read_column("runge_kutta_4_data.txt", data2);

    // Calculate the error between the two datasets
    calculate_error(data1, data2, error);

    // Write the error data to a file
    write_error_to_file("error_data.txt", error);

    // Plot the error using GNU Plot
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe == NULL) {
        printf("Error opening GNU Plot\n");
        return 1;
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'error_plot.png'\n");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title 'Error between RK2 and RK4'\n");
    fprintf(gnuplotPipe, "set xlabel 'Index'\n");
    fprintf(gnuplotPipe, "set ylabel 'Error'\n");
    fprintf(gnuplotPipe, "plot 'error_data.txt' using 1:2 with lines linewidth 2 linecolor rgb 'blue' title 'Error'\n");

    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);

    return 0;
}
