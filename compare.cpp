//./compare A.dat B.dat
#include <iostream>
#include <fstream>

#define EPSILON 1.0e-10
using namespace std;

template<typename T> 
int compare(fstream & f1, fstream & f2, uint64_t n, uint64_t m) {
    //int equals = 1;
    T a, b;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) {
            f1.read((char *)&a, sizeof(T));
            f2.read((char *)&b, sizeof(T));
            if ((a - b) > EPSILON) {
                return 0;
            } 
        }
    return 1;    
}

int main(int argc, char ** argv) {
    if (argc != 3) {
        cerr << "Wrong number of arguments";
        return -1;
    }
    fstream a, b;
    try {
        a.open(argv[1], ios::binary | ios::in);
        b.open(argv[2], ios::binary | ios::in);
    } catch (exception & e) {
        cerr << e.what();
        return -1;
    }
    char type_a, type_b;
    uint64_t n_a, m_a, n_b, m_b;
    a.read((char *)&type_a, sizeof(type_a));
    b.read((char *)&type_b, sizeof(type_b));
    if (type_a != type_b) {
        cerr << "Different types" << endl;
        return -1;
    }
    if (type_a != 'f' && type_a != 'd') {
        cerr << "Invalid type";
        return -1;
    }
    a.read((char *)&n_a, sizeof(n_a));
    a.read((char *)&m_a, sizeof(m_a));
    b.read((char *)&n_b, sizeof(n_b));
    b.read((char *)&m_b, sizeof(m_b));
    if (n_a != n_b || m_a != m_b) {
        cout << "Different sizes" << endl;
        return 0;
    }
    if (type_a == 'f') {
        if (compare<float>(a, b, n_a, m_b) == 1) {
            cout << "Matrices are equal" << endl;
        } else cout << "Matrices are NOT equal" << endl;
    } else if (type_a == 'd') {
        if (compare<float>(a, b, n_a, m_b) == 1) {
           cout << "Matrices are equal" << endl;
        } else cout << "Matrices are NOT equal" << endl;
    }     
    return 0;
}
