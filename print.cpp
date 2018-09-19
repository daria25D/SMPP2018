#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char ** argv) {
    //./print what > where
    if (argc != 2) {
        cerr << "Wrong number of arguments";
        return -1;
    }
    fstream file(argv[1], ios::binary | ios::in);
    char type;
    uint64_t n, m;
    file.read((char *)&type, sizeof(type));
    file.read((char *)&n, sizeof(n));
    file.read((char *)&m, sizeof(m));
    cout << type << endl << setw(5) << n << setw(5) << m << endl;
    if (type == 'f') {
        float f;
        for (uint64_t i = 0; i < n; i++) {
            for (uint64_t j = 0; j < m; j++) {
                file.read((char *)&f, sizeof(f));
                cout << fixed << setw(15) << setprecision(3) << f;
            }
            cout << endl;
        }
    } else if (type == 'd') {
        double d;
        for (uint64_t i = 0; i < n; i++) {
            for (uint64_t j = 0; j < m; j++) {
                file.read((char *)&d, sizeof(d));
                cout << fixed << setw(15) << setprecision(3) << d;
            }
            cout << endl;
        }
    } else if (file.peek() == EOF) {
        return 0;
    } else {
        cerr << "Invalid type";
        return -1;
    }
    return 0;
}