#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <windows.h>

bool isSafePunct(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::ispunct(uc);
}

bool isSafeSpace(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isspace(uc);
}

bool isSafeDigit(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return std::isdigit(uc);
}

bool isPrime(long long n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

bool isNumberString(const std::string& str) {
    if (str.empty()) return false;

    for (size_t i = 0; i < str.length(); i++) {
        if (!isSafeDigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool hasLeadingZeros(const std::string& str) {
    return str.length() > 1 && str[0] == '0';
}

std::vector<std::string> splitWords(const std::string& input) {
    std::vector<std::string> words;
    std::string currentWord;

    for (size_t i = 0; i < input.length(); i++) {
        char c = input[i];

        if (isSafePunct(c) || isSafeSpace(c)) {
            if (!currentWord.empty()) {
                words.push_back(currentWord);
                currentWord.clear();
            }
        }
        else {
            currentWord += c;
        }
    }

    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    return words;
}

std::vector<long long> extractPrimes(const std::vector<std::string>& words) {
    std::vector<long long> primes;

    for (size_t i = 0; i < words.size(); i++) {
        const std::string& word = words[i];

        if (isNumberString(word) && !hasLeadingZeros(word)) {
            try {
                long long num = std::stoll(word);

                if (isPrime(num)) {
                    primes.push_back(num);
                }
            }
            catch (const std::exception& e) {
            }
        }
    }

    return primes;
}

void printResult(const std::vector<long long>& primes) {
    for (size_t i = 0; i < primes.size(); i++) {
        if (i > 0) std::cout << " ";
        std::cout << primes[i];
    }
    std::cout << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "=== ПРОГРАММА ДЛЯ ПОИСКА ПРОСТЫХ ЧИСЕЛ В ТЕКСТЕ ===" << std::endl;
    std::cout << std::endl;

    std::cout << "ИНСТРУКЦИЯ:" << std::endl;
    std::cout << "1. Введите строку, содержащую слова, разделенные знаками препинания или пробелами" << std::endl;
    std::cout << "2. Программа найдет все простые числа среди этих слов" << std::endl;
    std::cout << "3. Результат будет выведен в одну строку, разделенный пробелами" << std::endl;
    std::cout << std::endl;

    std::cout << "ШАБЛОН ВВОДА: слово1,слово2,слово3,...,словоN" << std::endl;
    std::cout << "ПРИМЕР: apple,123,banana,17,42,orange,29" << std::endl;
    std::cout << std::endl;

    std::cout << "ВВЕДИТЕ СТРОКУ: ";
    std::string input;
    std::getline(std::cin, input);

    std::cout << std::endl;
    std::cout << "ОБРАБОТКА ДАННЫХ..." << std::endl;

    std::vector<std::string> words = splitWords(input);
    std::cout << "Найдено " << words.size() << " слов в строке" << std::endl;

    std::vector<long long> primes = extractPrimes(words);
    std::cout << "Найдено " << primes.size() << " простых чисел" << std::endl;

    std::cout << std::endl;
    std::cout << "РЕЗУЛЬТАТ:" << std::endl;
    if (primes.empty()) {
        std::cout << "Простые числа не найдены" << std::endl;
    }
    else {
        printResult(primes);
    }

    std::cout << std::endl;
    std::cout << "ПРОГРАММА ЗАВЕРШЕНА. НАЖМИТЕ ENTER ДЛЯ ВЫХОДА." << std::endl;
    std::cin.get();

    return 0;
}
