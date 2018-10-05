//./multimatrix A.dat B.dat C.dat {0, ..., 5}
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstring>
//TODO: delete matrix 
using namespace std;

#define FOR(var1, var2, var3, n, m, l) \
    for (var1 = 0; var1 < (n); var1++) \
        for (var2 = 0; var2 < (m); var2++) \
            for (var3 = 0; var3 < (l); var3++)

#define ADD(var1, var2, var3) \
        var1 += var2 * var3; 

template <typename T>
void read_matrix(T ** f, uint64_t n, uint64_t m, fstream & s) {
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            s.read((char *)&(f[i][j]), sizeof(T));    
}
template <typename T>
void write_matrix(T ** f, uint64_t n, uint64_t m, fstream & s) {
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            s.write((char *)&(f[i][j]), sizeof(T));   
}

template <typename T, typename U, typename V>
uint64_t multiply(char type, uint64_t N, uint64_t M, uint64_t L, 
            T ** A, U ** B, V ** C, char * order, fstream &f) {
    uint64_t i, j, k;
    uint64_t time_mul;
    if (strcmp(order, "0") == 0) { time_mul = clock();
        FOR(i, j, k, N, M, L) { ADD(C[i][j], A[i][k], B[k][j]);} //0 - ijk
        time_mul = clock() - time_mul;}
    else if (strcmp(order, "1") == 0) { time_mul = clock();
        FOR(i, k, j, N, L, M) { ADD(C[i][j], A[i][k], B[k][j]);} //1 - ikj
        time_mul = clock() - time_mul;} 
    else if (strcmp(order, "2") == 0) { time_mul = clock();
        FOR(k, i, j, L, N, M) { ADD(C[i][j], A[i][k], B[k][j]);} //2 - kij
        time_mul = clock() - time_mul;}
    else if (strcmp(order, "3") == 0) { time_mul = clock();
        FOR(j, i, k, M, N, L) { ADD(C[i][j], A[i][k], B[k][j]);} //3 - jik
        time_mul = clock() - time_mul;}
    else if (strcmp(order, "4") == 0) { time_mul = clock();
        FOR(j, k, i, M, L, N) { ADD(C[i][j], A[i][k], B[k][j]);} //4 - jki
        time_mul = clock() - time_mul;}
    else if (strcmp(order, "5") == 0) { time_mul = clock();
        FOR(k, j, i, L, M, N) { ADD(C[i][j], A[i][k], B[k][j]);} //5 - kji
        time_mul = clock() - time_mul;}
    else {
        throw "Invalid order";
    }
    f.write((char *)&type, sizeof(char));
    f.write((char *)&N, sizeof(uint64_t));
    f.write((char *)&M, sizeof(uint64_t));
    write_matrix(C, N, M, f);
    return time_mul;
}
template <typename T>
T ** get_matrix(uint64_t n, uint64_t m) {
    T ** t = new T *[n];
    for (int i = 0; i < n; i++) {
        t[i] = new T [m];
    }
    return t;
}
template <typename T> 
void delete_matrix(T ** M, uint64_t rows) {
    for (int i = 0; i < rows; i++) {
        delete[] M[i];
    }
    delete[] M;
}
double get_time(char * a, char * b, char * c, char * order) {
    fstream a_f, b_f;
    a_f.open(a, ios::binary | ios::in);
    b_f.open(b, ios::binary | ios::in);
    char T_a, T_b;
    a_f.read((char *)&T_a, sizeof(T_a));
    b_f.read((char *)&T_b, sizeof(T_b));
    uint64_t N_a, M_a, N_b, M_b;
    a_f.read((char *)&N_a, sizeof(N_a));
    a_f.read((char *)&M_a, sizeof(M_a));
    b_f.read((char *)&N_b, sizeof(N_b));
    b_f.read((char *)&M_b, sizeof(M_b));
    fstream c_f(c, ios::binary | ios::out);
    if ((T_a != 'f' && T_a != 'd') || (T_b != 'f' && T_b != 'd'))  return -1;
    if (N_b != M_a) return -1;
    uint64_t time_mul;
    if (T_a == 'f') {
        float ** A = get_matrix<float>(N_a, M_a);
        read_matrix<float>(A, N_a, M_a, a_f); 
        if (T_b == 'f') {
            float ** B = get_matrix<float>(N_b, M_b);
            read_matrix<float>(B, N_b, M_b, b_f);
            float ** C = get_matrix<float>(N_a, M_b);
            time_mul = multiply('f', N_a, M_b, N_b, A, B, C, order, c_f);
            delete_matrix<float>(B, N_b);
            delete_matrix<float>(C, N_a);
        } else {
            double ** B = get_matrix<double>(N_b, M_b);
            read_matrix<double>(B, N_a, M_a, b_f);
            double ** C = get_matrix<double>(N_a, M_b);
            time_mul = multiply('d', N_a, M_b, N_b, A, B, C, order, c_f);
            delete_matrix<double>(B, N_b);
            delete_matrix<double>(C, N_a);
        }
        delete_matrix<float>(A, N_a);
    } else {
        double ** A = get_matrix<double>(N_a, M_a);
        read_matrix<double>(A, N_a, M_a, a_f); 
        if (T_b == 'f') {
            float ** B = get_matrix<float>(N_b, M_b);
            read_matrix<float>(B, N_b, M_b, b_f);
            double ** C = get_matrix<double>(N_a, M_b);
            time_mul = multiply('d', N_a, M_b, N_b, A, B, C, order, c_f);
            delete_matrix<float>(B, N_b);
            delete_matrix<double>(C, N_a);
        } else {
            double ** B = get_matrix<double>(N_b, M_b);
            read_matrix<double>(B, N_a, M_a, b_f);
            double ** C = get_matrix<double>(N_a, M_b);
            time_mul = multiply('d', N_a, M_b, N_b, A, B, C, order, c_f);
            delete_matrix<double>(B, N_b);
            delete_matrix<double>(C, N_a);
        }
        delete_matrix<double>(A, N_a);
    }    
    return time_mul/(double)CLOCKS_PER_SEC ;
}

int main(int argc, char **argv) {
    //./multimatrix A.dat B.dat C.dat {0, ..., 5}
    if (argc != 5) {
        cerr << "Wrong number of arguments";
        return -1;
    }
    double time_mul;
    try{
        time_mul = get_time(argv[1], argv[2], argv[3], argv[4]);
        if (time_mul == -1) throw "Invalid data caused an error.";
    } catch (const char * s) {
        cerr << s;
        return -1;
    } catch (exception &e) {
        cerr << e.what();
    } catch (...) {
        cerr << "An error occured";
        return -1;
    }
    cout << setprecision(8) << fixed << time_mul<< " ";
    return 0;
}