//g++ -g pthread_eratoshenes.cpp -o pthread_eratoshenes -lpthread
#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <cmath>
#include <time.h>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <unistd.h>

using namespace std;

volatile int running_threads = 0;
pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int * PRIMES;
    int count;
    int A;
    int B;
    int N;
    int part;
    int id;
    FILE * file_primes;
    FILE * file_time;
} Args;

void * Eratosthenes_Sieve(void * args) {
    struct timespec start, finish;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    Args * data = (Args *)args;
    bool * NUMBERS = new bool[data->part];
    memset(NUMBERS, true, sizeof(bool) * data->part);
    for (int i = 0; i < data->part && data->N + i + data->part * data->id <= data->B; i++) {
        for (int j = 0; j < data->count; j++) {
            int k = data->N + i + data->part * data->id;
            if (k % data->PRIMES[j] == 0) {
                NUMBERS[i] = false;
                break;
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec)/1000000000.0;
    fprintf(data->file_time, "%lf\n", elapsed);
    //cout << elapsed << " " << data->id << endl;
    if (data->id == 0) {
        for (int i = 0; i < data->count; i++) {
            if (data->PRIMES[i] >= data->A)
                fprintf(data->file_primes, "%d ", data->PRIMES[i]);
        }
    }
    for (int i = 0; i < data->part && data->N + i + data->part * data->id <= data->B; i++) {
        if (NUMBERS[i]) {
            fprintf(data->file_primes, "%d ", data->N + i + data->part * data->id);
        }
    }
    delete[] NUMBERS;
    pthread_mutex_lock(&running_mutex);
    running_threads--;
    pthread_mutex_unlock(&running_mutex);
    pthread_exit(NULL);
    return NULL;
}

void Max_time(char * filename, int n_of_threads, char * fout) {
    double max_time = 0, cur_time;
    int max_id = 1, cur_id = 1;;
    double all_time = 0;
    FILE * f;
    f = fopen(filename, "r");
    while (cur_id <= n_of_threads) {
        fscanf(f, "%lf", &cur_time);
        if (cur_time > max_time) {
            max_time = cur_time;
            max_id = cur_id;
        }
        cur_id++;
        all_time += cur_time;
    }
    FILE * out = fopen(fout, "w");
    fprintf(out, "Max time of thread is: %.9lf\n",  max_time);
    fprintf(out, "Thread id: %d\n", max_id);
    fprintf(out, "Complete time of all threads: %.9lf\n", all_time);
    fclose(out);
    fclose(f);
}


int main(int argc, char ** argv) {
    if (argc != 7) {
        cerr << "Wrong number of arguments" << endl;
        return -1;
    }
    int n = atoi(argv[1]);
    int N_SQRT = floor(sqrt(atoi(argv[3])));
    pthread_t * threads = new pthread_t[n];
    FILE * file_primes = fopen(argv[4], "w");
    FILE * file_time = fopen(argv[5], "w");
    Args * thread_args = new Args[n];
    for (int i = 0; i < n; i++) {
        thread_args[i].A = atoi(argv[2]);
        thread_args[i].B = atoi(argv[3]);
        thread_args[i].file_primes = file_primes;  
        thread_args[i].file_time = file_time;
        thread_args[i].N = max(N_SQRT + 1, thread_args[i].A);  
        thread_args[i].part = (thread_args[i].B - thread_args[i].N + 1)/n + 1;
        thread_args[i].id = i;
    }
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
    thread_args[0].PRIMES = new int[count];
    thread_args[0].count = count;
    j = 0;
    for (i = 2; i <= N_SQRT; i++) {
        if (primes_bool[i]) {
            thread_args[0].PRIMES[j] = i;
            j++;
        } 
    }
    for (i = 1; i < n; i++) {
        thread_args[i].PRIMES = new int[count];
        thread_args[i].count = count;
        for (j = 0; j < count; j++) {
            thread_args[i].PRIMES[j] = thread_args[0].PRIMES[j];
        }
    }
    delete[] primes_bool;
    clock_t t = clock();
    for (i = 0; i < n; i++){
        pthread_mutex_lock(&running_mutex);
        running_threads++;
        pthread_mutex_unlock(&running_mutex);
        int rc = pthread_create(&threads[i], NULL, 
                    Eratosthenes_Sieve, (void *)&thread_args[i]);
        if (rc) {
            cerr << "Error: unable to create thread, " << rc << endl;
            return -1;
        }
    }
    // for (i = 0; i < n; i++) {
    //     pthread_join(threads[i], NULL);
    // }
    //sleep(2);
    while (running_threads > 0) {
        //sleep(1);
    }
    //cout << "Time: " << (clock() - t)/(CLOCKS_PER_SEC + 0.0) << endl;
    fclose(file_primes);
    fclose(file_time);
    for (i = 0; i < n; i++) {
        delete[] thread_args[i].PRIMES;
    }
    delete[] thread_args;
    Max_time(argv[5], n, argv[6]);
    pthread_exit(NULL);
}

