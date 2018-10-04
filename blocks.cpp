#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
using namespace std;

float ** init_matrix(uint64_t n, uint64_t m) {
	float ** M = new float *[n];
	for (uint64_t i = 0; i < n; i++)
		M[i] = new float[m];
	return M;	
}

void delete_matrix(float ** M, uint64_t rows) {
    for (uint64_t i = 0; i < rows; i++) {
        delete[] M[i];
    }
    delete[] M;
}

void read_matrix(float ** M, uint64_t n, uint64_t m, fstream & s) {
    for (uint64_t i = 0; i < n; i++) 
        for (uint64_t j = 0; j < m; j++) 
            s.read((char *)&(M[i][j]), sizeof(float));    
}

void write_matrix(float ** M, uint64_t n, uint64_t m, fstream & s) {
    for (uint64_t i = 0; i < n; i++) 
        for (uint64_t j = 0; j < m; j++) 
            s.write((char *)&(M[i][j]), sizeof(float));   
}

uint64_t multiply(float ** A, float ** B, float ** C, uint64_t n, uint64_t m, 
                    uint64_t l, uint64_t size_of_block, fstream & f) {
	uint64_t time_mul = clock();
	for (uint64_t i = 0; i < n; i += size_of_block) 
		for (uint64_t j = 0; j < m; j += size_of_block) 
			for (uint64_t k = 0; k < l; k += size_of_block)
				for (uint64_t i1 = 0; i1 < i + size_of_block; i1++)
					for (uint64_t j1 = 0; j1 < j + size_of_block; j1++)
						for (uint64_t k1 = 0; k1 < k + size_of_block; k1++)
							C[i1][j1] += A[i1][k1] * B[k1][j1];
	return time_mul - clock();						
}

double get_time(char * a, char * b, char * c, uint64_t size_of_block) {
	fstream a_f, b_f;
    a_f.open(a, ios::binary | ios::in);
    b_f.open(b, ios::binary | ios::in);
    uint64_t N_a, M_a, N_b, M_b;
    a_f.read((char *)&N_a, sizeof(N_a));
    a_f.read((char *)&M_a, sizeof(M_a));
    b_f.read((char *)&N_b, sizeof(N_b));
    b_f.read((char *)&M_b, sizeof(M_b));
    fstream c_f(c, ios::binary | ios::out);
	if (N_b != M_a) return -1; // throw error
	float ** A = init_matrix(N_a, M_a);
    read_matrix(A, N_a, M_a, a_f); 
	float ** B = init_matrix(N_b, M_b);
	read_matrix(B, N_b, M_b, b_f);
	float ** C = init_matrix(N_a, M_b); 
	uint64_t time_mul; 
	time_mul = multiply(A, B, C, N_a, M_b, N_b, size_of_block, c_f);
	delete_matrix(A, N_a);
	delete_matrix(B, N_b);
	delete_matrix(C, N_a);
	return time_mul/(double)CLOCKS_PER_SEC;
}

// ./multiply A.dat B.dat C.dat size_of_block
int main(int argc, char ** argv) {
	if (argc != 5) {
        cerr << "Wrong number of arguments";
        return -1;
    }
	uint64_t size_of_block;
	sscanf(argv[4], "%ull", &size_of_block); // change format
    double time_mul;
    try{
        time_mul = get_time(argv[1], argv[2], argv[3], size_of_block);
        if (time_mul == -1) throw "Invalid data caused an error";
    } catch (const char * s) {
        cerr << s;
        return -1;
    } catch (exception &e) {
        cerr << e.what();
    } catch (...) {
        cerr << "An error occured";
        return -1;
    }	
	cout << time_mul << endl;
	return 0;
}

