#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const int MAX_OUTPUT_LINES = 10;

int find_max_increasing_substring_length(const std::string& s) {
    if (s.empty()) {
        return 0;
    }

    int max_len = 1;
    int current_len = 1;

    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i] > s[i - 1]) {
            current_len++;
        }
        else {
            current_len = 1;
        }

        max_len = std::max(max_len, current_len);
    }

    return max_len;
}

void process_file_and_print_results(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "🚫 Ошибка: Не удалось открыть файл **" << filename << "**." << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::vector<int> lengths;
    int overall_max_len = 0;

    std::string line;
    while (std::getline(file, line)) {
        int len = find_max_increasing_substring_length(line);

        lines.push_back(line);
        lengths.push_back(len);

        overall_max_len = std::max(overall_max_len, len);
    }

    if (lines.empty() || overall_max_len == 0) {
        std::cout << "ℹ️ Файл **" << filename << "** пуст или не содержит строк." << std::endl;
        return;
    }

    file.close();

    std::cout << "\n--- ✅ РЕЗУЛЬТАТ ---" << std::endl;
    std::cout << "Максимальная длина строго возрастающей подстроки в файле: **" << overall_max_len << "**" << std::endl;
    std::cout << "Строки с этой максимальной длиной (первые " << MAX_OUTPUT_LINES << "):" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    int count = 0;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (count >= MAX_OUTPUT_LINES) {
            break;
        }

        if (lengths[i] == overall_max_len) {
            std::cout << "[" << count + 1 << "] (Длина: " << overall_max_len << "): " << lines[i] << std::endl;
            count++;
        }
    }

    if (count >= MAX_OUTPUT_LINES && count < lines.size()) {
        std::cout << "\n...и, возможно, еще больше строк. Выведено первых " << MAX_OUTPUT_LINES << "." << std::endl;
    }
    std::cout << "------------------------------------------" << std::endl;
}

int main() {
    const std::string filename = "input.txt";
    process_file_and_print_results(filename);

    return 0;
}
