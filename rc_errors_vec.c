#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 1000 // Maximum number of data points

int main() {
    FILE *file1, *file2;
    double data1[MAX_SIZE], data2[MAX_SIZE];
    int num_points = 0;

    // Open the first file
    file1 = fopen("rc_euler_output_data.txt", "r");
    if (file1 == NULL) {
        printf("Error opening data1.txt\n");
        return 1;
    }

    // Open the second file
    file2 = fopen("rc_euler_output_data.txt", "r");
    if (file2 == NULL) {
        printf("Error opening data2.txt\n");
        return 1;
    }

    // Read data from both files
    while (fscanf(file1, "%*lf %lf", &data1[num_points]) == 1 &&
           fscanf(file2, "%*lf %lf", &data2[num_points]) == 1) {
        num_points++;
    }

    // Calculate errors and apply error formula
    double total_error = 0.0;
    for (int i = 0; i < num_points; i++) {
        double error = fabs(data1[i] - data2[i]); // Absolute error
        // Apply your error formula here if needed
        total_error += error;
    }

    // Calculate average error
    double average_error = total_error / num_points;

    printf("Average error: %.6f\n", average_error);

    // Close the files
    fclose(file1);
    fclose(file2);

    return 0;
}
