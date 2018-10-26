//g++ -I/usr/local/include -O0 blocks.cpp /usr/local/lib/libpapi.a -o blocks
// ./blocks A.dat B.dat C.dat {0, 1} size_of_block [...parameters...]
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <inttypes.h>
#include <papi.h>
#include <vector>
#include <cmath>

#define NUMBER_OF_COUNTERS 7
#define NUMBER_OF_ARGC 6

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
uint64_t multiply_ijk(float ** A, float ** B, float ** C, uint64_t n, uint64_t m, 
                    uint64_t l, uint64_t size_of_block, fstream & f) {
    uint64_t time_mul = clock();
    for (uint64_t i = 0; i < n; i += size_of_block) 
	for (uint64_t j = 0; j < m; j += size_of_block) 
	    for (uint64_t k = 0; k < l; k += size_of_block)
		for (uint64_t i1 = i; i1 < i + size_of_block && i1 < n; i1++)
                    for (uint64_t j1 = j; j1 < j + size_of_block && j1 < m; j1++)
			for (uint64_t k1 = k; k1 < k + size_of_block && k1 < l; k1++)
			    C[i1][j1] += A[i1][k1] * B[k1][j1];
    return clock() - time_mul;						
}
uint64_t multiply_ikj(float ** A, float ** B, float ** C, uint64_t n, uint64_t m, 
                    uint64_t l, uint64_t size_of_block, fstream & f) {
    uint64_t time_mul = clock();
    for (uint64_t i = 0; i < n; i += size_of_block) 
        for (uint64_t k = 0; k < l; k += size_of_block) 
	    for (uint64_t j = 0; j < m; j += size_of_block)
		for (uint64_t i1 = i; i1 < i + size_of_block && i1 < n; i1++)
	            for (uint64_t k1 = k; k1 < k + size_of_block && k1 < l; k1++)
			for (uint64_t j1 = j; j1 < j + size_of_block && j1 < m; j1++)
			    C[i1][j1] += A[i1][k1] * B[k1][j1];
    return clock() - time_mul;						
}
double get_time(char * a, char * b, char * c, char mode, uint64_t size_of_block) {
    fstream a_f, b_f;
    a_f.open(a, ios::binary | ios::in);
    b_f.open(b, ios::binary | ios::in);
    uint64_t N_a, M_a, N_b, M_b;
    a_f.read((char *)&N_a, sizeof(N_a));
    a_f.read((char *)&M_a, sizeof(M_a));
    b_f.read((char *)&N_b, sizeof(N_b));
    b_f.read((char *)&M_b, sizeof(M_b));
    fstream c_f(c, ios::binary | ios::out);
    if (N_b != M_a) throw "Invalid sizes";
    float ** A = init_matrix(N_a, M_a);
    read_matrix(A, N_a, M_a, a_f); 
    float ** B = init_matrix(N_b, M_b);
    read_matrix(B, N_b, M_b, b_f);
    float ** C = init_matrix(N_a, M_b); 
    uint64_t time_mul; 
    if (mode == 0) 
	time_mul = multiply_ijk(A, B, C, N_a, M_b, N_b, size_of_block, c_f);
    else  
	time_mul = multiply_ikj(A, B, C, N_a, M_b, N_b, size_of_block, c_f);
    delete_matrix(A, N_a);
    delete_matrix(B, N_b);
    delete_matrix(C, N_a);
    return time_mul/(double)CLOCKS_PER_SEC;
}
void handle_error(int err){
    std::cerr << "PAPI error: " << err << std::endl;
}

// ./blocks A.dat B.dat C.dat {0 - ijk, 1 - ikj} size_of_block params
//NO FLOPS COUNTER
int main(int argc, char ** argv) {
    if (argc == 2) {
        if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) {
            cout << "help information: " << endl;
            cout << "Modes:\n1 - PAPI_L1_TCM\n2 - PAPI_L2_TCM\n3 - PAPI_L3_TCM\n";
            cout << "4 - PAPI_TOT_INS\n5 - PAPI_TLB_IM\n6 - PAPI_TOT_CYC\n7 - PAPI_TLB_DM\n";
            return 0;
        } else {
            cerr << "Invalid command line" << endl;
            return -1;
        }
    }
	if (argc < NUMBER_OF_ARGC) {
        cerr << "Wrong number of arguments" << endl;
        return -1;
    }
    int mode;
    uint64_t size_of_block;
    sscanf(argv[4], "%d", &mode);
    sscanf(argv[5], "%", SCNd64, &size_of_block); 
    //if ((mode != 0 && mode != 1) || (strcmp(argv[4], "0") !=0 && strcmp(argv[4], "1") != 0) || size_of_block < 1) {
      //  cerr << "Invalid parameters" << endl;
        //return -1;
    //}
    double time_mul;
    int NUMBER_OF_EVENTS, retval;
    long long * values;
    int COUNTERS[NUMBER_OF_COUNTERS];
    int * events;
    vector<string> NAMES;
    if (argc - NUMBER_OF_ARGC >= 0 || size_of_block == 0 || strcmp(argv[5], "0") == 0) { //there are counters to compute
        if ((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT) {
            handle_error(retval);
        }
        const PAPI_hw_info_t * info = PAPI_get_hardware_info();
        if (info == NULL) {
            handle_error(1);
        }
        if (size_of_block == 0 || strcmp(argv[5], "0") == 0) {
            size_of_block = info->mem_hierarchy.level[0].cache[0].size;
            //cout << "Cache L1 size is: " << size_of_block << endl;
            size_of_block = (int)floor(sqrt(size_of_block / (sizeof(float)*3)));
            //cout << "Size of block is: " << size_of_block << endl;
        } else {
            size_of_block = 32;
        }
        NUMBER_OF_EVENTS = (argc - NUMBER_OF_ARGC)/2;
        values = new long long[NUMBER_OF_EVENTS];
        memset(COUNTERS, 0, sizeof(int) * NUMBER_OF_COUNTERS);
        events = new int[NUMBER_OF_EVENTS];
        for (int i = NUMBER_OF_ARGC; i < argc - NUMBER_OF_EVENTS; i++) {
            int counter;
            sscanf(argv[i], "%d", &counter);
            bool flag = false;
            switch (counter) {
                case 1:
                    if (COUNTERS[0] == 0) {
                        events[i - NUMBER_OF_ARGC] = PAPI_L1_TCM;
                        NAMES.push_back("Level 1 cache misses");
                        COUNTERS[0]++;
                    } else flag = true;
                    break;
                case 2:
                    if (COUNTERS[1] == 0) {
                        events[i - NUMBER_OF_ARGC] = PAPI_L2_TCM;
                        NAMES.push_back("Level 2 cache misses");
                        COUNTERS[1]++;
                    } else flag = true;
                    break;
                case 3:
                    if (COUNTERS[2] == 0) {
                        events[i - NUMBER_OF_ARGC] = PAPI_L3_TCM;
                        NAMES.push_back("Level 3 cache misses");
                        COUNTERS[2]++;
                    } else flag = true;
                    break;
                case 4:
                    if (COUNTERS[3] == 0) { 
                        events[i - NUMBER_OF_ARGC] = PAPI_TOT_INS;
                        NAMES.push_back("Instructions completed");
                        COUNTERS[3]++;
                    } else flag = true;
                    break;
                case 5:
                    if (COUNTERS[4] == 0) {
                        events[i - NUMBER_OF_ARGC] = PAPI_TLB_IM;
                        NAMES.push_back("Instruction translation lookaside buffer misses");
                        COUNTERS[4]++;
                    } else flag = true;
                    break;
                case 6:
                    if (COUNTERS[5] == 0) {
                        events[i - NUMBER_OF_ARGC] = PAPI_TOT_CYC;
                        NAMES.push_back("Total cycles");
                        COUNTERS[5]++;
                    } else flag = true;
                    break;
                case 7:
                    if (COUNTERS[6] == 0) {
                        events[i - NUMBER_OF_ARGC] = PAPI_TLB_DM;
                        NAMES.push_back("Data translation lookaside buffer misses");
                        COUNTERS[6]++;
                    } else flag = true;
                    break;
                default :
                    cerr << "Invalid counter" << endl;
                    return -1;
            }
            if (flag) {
                cerr << "Invalid counters list" << endl;
                    return -1;
            }
        }
        if ((retval = PAPI_start_counters(events, NUMBER_OF_EVENTS)) != PAPI_OK)
            handle_error(retval);
    }
    try{
        time_mul = get_time(argv[1], argv[2], argv[3], mode, size_of_block);
        if (time_mul == -1) throw "Invalid data caused an error";
    } catch (const char * s) {
        cerr << s << endl;
        return -1;
    } catch (exception &e) {
        cerr << e.what();
    } catch (...) {
        cerr << "An error occured" << endl;
        return -1;
    }	
    if (argc - NUMBER_OF_ARGC >= 0 || strcmp(argv[5], "0") == 0) {
        if ((retval = PAPI_stop_counters(values, NUMBER_OF_EVENTS))!= PAPI_OK)
            handle_error(retval);
        for (int i = 0; i < NUMBER_OF_EVENTS; i++) {
            fstream f;
            f.open(argv[i + NUMBER_OF_ARGC + NUMBER_OF_EVENTS], ios::out | ios::app);
            f << NAMES[i] << ": " << values[i] << endl;
        }
        delete []values;
        delete []events;
    }
	cout << "Time: " << time_mul << endl;
	return 0;
}
