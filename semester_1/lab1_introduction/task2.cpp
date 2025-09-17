#include <iostream>

int main() {
    double b;
    double d = 0, e = 1;
    std::cout << "vvedite b: ";
    std::cin >> b ;
    for (int k = 1; k <= b; k++ ) {
        if (k % 2 == 0) {
            d = d + k;
        }
        else{
            e = e * k;
        }
    }
    std::cout << "summa:" << d << endl;
    std::cout << "proizvedenie:"<< e ;
    return 0;
}
