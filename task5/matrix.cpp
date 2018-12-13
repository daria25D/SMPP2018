#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "mpi.h"
#include <time.h>
#include <sys/time.h>
#define NUM_DIMS 3
using namespace std;
void PMATMAT_3(int * sizes, double * A, double * B, double * C, int * grid_sizes, MPI_Comm comm) {
    double * A_sub_matrix, * B_sub_matrix, * C_sub_matrix, * C_reduced;   
    int coords[3];  
    int sub_sizes[3];           
    int rank;    
    int * disp_a, * disp_b, * disp_c, * count_a, * count_b, * count_c;
    MPI_Datatype type_a, type_b, type_c, types[2];
    int periods[3], remains[3];
    MPI_Comm comm_3D, comm_2D[3], comm_1D[3], pcomm;
    int i, j, k, blen[2];
    MPI_Aint disp[2];
    MPI_Comm_dup(comm, &pcomm);
    MPI_Bcast(sizes, 3, MPI_INT, 0, pcomm);
    MPI_Bcast(grid_sizes, 3, MPI_INT, 0, pcomm);
    for (i = 0; i < 3; i++)
        periods[i] = 0;
    MPI_Cart_create(pcomm, 3, grid_sizes, periods, 0, &comm_3D);
    MPI_Comm_rank(comm_3D, &rank);
    MPI_Cart_coords(comm_3D, rank, 3, coords);
    for (i = 0; i < 3; i++) { 
        for (j = 0; j < 3; j++)
              remains[j] = (i != j);
        MPI_Cart_sub(comm_3D, remains, &comm_2D[i]);
    }
    for (i = 0; i < 3; i++) { 
        for (j = 0; j < 3; j++)
            remains[j] = (i == j);
        MPI_Cart_sub(comm_3D, remains, &comm_1D[i]);
    }
    for (i = 0; i < 3; i++)
        sub_sizes[i] = sizes[i]/grid_sizes[i];
    A_sub_matrix = (double *)malloc(sub_sizes[0] * sub_sizes[1] * sizeof(double));
    B_sub_matrix = (double *)malloc(sub_sizes[1] * sub_sizes[2] * sizeof(double));
    C_sub_matrix = (double *)malloc(sub_sizes[0] * sub_sizes[2] * sizeof(double));
    if (rank == 0) {
        MPI_Type_vector(sub_sizes[0], sub_sizes[1], sizes[1], MPI_DOUBLE, &types[0]);
        blen[0] = 1;
        blen[1] = 1;
        disp[0] = 0;
        disp[1] = sizeof(double) * sub_sizes[1];
        types[1] = MPI_UB;
        MPI_Type_create_struct(2, blen, disp, types, &type_a);
        MPI_Type_commit(&type_a);
        disp_a = (int *)malloc(grid_sizes[0] * grid_sizes[1] * sizeof(int));
        count_a = (int *)malloc(grid_sizes[0] * grid_sizes[1] * sizeof(int));
        for (j = 0; j < grid_sizes[0]; j++)
            for (i = 0; i < grid_sizes[1]; i++) { 
                disp_a[j * grid_sizes[1] + i] = (j * grid_sizes[1] * sub_sizes[0] + i);
                count_a[j * grid_sizes[1] + i] = 1;
            }
        MPI_Type_vector(sub_sizes[1], sub_sizes[2], sizes[2], MPI_DOUBLE, &types[0]);
        disp[1] = sizeof(double) * sub_sizes[2];
        MPI_Type_create_struct(2, blen, disp, types, &type_b);
        MPI_Type_commit(&type_b);
        disp_b = (int *)malloc(grid_sizes[1] * grid_sizes[2] * sizeof(int));
        count_b = (int *)malloc(grid_sizes[1] * grid_sizes[2] * sizeof(int));
        for (j = 0; j < grid_sizes[1]; j++)
            for (i = 0; i < grid_sizes[2]; i++) { 
                disp_b[j * grid_sizes[2] + i] = (j * grid_sizes[2] * sub_sizes[1] + i);
                count_b[j * grid_sizes[2] + i] = 1;
            }
        MPI_Type_vector(sub_sizes[0], sub_sizes[2], sizes[2], MPI_DOUBLE, &types[0]);
        disp[1] = sizeof(double) * sub_sizes[2];
        MPI_Type_create_struct(2, blen, disp, types, &type_c);
        MPI_Type_commit(&type_c);
        disp_c = (int *)malloc(grid_sizes[0] * grid_sizes[2] * sizeof(int));
        count_c = (int *)malloc(grid_sizes[0] * grid_sizes[2] * sizeof(int));
        for (j = 0; j < grid_sizes[0]; j++)
            for (i = 0; i < grid_sizes[2]; i++) { 
                disp_c[j * grid_sizes[2] + i] = (j * grid_sizes[2] * sub_sizes[0] + i);
                count_c[j * grid_sizes[2] + i] = 1;
            }   
    } 
    if (coords[2] == 0)
    MPI_Scatterv(A, count_a, disp_a, type_a, A_sub_matrix, sub_sizes[0] * sub_sizes[1], MPI_DOUBLE, 0, comm_2D[2]);
    if (coords[0] == 0)
    MPI_Scatterv(B, count_b, disp_b, type_b, B_sub_matrix, sub_sizes[1] * sub_sizes[2], MPI_DOUBLE, 0, comm_2D[0]);
    MPI_Bcast(A_sub_matrix, sub_sizes[0] * sub_sizes[1], MPI_DOUBLE, 0, comm_1D[2]);
    MPI_Bcast(B_sub_matrix, sub_sizes[1] * sub_sizes[2], MPI_DOUBLE, 0, comm_1D[0]);
    for (i = 0; i < sub_sizes[0]; i++)
        for (k = 0; k < sub_sizes[1]; k++) { 
            C_sub_matrix[sub_sizes[2] * i + k] = 0;
            for (j = 0; j < sub_sizes[2]; j++)
                C_sub_matrix[sub_sizes[2] * i + j] += + A_sub_matrix[sub_sizes[1] * i + k] * B_sub_matrix[sub_sizes[2] * k + j];
        }
    C_reduced = (double *)malloc(sub_sizes[0] * sub_sizes[2] * sizeof(double));
    MPI_Reduce(C_sub_matrix, C_reduced, sub_sizes[0] * sub_sizes[2], MPI_DOUBLE, MPI_SUM, 0, comm_1D[1]);
    if (coords[1] == 0)
        MPI_Gatherv(C_reduced, sub_sizes[0] * sub_sizes[2], MPI_DOUBLE, C, count_c, disp_c, type_c, 0,
                                                                 comm_2D[1]);
    free(A_sub_matrix);
    free(B_sub_matrix);
    free(C_sub_matrix);
    free(C_reduced);
    MPI_Comm_free(&pcomm);
    MPI_Comm_free(&comm_3D);
    for (i = 0; i < 3; i++) { 
        MPI_Comm_free(&comm_2D[i]);
        MPI_Comm_free(&comm_1D[i]);
    }
    if (rank == 0) { 
        free(count_a);
        free(count_b);
        free(count_c);
        free(disp_a);
        free(disp_b);
        free(disp_c);
        MPI_Type_free(&type_a);
        MPI_Type_free(&type_b);
        MPI_Type_free(&type_c);
        MPI_Type_free(&types[0]);
    }
}
 
int main(int argc, char **argv) {
    double * A, * B, * C;
    int size, rank, sizes[3], grid_sizes[3], i, j, k;
    int reorder = 0;
    double time_one;
    MPI_Comm comm;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int dims[NUM_DIMS], periods[NUM_DIMS];
    for (i = 0; i < NUM_DIMS; i++) { 
        dims[i] = 0; 
        periods[i] = 0; 
    }
    MPI_Dims_create(size, NUM_DIMS, dims);
    MPI_Cart_create(MPI_COMM_WORLD, NUM_DIMS, dims, periods, reorder, &comm);
    grid_sizes[0] = atoi(argv[4]);
    grid_sizes[1] = grid_sizes[0];
    grid_sizes[2] = grid_sizes[0];
    if (grid_sizes[0] * grid_sizes[1] * grid_sizes[2] != size) {
        cerr << "Not a cube\n";
        return -1;
    }
    if(rank == 0) { 
        MPI_File f_A, f_B;
        MPI_File_open(MPI_COMM_SELF, argv[1], MPI_MODE_RDONLY, MPI_INFO_NULL, &f_A);
        MPI_File_open(MPI_COMM_SELF, argv[2], MPI_MODE_RDONLY, MPI_INFO_NULL, &f_B);
        MPI_File_read_shared(f_A, &sizes[0], 1, MPI_INT, NULL);
        MPI_File_read_shared(f_A, &sizes[1], 1, MPI_INT, NULL);
        int b_size;
        MPI_File_read_shared(f_B, &b_size, 1, MPI_INT, NULL);
        if (b_size != sizes[1]) {
            cerr << "Wrong sizes\n";
            return -1;        
        }
        MPI_File_read_shared(f_B, &sizes[2], 1, MPI_INT, NULL);
        A = (double *)malloc(sizes[0] * sizes[1] * sizeof(double));
        B = (double *)malloc(sizes[1] * sizes[2] * sizeof(double));
        C = (double *)malloc(sizes[0] * sizes[2] * sizeof(double));
        MPI_File_read_shared(f_A, A, sizes[0] * sizes[1], MPI_DOUBLE, NULL);
        MPI_File_read_shared(f_B, B, sizes[1] * sizes[2], MPI_DOUBLE, NULL);
        MPI_File_close(&f_A);
        MPI_File_close(&f_B);
    } 
    time_one = MPI_Wtime();
    PMATMAT_3(sizes, A, B, C, grid_sizes, comm);
    time_one = MPI_Wtime() - time_one;
    printf("%lf\n", time_one);
    if(rank == 0) { 
        MPI_File f_C;
        MPI_File_open(MPI_COMM_SELF, argv[3], MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &f_C);
        MPI_File_write_shared(f_C, &sizes[0], 1, MPI_INT, NULL);
        MPI_File_write_shared(f_C, &sizes[2], 1, MPI_INT, NULL);
        MPI_File_write_shared(f_C, C, sizes[0] * sizes[2], MPI_DOUBLE, NULL);
        MPI_File_close(&f_C);
    }
    if(rank == 0) { 
        free(A);
        free(B);
        free(C);
    }
    MPI_Comm_free(&comm);
    MPI_Finalize();
    return 0;
}

 