#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace chrono;

// Función para multiplicar matrices clásicamente
void multiplyMatrices(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& result) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// Función para multiplicar matrices por bloques con 5 bucles anidados
void multiplyMatricesByBlocks5(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& result, int blockSize) {
    int n = matrix1.size();

    for(int jj=0;jj<n;jj+= blockSize){
        for(int kk=0;kk<n;kk+= blockSize){
            for(int i=0;i<n;i++){
                for(int j = jj; j<((jj+blockSize)>n?n:(jj+blockSize)); j++){
                    int temp = 0;
                    for(int k = kk; k<((kk+blockSize)>n?n:(kk+blockSize)); k++){
                            temp += matrix1[i][k]*matrix2[k][j];
                    }
                    result[i][j] += temp;
                }
            }
        }
    }
}

// Función para multiplicar matrices por bloques con 6 bucles anidados
void multiplyMatricesByBlocks6(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2, vector<vector<int>>& result, int blockSize) {
    int n = matrix1.size();

    for (int ii = 0; ii < n; ii += blockSize) {
        for (int jj = 0; jj < n; jj += blockSize) {
            for (int kk = 0; kk < n; kk += blockSize) {
                for (int i = ii; i < min(ii + blockSize, n); i++) {
                    for (int j = jj; j < min(jj + blockSize, n); j++) {
                        int temp = 0;
                        for (int k = kk; k < min(kk + blockSize, n); k++) {
                            temp += matrix1[i][k] * matrix2[k][j];
                        }
                        result[i][j] += temp;
                    }
                }
            }
        }
    }
}

// Función para comparar si dos matrices son iguales
bool areMatricesEqual(const vector<vector<int>>& matrix1, const vector<vector<int>>& matrix2) {
    // Verificar si las dimensiones de las matrices son iguales
    if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        return false;
    }

    int rows = matrix1.size();
    int cols = matrix1[0].size();

    // Comparar elemento por elemento
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false; // Se encontró un elemento diferente, las matrices no son iguales
            }
        }
    }

    // Si no se encontraron diferencias, las matrices son iguales
    return true;
}

// Función para imprimir una matriz con formato y sangría
void printMatrix(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << matrix[i][j];
        }
        cout << endl; // Salto de línea después de cada fila
    }
}

int main() {
    // Tamaños de las matrices
    int sizes[] = {300, 400, 500, 600, 700};

    // Tamaños de bloque para caché L1, L2 y L3
    int blockSizes[] = {256, 1024, 8192};

    for (int size : sizes) {
        cout << "\tTAMANO DE MATRIZ: " << size << "x" << size << endl;
        for (int blockSize : blockSizes) {
            cout << "\t\tTAMANO DE BLOQUE: " << blockSize << endl;
            // Inicializar matrices aleatorias
            vector<vector<int>> matrix1(size, vector<int>(size, (int)(rand() % 9 + 1)));
            vector<vector<int>> matrix2(size, vector<int>(size, (int)(rand() % 9 + 1)));

            vector<vector<int>> resultClassic(size, vector<int>(size, 0));
            vector<vector<int>> resultBlocks5(size, vector<int>(size, 0));
            vector<vector<int>> resultBlocks6(size, vector<int>(size, 0));

            // Medir el tiempo de ejecución para la multiplicación clásica
            auto start = high_resolution_clock::now();
            multiplyMatrices(matrix1, matrix2, resultClassic);
            auto stop = high_resolution_clock::now();

            // Calcular el tiempo transcurrido en milisegundos
            auto durationClassic = duration_cast<milliseconds>(stop - start);

            cout << "\t\t\tTiempo de ejecucion (clasico): " << durationClassic.count() << " ms" << endl;

            // Medir el tiempo de ejecución para la multiplicación por bloques con 5 bucles anidados
            start = high_resolution_clock::now();
            multiplyMatricesByBlocks5(matrix1, matrix2, resultBlocks5, blockSize);
            stop = high_resolution_clock::now();

            // Calcular el tiempo transcurrido en milisegundos
            auto durationBlocks5 = duration_cast<milliseconds>(stop - start);

            cout << "\t\t\tTiempo de ejecucion (por bloques, 5 bucles): " << durationBlocks5.count() << " ms" << endl;

            // Medir el tiempo de ejecución para la multiplicación por bloques con 6 bucles anidados
            start = high_resolution_clock::now();
            multiplyMatricesByBlocks6(matrix1, matrix2, resultBlocks6, blockSize);
            stop = high_resolution_clock::now();

            // Calcular el tiempo transcurrido en milisegundos
            auto durationBlocks6 = duration_cast<milliseconds>(stop - start);

            cout << "\t\t\tTiempo de ejecucion (por bloques, 6 bucles): " << durationBlocks6.count() << " ms" << endl;
            cout << "\t\t\t\tResultado (5 bucles): " << (areMatricesEqual(resultClassic, resultBlocks5) ? "CORRECTO" : "INCORRECTO")  << endl;
            cout << "\t\t\t\tResultado (5 bucles): " << (areMatricesEqual(resultClassic, resultBlocks6) ? "CORRECTO" : "INCORRECTO")  << endl;

            //printMatrix(resultClassic);
            //printMatrix(resultBlocks5);
            //printMatrix(resultBlocks6);
        }
    }

    return 0;
}