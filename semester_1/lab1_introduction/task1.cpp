
#include <iostream>

int main() {
    double a, b, d;
    std::cout << "vvedite a,zatem b,zatem d: ";
    std::cin >> a >> b >> d;
   for (int k = a; k <= b; k = k+d) {
        if (k % 3 == 0)
           std::cout << k << " ";
    }
    return 0;
}

