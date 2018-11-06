#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <mpi.h>
#include <unistd.h>
 
using namespace std;
int main(int argc, char ** argv) {
    clock_t t_all = clock();
    if (argc != 4) {
        cerr << "Wrong command line, supposed to be ./eratosthenes A B file_name" << endl;
        return -1;
    }
    int A, B;
    MPI_File f;
    try {
        A = atoi(argv[1]);
        B = atoi(argv[2]);
    } catch (exception & e) {
        cerr << e.what();
        return -1;
    } catch (...) {
        cerr << "Some error with data from command line occured" << endl;
        return -1;
    }
    int N_SQRT = floor(sqrt(B));    
    bool * primes_bool = new bool[N_SQRT + 1];
    int i, j, count = 0;
    memset(primes_bool, true, sizeof(bool) * (N_SQRT + 1));
    for (i = 2; i <= N_SQRT; i++)
        if(primes_bool[i])
            for(j = i * i; j <= N_SQRT; j += i)
                primes_bool[j] = false;
    for (i = 2; i <= N_SQRT; i++)
        if(primes_bool[i]) {
            count++;
        }
    int * PRIMES = new int[count];
    j = 0;
    for(i = 2; i <= N_SQRT; i++)
        if (primes_bool[i]) {
            PRIMES[j] = i;
            j++;
        } 
    delete[] primes_bool;
    int nproc, rank;
    int N = max((int)sqrt(B) + 1, A);
    int sum = 0;
    int sum_all = 0;
    const char * buf = new char[20]; 
    MPI_Status status;
    clock_t t_MPI = clock();
    MPI_Init(&argc, &argv);
    int er = MPI_File_open(MPI_COMM_WORLD, argv[3], MPI_MODE_CREATE | MPI_MODE_DELETE_ON_CLOSE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f);
    er = MPI_File_close(&f);
    er = MPI_File_open(MPI_COMM_WORLD, argv[3], MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f);
    if (er != MPI_SUCCESS) {
        cerr << "Cannot open file";
        return -1;
    }
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int part = (B - N + 1)/nproc + 1;
    bool * NUMBERS = new bool[part];
    memset(NUMBERS, true, sizeof(bool) * part);
    for (i = 0; i < part && N + i + part * rank <= B; i++) {
        for (j = 0; j < count; j++) {
            if ((N + i + part * rank) % PRIMES[j] == 0) NUMBERS[i] = false;
        }
    }
    clock_t T_write = clock();
    for (i = 0; i < part && N + i + part * rank <= B; i++) {
        if (NUMBERS[i]) {
            sum++;
            string num = to_string(N + i + part * rank) + " ";
            buf = num.c_str();
            MPI_File_write_shared(f, buf, strlen(buf), MPI_CHAR, &status);
        }
    }
    T_write = clock() - T_write;
    delete[] NUMBERS;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&sum, &sum_all, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        clock_t T = clock();
        cout << "Time of MPI program: " << (T - t_MPI - T_write)/(double)CLOCKS_PER_SEC << endl;
        int count1 = 0;
        for (i = 0; i < count; i++) {
            if (PRIMES[i] >= A) {
                string num = to_string(PRIMES[i]) + " ";
                buf = num.c_str();
                MPI_File_write_shared(f, buf, strlen(buf), MPI_CHAR, &status);
                count1++;
            }
        }
        T = clock();
        cout << "Time of whole program: " << (T - t_all)/(double)CLOCKS_PER_SEC << endl;
        //cout << endl;
        cout << "Number of primes within [A;B]: " << sum_all + count1 << endl; //consider if they are < A
    }
    delete[] PRIMES;
    MPI_File_close(&f);
    MPI_Finalize();
    return 0;
}
