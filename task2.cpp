#include <iostream>
using namespace std;

int main() {
    double b;
    double d = 0, e = 1;
    cout << "vvedite b: ";
    cin >> b ;
    for (int k = 1; k <= b; k++ ) {
        if (k % 2 == 0) {
            d = d + k;
        }
        else{
            e = e * k;
        }
    }
    cout << "summa:" << d << endl;
    cout << "proizvedenie:"<< e ;
    return 0;
}
