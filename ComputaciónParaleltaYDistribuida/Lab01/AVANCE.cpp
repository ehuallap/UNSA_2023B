#include <iostream>
#include <cstring>
#include <chrono>
using namespace std;

#define MAX 500

int main() {
    int i, j;
    double A[MAX][MAX], x[MAX], y[MAX];

    /* Initialize A and x, assign y = 0 */
    memset(A, 2, sizeof(A));
    memset(x, 3, sizeof(x));
    memset(y, 0, sizeof(y));
    
    auto start_time = std::chrono::high_resolution_clock::now();
    /* First pair of loops */
    for (i = 0; i < MAX; i++)
        for (j = 0; j < MAX; j++)
            y[i] += A[i][j]*x[j];
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);

    cout << "PRIMER BUCLE CON: " << duration.count() << " milisegundos" << endl;
    
    /* Assign y = 0 */
    memset(y, 0, sizeof(y));

    start_time = std::chrono::high_resolution_clock::now();
    /* Second pair of loops */
    for (j = 0; j < MAX; j++)
        for (i = 0; i < MAX; i++)
            y[i] += A[i][j]*x[j];
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time);

    cout << "SEGUNDO BUCLE CON: " << duration.count() << " milisegundos" << endl;
}