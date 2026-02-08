#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iomanip>


struct Mark {
    std::string subject_; 
    size_t mark_;         
};

struct StudentData {
    std::string name_;           
    size_t number_;              
    std::vector<Mark> marks_;    

    double CalculationAverage() const {
        if (marks_.empty()) return 0.0;
        double sum = 0;
        for (const auto& m : marks_) sum += m.mark_;
        return sum / marks_.size();
    }

    size_t CalcTotalSum() const {
        size_t sum = 0;
        for (const auto& m : marks_) sum += m.mark_;
        return sum;
    }
};

using StudentMap = std::map<size_t, StudentData>;

int main() {
    StudentMap students;

    std::ifstream file("students.txt");
    if (!file.is_open()) {
        std::cerr << "cannot read file!" << std::endl;
        return 1;
    }

    size_t id;
    while (file >> id) {
        StudentData s;
        s.number_ = id;
        file >> s.name_;

        int marksCount;
        file >> marksCount;
        for (int i = 0; i < marksCount; ++i) {
            Mark m;
            file >> m.subject_ >> m.mark_;
            s.marks_.push_back(m);
        }
        students[id] = s;
    }
    file.close();

    std::cout << "2. listed by student id\n";
    for (const auto& [id, data] : students) {
        std::cout << id << ": " << data.name_ << std::endl;
    }

    std::cout << "\n3.Avarage mark\n";
    for (const auto& [id, data] : students) {
        std::cout << data.name_ << " - " << std::fixed << std::setprecision(2) << data.getAverage() << std::endl;
    }

    std::cout << "\n--- 4. Alphabetic order (and avarage mark) ---\n";
    std::vector<const StudentData*> sortedList;
    for (auto& pair : students) sortedList.push_back(&pair.second);

    std::sort(sortedList.begin(), sortedList.end(), [](const StudentData* a, const StudentData* b) {
        if (a->name_ != b->name_) return a->name_ < b->name_;
        return a->getAverage() > b->getAverage();
        });

    int count = 1;
    for (const auto* s : sortedList) {
        std::cout << count++ << ". " << s->name_ << ", ID: " << s->number_
            << ", Avg: " << s->getAverage() << std::endl;
    }

    double minRange = 4.0, maxRange = 5.0;
    std::cout << "\n 5. Students avarage mark [" << minRange << ", " << maxRange << "]\n";
    for (const auto* s : sortedList) {
        double avg = s->getAverage();
        if (avg >= minRange && avg <= maxRange) {
            std::cout << s->name_ << " (" << avg << ")" << std::endl;
        }
    }

    std::string targetSubject = "Math";
    std::cout << "\n--- 6. passed subject '" << targetSubject << "'\n";
    for (const auto& [id, s] : students) {
        for (const auto& m : s.marks_) {
            if (m.subject_ == targetSubject) {
                std::cout << s.name_ << std::endl;
                break;
            }
        }
    }

    std::cout << "\n7. Number of students by subject\n";
    std::map<std::string, int> subjectStats;
    for (const auto& [id, s] : students) {
        for (const auto& m : s.marks_) subjectStats[m.subject_]++;
    }
    for (const auto& [sub, n] : subjectStats) {
        std::cout << sub << ": " << n << std::endl;
    }

    std::cout << "\n 8. Avarage subject mark by descending\n";
    std::map<std::string, std::vector<size_t>> subjectMarks;
    for (const auto& [id, s] : students) {
        for (const auto& m : s.marks_) subjectMarks[m.subject_].push_back(m.mark_);
    }

    std::vector<std::pair<std::string, double>> avgSubjectList;
    for (auto& [sub, marks] : subjectMarks) {
        double sum = std::accumulate(marks.begin(), marks.end(), 0.0);
        avgSubjectList.push_back({ sub, sum / marks.size() });
    }
    std::sort(avgSubjectList.begin(), avgSubjectList.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });
    for (const auto& p : avgSubjectList) std::cout << p.first << ": " << p.second << std::endl;

    std::cout << "\n 9. Students with max sum of marks \n";
    size_t maxTotal = 0;
    for (const auto& [id, s] : students) maxTotal = std::max(maxTotal, s.getTotalSum());
    for (const auto& [id, s] : students) {
        if (s.getTotalSum() == maxTotal) std::cout << s.name_ << " (Sum: " << maxTotal << ")" << std::endl;
    }

    std::cout << "\n 10. students with debts (1, 2, 3) \n";
    for (const auto& [id, s] : students) {
        bool hasBadMark = false;
        for (const auto& m : s.marks_) {
            if (m.mark_ <= 3) { hasBadMark = true; break; }
        }
        if (hasBadMark) std::cout << s.name_ << std::endl;
    }

    return 0;
}
