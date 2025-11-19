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
    if (!(std::cin >> rows >> cols) || !inputValid()) {
        throw "Input error: Failed to read matrix dimensions";
    }
    if (rows <= 0 || cols <= 0) {
        throw "Input error: Dimensions must be positive numbers";
    }
    if (rows > 1000 || cols > 1000) {
        throw "Input error: Matrix dimensions too large (max 1000x1000)";
    }
}

int** allocateMatrix(int rows, int cols) {
    int** matrix = nullptr;
    try {
        matrix = new int*[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[cols]();
        }
        return matrix;
    } catch (...) {
        if (matrix != nullptr) {
            for (int i = 0; i < rows; i++) {
                if (matrix[i] != nullptr) {
                    delete[] matrix[i];
                }
            }
            delete[] matrix;
        }
        throw "Memory error: Failed to allocate memory for matrix";
    }
}

void freeMatrix(int** matrix, int rows) {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

int selectInputMethod() {
    int choice;
    std::cout << "Choose input method:\n1 - Manual\n2 - Random\n";
    if (!(std::cin >> choice) || !inputValid()) {
        throw "Input error: Failed to read input method choice";
    }
    return choice;
}

void inputMatrixManually(int** matrix, int rows, int cols) {
    if (matrix == nullptr) throw "Calculation error: Matrix is null";
    
    std::cout << "Enter matrix elements:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(std::cin >> matrix[i][j]) || !inputValid()) {
                throw "Input error: Invalid matrix element input";
            }
        }
    }
}

void inputRandomBounds(int& a, int& b) {
    std::cout << "Enter interval boundaries [a, b]: ";
    if (!(std::cin >> a >> b) || !inputValid()) {
        throw "Input error: Failed to read interval boundaries";
    }
    if (a > b) {
        throw "Input error: Invalid interval boundaries - a must be <= b";
    }
}

void fillMatrixRandom(int** matrix, int rows, int cols, int a, int b) {
    if (matrix == nullptr) throw "Calculation error: Matrix is null";
    
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

    switch (method) {
        case 1:
            inputMatrixManually(matrix, rows, cols);
            break;
        case 2: {
            int a, b;
            inputRandomBounds(a, b);
            fillMatrixRandom(matrix, rows, cols, a, b);
            break;
        }
        default:
            throw "Input error: Invalid choice - must be 1 or 2";
    }
}

void printMatrix(int** matrix, int rows, int cols) {
    int maxWidth = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int value = matrix[i][j];
            int digits = (value == 0) ? 1 : static_cast<int>(std::log10(std::abs(value))) + 1;
            if (value < 0) digits++;
            if (digits > maxWidth) {
                maxWidth = digits;
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

void sumColumnsWithZero(int** matrix, int rows, int cols) {
    if (matrix == nullptr || rows <= 0 || cols <= 0) {
        throw "Calculation error: Invalid matrix for column sum calculation";
    }

    for (int i = 0; i < cols; i++) {
        bool zeroPresence = false;
        double totalSum = 0;
        for (int j = 0; j < rows; j++) {
            if (matrix[i][j] == 0) {
                zeroPresence = true;
                break;
            }
        }
        if (zeroPresence) {
            for (int j = 0; j < rows; j++) {
                if ((matrix[i][j] > 0 && totalSum > std::numeric_limits<int>::max() - matrix[i][j]) ||
                    (matrix[i][j] < 0 && totalSum < std::numeric_limits<int>::min() - matrix[i][j])) {
                    throw "Calculation error: Integer overflow in column sum calculation";
                }
                totalSum += matrix[i][j];
            }
        }
        if (zeroPresence) {
            std::cout << "Sum in column with zero:" << totalSum << std::endl;
        }
    }
}

void sortEvenRowAscending(int* row, int cols) {
    if (row == nullptr || cols <= 0) {
        throw "Calculation error: Invalid row for sorting";
    }

    for (int k = 0; k < cols - 1; k++) {
        for (int l = 0; l < cols - k - 1; l++) {
            if (row[l] > row[l + 1]) {
                std::swap(row[l], row[l + 1]);
            }
        }
    }
}

void sortOddRowDescending(int* row, int cols) {
    if (row == nullptr || cols <= 0) {
        throw "Calculation error: Invalid row for sorting";
    }

    for (int k = 0; k < cols - 1; k++) {
        for (int l = 0; l < cols - k - 1; l++) {
            if (row[l] < row[l + 1]) {
                std::swap(row[l], row[l + 1]);
            }
        }
    }
}

void sortMatrixRows(int** matrix, int rows, int cols) {
    if (matrix == nullptr || rows <= 0 || cols <= 0) {
        throw "Calculation error: Invalid matrix for sorting";
    }

    for (int i = 0; i < rows; i++) {
        if (i % 2 == 0) {
            sortEvenRowAscending(matrix[i], cols);
        } else {
            sortOddRowDescending(matrix[i], cols);
        }
    }
}

void processMatrix() {
    int rows = 0, cols = 0;
    int** matrix = nullptr;

    try {
        inputMatrixDimensions(rows, cols);
        matrix = allocateMatrix(rows, cols);
        fillMatrix(matrix, rows, cols);

        std::cout << "\nOriginal matrix:\n";
        printMatrix(matrix, rows, cols);

        sumColumnsWithZero(matrix, rows, cols);

        sortMatrixRows(matrix, rows, cols);

        std::cout << "\nTransformed matrix:\n";
        printMatrix(matrix, rows, cols);

        freeMatrix(matrix, rows);
        
    } catch (const char* errorMsg) {
        if (matrix != nullptr) {
            freeMatrix(matrix, rows);
        }
        throw;
    }
}

int main() {
    try {
        processMatrix();
        std::cout << "Program completed successfully." << std::endl;
        return 0;
    } catch (const char* errorMsg) {
        std::cerr << "Error: " << errorMsg << std::endl;
        std::cerr << "Program terminated due to errors." << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        std::cerr << "Program terminated due to errors." << std::endl;
        return 1;
    }
}
