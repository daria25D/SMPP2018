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
    int n, m;
    file.read((char *)&n, sizeof(n));
    file.read((char *)&m, sizeof(m));
    cout << setw(5) << n << setw(5) << m << endl;
    double f;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            file.read((char *)&f, sizeof(f));
            cout << fixed << setw(15) << setprecision(3) << f;
        }
        cout << endl;
    }
    return 0;
}