#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>

template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}

const size_t kMatrixSize = 80;

using Matrix = std::array<std::array<size_t, kMatrixSize>, kMatrixSize>;

Matrix g_matrix;
Matrix g_path_sums;

void ReadMatrix(Matrix& matrix, std::istream& input = std::cin) {
    for (size_t first = 0; first < kMatrixSize; ++first) {
        for (size_t second = 0; second < kMatrixSize; ++second) {
             input >> matrix[first][second];
             input.get();
        }
    }
}

void ComputePathSums(const Matrix& matrix, Matrix& sums) {
    sums[0][0] = matrix[0][0];
    for (size_t second = 1; second < kMatrixSize; ++second) {
        sums[0][second] = matrix[0][second] + sums[0][second - 1];
    }
    for (size_t first = 1; first < kMatrixSize; ++first) {
        sums[first][0] = matrix[first][0] + sums[first - 1][0];
    }
    for (size_t first = 1; first < kMatrixSize; ++first) {
        for (size_t second = 1; second < kMatrixSize; ++second) {
            sums[first][second] = matrix[first][second] +
                std::min(sums[first - 1][second], sums[first][second - 1]);
        }
    }
}

int main() {
    std::ifstream input_stream("p081_matrix.txt");
    std::ofstream output_stream("output.txt");
    ReadMatrix(g_matrix, input_stream);
    ComputePathSums(g_matrix, g_path_sums);
    output_stream << g_path_sums[kMatrixSize - 1][kMatrixSize - 1];
    return 0;
}


