#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

const int MAX_OUTPUT_LINES = 10;

int maxSubstringSearch(const std::string& s) {
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

int fileRead(const std::string& filename,
    std::vector<std::string>& lines,
    std::vector<int>& lengths) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file **" + filename + "**.");
    }

    int overall_max_len = 0;
    std::string line;

    while (std::getline(file, line)) {
        int len = maxSubstringSearch(line);

        lines.push_back(line);
        lengths.push_back(len);

        overall_max_len = std::max(overall_max_len, len);
    }

    file.close();

    return overall_max_len;
}

void matchingLinesPrint(const std::vector<std::string>& lines, const std::vector<int>& lengths, int max_len) {

    if (lines.empty() || max_len <= 0) {
        std::cout << "Info: No lines found or maximum length is 0." << std::endl;
        return;
    }

    std::cout << "\n--- RESULT ---" << std::endl;
    std::cout << "Maximum increasing substring length in file: **" << max_len << "**" << std::endl;
    std::cout << "Lines with this maximum length (first " << MAX_OUTPUT_LINES << "):" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    int count = 0;

    for (size_t i = 0; i < lines.size(); ++i) {
        if (count >= MAX_OUTPUT_LINES) {
            break;
        }

        if (lengths[i] == max_len) {
            std::cout << '[' << count + 1 << "] (Length: " << max_len << "): " << lines[i] << std::endl;
            count++;
        }
    }

    if (count >= MAX_OUTPUT_LINES && count < lines.size()) {
        std::cout << "\n...there possible more lines. Displayed the first " << MAX_OUTPUT_LINES << ' ' << std::endl;
    }
    std::cout << "------------------------------------------" << std::endl;
}

int main() {
    const std::string filename = "input.txt";

    std::ifstream test_file(filename);


    std::vector<std::string> lines_content;
    std::vector<int> lines_lengths;
    int max_len = 0;

    try {
        max_len = fileRead(filename, lines_content, lines_lengths);

        if (lines_content.empty()) {
            std::cout << "Info: File **" << filename << "** is empty or contains no processable lines." << std::endl;
            return 0;
        }

        matchingLinesPrint(lines_content, lines_lengths, max_len);

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}
