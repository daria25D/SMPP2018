#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <fstream>
#include <mpi.h>

using namespace std;

int main(int argc, char ** argv) {
    uint64_t t_all = clock();
    if (argc != 4) {
        cerr << "Wrong command line, supposed to be ./eratosthenes A B file_name" << endl;
        return -1;
    }
    int A, B;
    fstream f;
    try {
        A = atoi(argv[1]);
        B = atoi(argv[2]);
        f.open(argv[3], ios::out);
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
    uint64_t t_MPI = clock();
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int part = (B - N + 1)/nproc + 1;
    bool * NUMBERS = new bool[part * nproc];
    memset(NUMBERS, true, sizeof(bool) * (part * nproc));
    for (i = rank * part; i < part * (rank + 1) && i < B - N + 1; i++) {
        for (j = 0; j < count; j++) {
            if ((N + i) % PRIMES[j] == 0) NUMBERS[i] = false;
        }
    }
    for (i = rank * part; i < part * (rank + 1) && i < B - N + 1; i++) {
        if (NUMBERS[i]) sum++;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&sum, &sum_all, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Gather(NUMBERS + part * rank, part, MPI_C_BOOL, NUMBERS, part, MPI_C_BOOL, 0, MPI_COMM_WORLD);
    if (rank == 0) {   
        int count1 = 0;
        for (i = 0; i < count; i++) {
            if (PRIMES[i] >= A) {
                f << PRIMES[i] << ' ';
                count1++;
            }
        }
        for (i = 0; i < B - N + 1; i++) {
            if (NUMBERS[i]) f << N + i << ' ';
        }
        cout << "Number of primes within [A;B]: " << sum_all + count1 << endl; //consider if they are < A
        uint64_t T = clock();
        cout << "Time of whole proram: " << (T - t_all)/(double)CLOCKS_PER_SEC << endl;
        cout << "Time of MPI program: " << (T - t_MPI)/(double)CLOCKS_PER_SEC << endl;
    }
    MPI_Finalize();
	return 0;
}