#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cmath>

template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}

const size_t kBase = 10;
const uint64_t kMaxCubicRoot = 1000 * 1000;

uint64_t Reverse(uint64_t number, size_t log) {
    uint64_t answer = 0;
    for (size_t index = 0; index <= log; ++index) {
        answer = answer * kBase + number % kBase;
        number /= kBase;
    }
    return answer;
}

uint64_t ConstructPalindrom(uint64_t half, uint64_t shift, size_t parity, size_t log) {
    uint64_t reversed = Reverse(half, log);
    if (parity) {
        return half * shift + reversed;
    } else {
        return (half / kBase) * shift + reversed;
    }
}

bool IsSquare(uint64_t number) {
    uint64_t root = std::sqrt(number);
    for (uint64_t index = root - 1; index < root + 2; ++index) {
        if (index * index == number) {
            return true;
        }
    }
    return false;
}

size_t CountDifferentWaysOfSquareCubExpression(uint64_t number) {
    std::unordered_map<uint64_t, uint64_t> cube_to_square_map;
    for (uint64_t cubic_root = 2; cubic_root <= kMaxCubicRoot; ++cubic_root) {
        uint64_t cube = cubic_root * cubic_root * cubic_root;
        if (number <= 1 + cube) {
            break;
        }
        uint64_t square = number - cube;
        if (IsSquare(square)) {
            auto iterator = cube_to_square_map.find(square);
            if (iterator == cube_to_square_map.end() || iterator->second != cube) {
                cube_to_square_map[cube] = square;
            }
        }
    }
    return cube_to_square_map.size();
}

void OutputPalindromsAndSum(
        const std::vector<uint64_t>& palindroms,
        std::ostream& output = std::cout)
{
    uint64_t sum = 0;
    for (auto palindrom: palindroms) {
        output << palindrom << std::endl;
        sum += palindrom;
    }
    output << std::endl;
    output << sum << std::endl;
}


int main(int argc, char* argv[]) {
    std::ofstream output_stream("output.txt");

    size_t good_ways_count = 4;
    size_t max_half_log = 9;
    size_t first_palindroms_count = 5;
    if (argc > 1) {
        std::ifstream input_stream("input.txt");
        input_stream >> good_ways_count >> max_half_log >> first_palindroms_count;
    }

    std::vector<uint64_t> expressed_palindroms;
    uint64_t min_half = 1;
    for (size_t half_log = 0; half_log <= max_half_log; ++half_log) {
        for (size_t parity = 0; parity < 2; ++parity) {
            for (uint64_t half = min_half; half < kBase * min_half; ++half) {
                uint64_t palindrom = ConstructPalindrom(half, kBase * min_half, parity, half_log);
                size_t ways_count = CountDifferentWaysOfSquareCubExpression(palindrom);
                if (ways_count == good_ways_count) {
                    expressed_palindroms.push_back(palindrom);
                    Print(palindrom);
                    if (expressed_palindroms.size() == first_palindroms_count) {
                        OutputPalindromsAndSum(expressed_palindroms, output_stream);
                        return 0;
                    }
                }
            }
        }
        min_half *= kBase;
    }
    OutputPalindromsAndSum(expressed_palindroms, output_stream);
    return 0;
}


