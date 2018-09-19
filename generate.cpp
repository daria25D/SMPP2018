//./generate type rows columns file
#include <iostream>
#include <fstream>
#include <limits>
#include <random>

using namespace std;

template <typename T>
T new_random(T dMin, T dMax)
{
    return dMin + (dMax - dMin) * (T(random())/ (T)RAND_MAX);
}

template<typename T>
void generate_E(uint64_t n, uint64_t m, fstream & f, T const val) {
    T zero = 0.0;
    for (uint64_t i = 0; i < n; i++) 
        for (uint64_t j = 0; j < m; j++) 
            if (i == j) f.write((char *)&val, sizeof(T));
            else f.write((char *)&zero, sizeof(T));
}

int main(int argc, char **argv) {
    //./generate type rows columns file
    if (argc < 5 || argc > 6) {
        cerr << "Wrong number of arguments";
        return -1;
    }
    srand(time(NULL));
    char type;
    sscanf(argv[1], "%c", &type);
    if (type != 'f' && type != 'd') {
        cerr << "Invalid type";
        return -1;
    }
    uint64_t n, m;
    try {
        n = strtoull(argv[2], NULL, 0);
        m = strtoull(argv[3], NULL, 0);
    } catch (exception & e) {
        cerr << e.what();
        return -1;
    }
    fstream file(argv[4], ios::binary | ios::out);
    if (!file.is_open()) {
        cerr << "Cannot open file";
        return -1;
    }
    file.write((char *)&type, sizeof(type));
    file.write((char *)&n, sizeof(n));
    file.write((char *)&m, sizeof(m));
    try {
        if (argc == 6) { //for prinring matrix E
            if (type == 'f') generate_E(n, m, file, (float)1.0);
            else generate_E(n, m, file, (double)1.0);
        } else {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++) 
                    if (type == 'f') {
                        float fr = new_random<float>(-INT16_MAX + 1, INT16_MAX);
                        file.write((char *)&fr, sizeof(float));
                    } else {
                        double dr = new_random<double>(-INT16_MAX + 1, INT16_MAX);
                        file.write((char *)&dr, sizeof(double));
                    }
        }
    } catch (exception & e) {
        cerr << e.what();
        return -1;
    } 
    return 0;
}   