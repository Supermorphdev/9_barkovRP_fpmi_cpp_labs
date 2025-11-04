#include <iostream>
#include <limits>
#include <cmath>
#include <random>

const int MAX_SIZE = 100000;

template<typename T>
void Read(T& number) {
    while (true) {
        if (!(std::cin >> number)) {
            std::cout << "Fail on reading the number. Try again: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
}

static void CheckSize(const int n) {
    if (n > MAX_SIZE || n <= 0) {
        std::cout << "Array size is invalid. Try again next time";
        exit(1);
    }
}

static void FillMassiveManual(double* massive, const int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << "Enter element " << i + 1 << ": ";
        Read(massive[i]);
    }
}

static void CheckRandomBounds(double& a, double& b) {
    std::cout << "Enter interval boundaries [a, b]: ";
    Read(a);
    Read(b);
    if (a > b) {
        std::swap(a, b);
    }
}

void fillArrayRandom(double* matrix, const int n, const double a, const double b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(a, b);

    for (int i = 0; i < n; i++) {
        matrix[i] = dist(gen);
    }
}

int option_receive() {
    std::cout << "\nChoose option of filling array: manual(1), randomfill(2): ";
    int option;
    while (true) {
        if (!(std::cin >> option) || (option != 1 && option != 2)) {
            std::cout << "There is no such option. Try again\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    return option;
}

void array_print(const double* massive, const int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << massive[i] << " ";
    }
    std::cout << std::endl;
}

int countDistinctElements(const double* massive, const int n) {
    int distinctCount = 0;

    for (int i = 0; i < n; ++i) {
        bool isUnique = true;

        for (int j = 0; j < i; ++j) {
            if (std::fabs(massive[i] - massive[j]) < 1e-9) {
                isUnique = false;
                break;
            }
        }

        if (isUnique) {
            distinctCount++;
        }
    }

    return distinctCount;
}

double productBeforeMinAbsolute(const double* massive, const int n) {
    if (n <= 0) return 1.0;

    int minIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (std::fabs(massive[i]) < std::fabs(massive[minIndex])) {
            minIndex = i;
        }
    }

    if (minIndex == 0) {
        return 1.0;
    }

    double product = 1.0;
    for (int i = 0; i < minIndex; ++i) {
        product *= massive[i];
    }

    return product;
}

void rearrangeArray(double* massive, const int n) {
    int insertPos = 0;

    for (int i = 0; i < n; ++i) {
        if (massive[i] < 0) {
            double temp = massive[i];
            for (int j = i; j > insertPos; --j) {
                massive[j] = massive[j - 1];
            }
            massive[insertPos] = temp;
            insertPos++;
        }
    }

    for (int i = insertPos; i < n; ++i) {
        if (std::fabs(massive[i]) < 1e-9) {
            double temp = massive[i];
            for (int j = i; j > insertPos; --j) {
                massive[j] = massive[j - 1];
            }
            massive[insertPos] = temp;
            insertPos++;
        }
    }
}

int main() {
    int n;
    std::cout << "Enter array size: ";
    Read(n);
    CheckSize(n);

    double* massive = new double[n];

    int option = option_receive();
    if (option == 1) {
        FillMassiveManual(massive, n);
    }
    else {
        double a, b;
        CheckRandomBounds(a, b);
        fillArrayRandom(massive, n, a, b);
    }

    std::cout << "Original array: ";
    array_print(massive, n);

    int distinctCount = countDistinctElements(massive, n);
    std::cout << "Number of distinct elements: " << distinctCount << std::endl;

    double product = productBeforeMinAbsolute(massive, n);
    std::cout << "Product of elements before minimum absolute: " << product << std::endl;

    rearrangeArray(massive, n);
    std::cout << "Rearranged array (negative, zero, positive): ";
    array_print(massive, n);

    delete[] massive;

    return 0;
}
