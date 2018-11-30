//mpicxx -std=c++11 new_mv.cpp -o new_mv
#include <iostream>
#include "mpi.h" 
#include "time.h"
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <sstream>
//#include <cstdint>

#define MASTER 0
#define NANOSEC 1000000000

using namespace std;

double * init_matrix(int rows, int columns) {
    double * A = (double *)malloc(rows * columns * sizeof(double));
    return A;
}

double * init_vector(int n) {
    double * v = (double *)malloc(n * sizeof(double));
    return v;
}

//./new_mv A.dat b.dat c.dat
int main(int argc, char ** argv) {
    if (argc != 4) {
        cerr << "Wrong number of arguments!" << endl;
        return -1;
    }
    int sizes[4];//n_A, m_A, n_b, m_b
    int rank, nproc, count;
    double * part_A = NULL;
    double * part_b = NULL;
    double * part_c = NULL, * c = NULL;
    double time_one = 0.0, time_all = 0.0;
    //struct timespec start, finish;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_File f_A, f_b, f_c;
    int er = MPI_File_open(MPI_COMM_WORLD, argv[1], MPI_MODE_RDONLY | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &f_A);
    er = MPI_File_open(MPI_COMM_WORLD, argv[2], MPI_MODE_RDONLY | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &f_b);
    if (er != MPI_SUCCESS) {
        cerr << "Cannot open file" << endl;
        return -1;
    }
    if (rank == MASTER) { //reading data
        MPI_File_read_shared(f_A, &sizes[0], 1, MPI_INT, NULL);
        MPI_File_read_shared(f_A, &sizes[1], 1, MPI_INT, NULL);
        MPI_File_read_shared(f_b, &sizes[2], 1, MPI_INT, NULL);
        MPI_File_read_shared(f_b, &sizes[3], 1, MPI_INT, NULL);
        if (sizes[3] != 1 || sizes[1] != sizes[2]) {//m_b != 1 || m_A != n_b
            cerr << "Wrong size of vector" << endl;
            return -1;
        }
    }
    MPI_Bcast(&sizes, 4, MPI_INT, MASTER, MPI_COMM_WORLD);
    if (sizes[0] >= sizes[1]) { // n >= m
        //rows of matrix and whole vector
        part_b = init_vector(sizes[2]);
        //double * const bfree = part_b;
        if (rank != nproc - 1) {
            count = sizes[0] / nproc;
        } else {
            count = sizes[0] / nproc + sizes[0] % nproc;
        }
        part_A = init_matrix(count, sizes[1]);
        //double  * const afree = part_A;
        MPI_File_read_ordered(f_A, part_A, count * sizes[1], MPI_DOUBLE, NULL);
        if (rank == MASTER) {
            MPI_File_read_shared(f_b, part_b, sizes[2], MPI_DOUBLE, NULL);
        }
        MPI_Bcast(part_b, sizes[2], MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        time_one = MPI_Wtime();
        part_c = init_vector(count);
        //double * const cfree = part_c;
        for (int i = 0; i < count && 
                rank * count + i < sizes[0] ; i++) {
            part_c[i] = 0.0;
            for (int j = 0; j < sizes[1]; j++) {
                part_c[i] += part_A[i * sizes[1] + j] * part_b[j];
            }
        }
        time_one = MPI_Wtime() - time_one;
        MPI_File_open(MPI_COMM_WORLD, argv[3], MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f_c);
        if (rank == MASTER) {
            MPI_File_write_shared(f_c, &sizes[0], 1, MPI_INT, NULL);
            int m = 1;
            MPI_File_write_shared(f_c, &m, 1, MPI_INT, NULL);
        }
        MPI_File_write_ordered(f_c, part_c, count, MPI_DOUBLE, NULL);
        MPI_File_close(&f_c);
    } else {// n < m 
        //columns of matrix and parts of vector
        if (rank != nproc - 1) {
            count = sizes[1] / nproc;
        } else {
            count = sizes[1] / nproc + sizes[1] % nproc;
        }
        part_b = init_vector(count);
        //double * const bfree = part_b;
        part_A = init_matrix(sizes[0], count);
        //double * const afree = part_A;
        for (int i = 0; i < sizes[0]; i++) {
            MPI_File_read_ordered(f_A, part_A + i * count, count, MPI_DOUBLE, NULL);
        }
        MPI_File_read_ordered(f_b, part_b, count, MPI_DOUBLE, NULL);
        MPI_Barrier(MPI_COMM_WORLD);
        time_one = MPI_Wtime();
        part_c = init_vector(sizes[0]);
        //double * const cfree = part_c;
        for (int i = 0; i < sizes[0]; i++) {
            part_c[i] = 0.0;
            for (int j = 0; j < count && 
                    rank * count + j < sizes[1]; j++) {
                part_c[i] += part_A[i * count + j] * part_b[j];
            }
        }
        if (rank == MASTER) {
            c = init_vector(sizes[0]);
        }
        MPI_Reduce(part_c, c, sizes[0], MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
        time_one = MPI_Wtime() - time_one;
        if (rank == MASTER) {
            MPI_File_open(MPI_COMM_SELF, argv[3], MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f_c);
            MPI_File_write(f_c, &sizes[0], 1, MPI_INT, NULL);
            int m = 1;
            MPI_File_write(f_c, &m, 1, MPI_INT, NULL);
            MPI_File_write(f_c, c, sizes[0], MPI_DOUBLE, NULL);
            free(c);
            MPI_File_close(&f_c);
        }   
    }
    for (int i = 0; i < nproc; i++) {
        if (rank == i) {
            cout << time_one << endl;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Reduce(&time_one, &time_all, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
    if (rank == MASTER) {
        cout << time_all << endl;
    }
    if (part_A) free(part_A);
    if (part_b) free(part_b);
    if (part_c) free(part_c);
    MPI_File_close(&f_A);
    MPI_File_close(&f_b);
    MPI_Finalize();
    //fclose(f_time);
    return 0;
}