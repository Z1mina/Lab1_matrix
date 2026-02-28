#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

void multiply(int n, int A[1000][1000], int B[1000][1000], int C[1000][1000])
{
    int i, j, k;
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
    std::cout << "Enter matrix size: ";
    std::cin >> n;

    static int A[1000][1000];
    static int B[1000][1000];
    static int C[1000][1000];

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

    clock_t start = clock();

    multiply(n, A, B, C);

    clock_t end = clock();

    std::ofstream Cfile("Result.txt");

    Cfile << n << "\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            Cfile << C[i][j] << " ";
        Cfile << "\n";
    }

    Cfile.close();

    double t = (double)(end - start) / CLOCKS_PER_SEC;

    std::cout << "Time = " << t << "\n";
    std::cout << "Operations = " << (long long)n * n * n << "\n";

    return 0;
}