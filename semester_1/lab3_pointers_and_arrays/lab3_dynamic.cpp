#include <iostream>
#include <limits>
#include <cmath>
void TryRead(int& number) {
    while (true) {
        if (!(std::cin >> number)) {
            std::cout << "Fail on reading the number. Try again: ";
            std::cin.clear(); // Сброс флагов ошибок
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
        }
        else {
            break; // Успешный ввод
        }
    }
}



int main() {
    int n;
    std::cout << "enter amount of array: ";
    std::cin >> n;

    double* massive = new double[n];

    std::cout << "enter elements:\n";
    for (int i = 0; i < n; i++) {
        std::cin >> massive[i];
    }

    int MinIndex = 0;
    for (int i = 1; i < n; i++) {
        if (massive[i] <= massive[MinIndex]) {
            MinIndex = i;
        }
    }
    std::cout << "number of min elemet: " << MinIndex + 1 << std::endl;
    ////////////////////////////////////////////////////////
    int FirstNeg, LastNeg = -1;
    for (int i = 0; i < n; i++) {
        if (massive[i] < 0) {
            FirstNeg = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        if (massive[i] < 0) {
            LastNeg = i;
            break;
        }
    }

    double sum = 0;
    if (FirstNeg != -1 && LastNeg != -1 && FirstNeg < LastNeg) {
        for (int i = FirstNeg + 1; i < LastNeg; i++) {
            sum += massive[i];
        }
        std::cout << "Sum of elements between first and last negative elements of array: " << sum << std::endl;
    }
    else {
        std::cout << "There are no elements between first and last neg or there is no neg";
    }
    ////////////////////////////////////////////////////////
    double x;
    std::cout << "enter x: ";
    std::cin >> x;

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (std::abs(massive[i]) <= x) {
            count++;
        }
    }
    int i = 0, j = count;
    while (i < count && j < n) {
        if (std::abs(massive[i]) > x && std::abs(massive[i]) <= x) {
            std::swap(massive[i], massive[j]);
            j++;
            i++;
        }
        else if (std::abs(massive[i]) <= x) {
            i++;
        }
        else {
            j++;
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << massive[i] << " ";
    }
    delete[] massive;
    return 0;
}
