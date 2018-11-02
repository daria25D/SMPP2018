#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main(int argc, char ** argv) {
    fstream f;
    f.open(argv[1], ios::in);
    int num;
    while (!f.eof()) {
        f >> num;
        int n_sqrt = (int)floor(sqrt(num));
        if (num % 2 == 0 && num != 2) {
            cout << num << " not prime, error input, divided by 2" << endl;
            return -1;
        }
        for (int i = 3; i <= n_sqrt; i += 2) {
            if (num % i == 0) {
                cout << num << " not prime, error input, divided by " << i << endl;
                return -1;
            }
        }
    }
    cout << "Correct input" << endl;
    return 0;
}