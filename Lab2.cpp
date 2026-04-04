#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include <omp.h>

void multiply(int n, int A[2000][2000], int B[2000][2000], int C[2000][2000])
{
    int i, j, k;
    #pragma omp parallel for
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            C[i][j] = 0;
            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main()
{
    int n;
    int threads;

    std::cout << "Enter matrix size: ";
    std::cin >> n;

    std::cout << "Enter number of threads: ";
    std::cin >> threads;

    omp_set_num_threads(threads);

    std::cout << "Max available threads: " << omp_get_max_threads() << "\n";

    static int A[2000][2000];
    static int B[2000][2000];
    static int C[2000][2000];

    std::ofstream Afile("A_matrix.txt");
    std::ofstream Bfile("B_matrix.txt");

    srand(time(0));

    Afile << n << "\n";
    Bfile << n << "\n";

    int i, j;

    // генерация и запись
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;

            Afile << A[i][j] << " ";
            Bfile << B[i][j] << " ";
        }
        Afile << "\n";
        Bfile << "\n";
    }

    Afile.close();
    Bfile.close();

    double start = omp_get_wtime();

    multiply(n, A, B, C);

    double end = omp_get_wtime();

    std::ofstream Cfile("Result.txt");

    Cfile << n << "\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            Cfile << C[i][j] << " ";
        Cfile << "\n";
    }

    Cfile.close();

    double t = end - start;

    std::cout << "\n    RESULT    \n";
    std::cout << "Matrix size: " << n << " x " << n << "\n";
    std::cout << "Threads: " << threads << "\n";
    std::cout << "Time: " << t << " sec\n";
    std::cout << "Operations: " << (long long)n * n * n << "\n";

    return 0;
}