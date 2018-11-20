//mpicxx -std=c++11 matrixvector.cpp -o matrixvector
#include <iostream>
#include "mpi.h" 
#include <cmath>
#include <fstream>
#include <cstdlib>

#define MASTER 0

using namespace std;

double * init_matrix(uint64_t rows, uint64_t columns) {
    double * A = (double *)malloc(rows * columns * sizeof(double *));
    return A;
}

double * init_vector(uint64_t n) {
    double * v = (double *)malloc(n * sizeof(double));
    return v;
}

void read_matrix(double * A, uint64_t rows, uint64_t columns, MPI_File f) {
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < columns; j++) 
            MPI_File_read(f, &A[i * columns + j], 1, MPI_DOUBLE, NULL);    
}

void read_vector(double * v, uint64_t n, MPI_File f) {
    for (uint64_t i = 0; i < n; i++) {
        MPI_File_read(f, &v[i], 1, MPI_DOUBLE, NULL);
    }
}

void write_vector(double * v, uint64_t n, MPI_File f) {
    MPI_File_write(f, &n, 1, MPI_UINT64_T, NULL); 
    uint64_t m = 1;
    MPI_File_write(f, &m, 1, MPI_UINT64_T, NULL);
    for (uint64_t i = 0; i < n; i++) {
        MPI_File_write(f, &v[i], 1, MPI_DOUBLE, NULL);
    }
}
//./matrixvector A.dat b.dat c.dat
int main(int argc, char ** argv) {
    if (argc != 4) {
        cerr << "Wrong number of arguments!" << endl;
        return -1;
    }
    uint64_t sizes[4];//n_A, m_A, n_b, m_b
    int rank, nproc;
    double * part_A, * A;
    double * part_b, * b;
    double * part_c, * c;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == MASTER) { //reading data
        MPI_File f_A, f_b;
        int er = MPI_File_open(MPI_COMM_SELF, argv[1], MPI_MODE_RDONLY | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &f_A);
        er = MPI_File_open(MPI_COMM_SELF, argv[2], MPI_MODE_RDONLY | MPI_MODE_UNIQUE_OPEN, MPI_INFO_NULL, &f_b);
        if (er != MPI_SUCCESS) {
            cerr << "Cannot open file" << endl;
            return -1;
        }
        MPI_File_read(f_A, &sizes[0], 1, MPI_UINT64_T, NULL);
        MPI_File_read(f_A, &sizes[1], 1, MPI_UINT64_T, NULL);
        MPI_File_read(f_b, &sizes[2], 1, MPI_UINT64_T, NULL);
        MPI_File_read(f_b, &sizes[3], 1, MPI_UINT64_T, NULL);
        if (sizes[3] != 1 || sizes[1] != sizes[2]) {//m_b != 1 || m_A != n_b
            cerr << "Wrong size of vector" << endl;
            return -1;
        }
        if (sizes[0] >= sizes[1]) // n >= m
            A = init_matrix(nproc * (sizes[0] / nproc + 1), sizes[1]); 
        else // n < m
            A = init_matrix(sizes[0], nproc * (sizes[1] / nproc + 1));
        read_matrix(A, sizes[0], sizes[1], f_A);
        b = init_vector(nproc * (sizes[2] / nproc + 1)); 
        read_vector(b, sizes[2], f_b);
        c = init_vector(nproc * (sizes[0] / nproc + 1));
        MPI_File_close(&f_A);
        MPI_File_close(&f_b);
    }
    //sending and receiving data
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&sizes, 4, MPI_UINT64_T, MASTER, MPI_COMM_WORLD);
    if (sizes[0] >= sizes[1]) { //n >= m
        //rows of matrix and whole vector
        part_b = init_vector(nproc * (sizes[2] / nproc + 1));
        part_A = init_matrix(sizes[0] / nproc + 1, sizes[1]);
        if (rank == MASTER) {
            for (uint64_t i = 0; i < nproc * (sizes[2] / nproc + 1); i++) {
                  part_b[i] = b[i]; 
            }
        }
        int er = MPI_Scatter(A, sizes[1] * (sizes[0] / nproc + 1), MPI_DOUBLE, 
                part_A, sizes[1] * (sizes[0] / nproc + 1), MPI_DOUBLE, 
                MASTER, MPI_COMM_WORLD);
        er = MPI_Bcast(part_b, nproc * (sizes[2] / nproc + 1), MPI_DOUBLE, MASTER, MPI_COMM_WORLD);

    } else { // n < m 
        //columns of matrix and parts of vector
        part_b = init_vector(sizes[2] / nproc + 1);
        part_A = init_matrix(sizes[0], sizes[1] / nproc + 1);
        for (uint64_t i = 0; i < nproc; i++) {
            MPI_Scatter(&A[i], sizes[1] / nproc + 1, MPI_DOUBLE,
                    &part_A[i * (sizes[1] / nproc + 1)], sizes[1] / nproc + 1, MPI_DOUBLE,
                    MASTER, MPI_COMM_WORLD);
            MPI_Scatter(b, sizes[2] / nproc + 1, MPI_DOUBLE,
                    part_b, sizes[2] / nproc + 1, MPI_DOUBLE,
                    MASTER, MPI_COMM_WORLD);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    //processing data
    if (sizes[0] >= sizes[1]) { // n >= m
        part_c = init_vector(sizes[0] / nproc + 1);
        for (uint64_t i = 0; i < sizes[0] / nproc + 1 && 
                rank * (sizes[0] / nproc + 1) + i < sizes[0] ; i++) {
            part_c[i] = 0.0;
            for (uint64_t j = 0; j < sizes[1]; j++) {
                part_c[i] += part_A[i * sizes[1] + j] * part_b[j];
            }
        }
        MPI_Gather(part_c, sizes[0] / nproc + 1, MPI_DOUBLE,
                c, sizes[0] / nproc + 1, MPI_DOUBLE,
                MASTER, MPI_COMM_WORLD);
        free(part_A);
        free(part_b);
        free(part_c);
    } else { // n < m
        part_c = init_vector(nproc * (sizes[0] / nproc + 1));
        for (uint64_t i = 0; i < sizes[0]; i++) {
            part_c[i] = 0.0;
            for (uint64_t j = 0; j < sizes[1] / nproc + 1 && 
                    rank * (sizes[1] / nproc + 1) + j < sizes[1]; j++) {
                part_c[i] += part_A[i * (sizes[1] / nproc + 1) + j] * part_b[j];
            }
        }
        MPI_Reduce(part_c, c, nproc * (sizes[0] / nproc + 1), MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
        free(part_A);
        free(part_b);
        free(part_c);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    //data output
    if (rank == MASTER) {
        free(A);
        free(b);
        MPI_File f_c;
        int er = MPI_File_open(MPI_COMM_SELF, argv[3], MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &f_c);
        if (er != MPI_SUCCESS) {
            cerr << "Cannot open file for vector c at Master process" << endl;
            return -1;
        }
        write_vector(c, sizes[0], f_c);
        free(c);
        MPI_File_close(&f_c);
    }
    MPI_Finalize();
    return 0;
}