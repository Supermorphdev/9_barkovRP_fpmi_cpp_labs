#include <iostream>
#include <random>
#include <limits>
#include <iomanip>

bool inputValid() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

void inputMatrixDimensions(int& rows, int& cols) {
    std::cout << "Enter number of rows and columns: ";
    if (!(std::cin >> rows >> cols) || rows <= 0 || cols <= 0) {
        std::cout << "Input error! Dimensions must be positive numbers. Program terminated.\n";
        exit(1);
    }
}

int** allocateMatrix(int rows, int cols) {
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int selectInputMethod() {
    int choice;
    std::cout << "Choose input method:\n1 - Manual\n2 - Random\n";
    if (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cout << "Input error! Invalid choice. Program terminated.\n";
        exit(1);
    }
    return choice;
}

void inputMatrixManually(int** matrix, int rows, int cols) {
    std::cout << "Enter matrix elements:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(std::cin >> matrix[i][j])) {
                std::cout << "Input error! Program terminated.\n";
                exit(1);
            }
        }
    }
}

void inputRandomBounds(int& a, int& b) {
    std::cout << "Enter interval boundaries [a, b]: ";
    if (!(std::cin >> a >> b) || a > b) {
        std::cout << "Input error! Invalid interval boundaries. Program terminated.\n";
        exit(1);
    }
}

void fillMatrixRandom(int** matrix, int rows, int cols, int a, int b) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(a, b);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = dist(gen);
        }
    }
}

void fillMatrix(int** matrix, int rows, int cols) {
    int method = selectInputMethod();

    if (method == 1) {
        inputMatrixManually(matrix, rows, cols);
    }
    else {
        int a, b;
        inputRandomBounds(a, b);
        fillMatrixRandom(matrix, rows, cols, a, b); 
    }
}

void printMatrix(int** matrix, int rows, int cols) {
    int maxWidth = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int num = matrix[i][j];
            int width = 1;
            if (num < 0) {
                width++;
                num = -num;
            }
            while (num >= 10) {
                width++;
                num /= 10;
            }
            if (width > maxWidth) {
                maxWidth = width;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(maxWidth) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int sumColumnsWithZero(int** matrix, int rows, int cols) {
    int totalSum = 0;
    for (int j = 0; j < cols; j++) {
        bool hasZero = false;
        for (int i = 0; i < rows; i++) {
            if (matrix[i][j] == 0) {
                hasZero = true;
                break;
            }
        }
        if (hasZero) {
            for (int i = 0; i < rows; i++) {
                totalSum += matrix[i][j];
            }
        }
    }
    return totalSum;
}

void sortEvenRowAscending(int* row, int cols) {
    for (int k = 0; k < cols - 1; k++) {
        for (int l = 0; l < cols - k - 1; l++) {
            if (row[l] > row[l + 1]) {
                std::swap(row[l], row[l + 1]);
            }
        }
    }
}

void sortOddRowDescending(int* row, int cols) {
    for (int k = 0; k < cols - 1; k++) {
        for (int l = 0; l < cols - k - 1; l++) {
            if (row[l] < row[l + 1]) {
                std::swap(row[l], row[l + 1]);
            }
        }
    }
}

void sortMatrixRows(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        if (i % 2 == 0) {
            sortEvenRowAscending(matrix[i], cols);
        }
        else {
            sortOddRowDescending(matrix[i], cols);
        }
    }
}

void processMatrix() {
    int rows, cols;

    inputMatrixDimensions(rows, cols);

    int** matrix = allocateMatrix(rows, cols);

    fillMatrix(matrix, rows, cols);

    std::cout << "\nOriginal matrix:\n";
    printMatrix(matrix, rows, cols);

    int sum = sumColumnsWithZero(matrix, rows, cols);
    std::cout << "Sum of elements in columns with zeros: " << sum << std::endl;

    sortMatrixRows(matrix, rows, cols);

    std::cout << "\nTransformed matrix:\n";
    printMatrix(matrix, rows, cols);

    freeMatrix(matrix, rows);
}

int main() {
    processMatrix();
    return 0;
}
