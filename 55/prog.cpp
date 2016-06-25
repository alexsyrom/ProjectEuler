#include <iostream>
#include <fstream>
#include <vector>

template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}

const size_t kBase = 10;
const size_t kMaxStepNumber = 50;

size_t Reverse(size_t number, size_t log) {
    size_t answer = 0;
    for (size_t index = 0; index <= log; ++index) {
        answer = answer * kBase + number % kBase;
        number /= kBase;
    }
    return answer;
}

bool IsPalindrom(size_t number, size_t log) {
    return number == Reverse(number, log);
}

bool IsLychrelNumber(size_t number, size_t log, size_t begin) {
    for (size_t index = 0; index < kMaxStepNumber; ++index) {
        number += Reverse(number, log);
        if (number >= begin * kBase) {
            ++log;
            begin *= kBase;
        }
        if (IsPalindrom(number, log)) {
            return false;
        }
    }
    return true;
}


int main() {
    std::ofstream output_stream("output.txt");
    size_t max_log = 3;

    size_t lychrel_numbers_count = 0;
    size_t begin = 10;
    for (size_t log = 1; log <= max_log; ++log) {
        for (size_t index = begin; index < begin * kBase; ++index) {
            if (IsLychrelNumber(index, log, begin)) {
                ++lychrel_numbers_count;
            }
        }
        begin *= kBase;
    }
    output_stream << lychrel_numbers_count;
    return 0;
}


