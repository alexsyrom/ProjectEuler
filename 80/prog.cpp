#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}


class UnsignedDecimalFloat {
  public:
    static const size_t kBase = 10;
    static const size_t kPrecision = 204;

    UnsignedDecimalFloat(size_t number = 0)
        : digits_(kPrecision, 0)
    {
        digits_[0] = number;
    }

    UnsignedDecimalFloat operator* (const UnsignedDecimalFloat& multiplier) const {
        UnsignedDecimalFloat result = 0;
        for (size_t result_index = 0; result_index < kPrecision; ++result_index) {
            for (size_t this_index = 0; this_index <= result_index; ++ this_index) {
                size_t multiplier_index = result_index - this_index;
                result.digits_[result_index] += this->digits_[this_index] * 
                    multiplier.digits_[multiplier_index];
            }
        }
        for (size_t result_index = kPrecision - 1; result_index > 0; --result_index) {
            result.digits_[result_index - 1] += result.digits_[result_index] / kBase;
            result.digits_[result_index] %= kBase;
        }
        return result;
    }

    UnsignedDecimalFloat operator+ (const UnsignedDecimalFloat& other) const {
        UnsignedDecimalFloat result = 0;
        for (size_t index = 0; index < kPrecision; ++index) {
            result.digits_[index] = this->digits_[index] + other.digits_[index];
        }
        for (size_t index = kPrecision - 1; index > 0; --index) {
            result.digits_[index - 1] += result.digits_[index] / kBase;
            result.digits_[index] %= kBase;
        }
        return result;
    }

    UnsignedDecimalFloat operator/ (size_t other) const {
        UnsignedDecimalFloat result = *this;
        for (size_t index = 0; index < kPrecision - 1; ++index) {
            result.digits_[index + 1] += kBase * (result.digits_[index] % other);
            result.digits_[index] /= other;
        }
        result.digits_[kPrecision - 1] /= other;
        return result;
    }

    bool operator< (const UnsignedDecimalFloat& other) const {
        return digits_ < other.digits_;
    }

    size_t ComputeNFirstDigitsSum(size_t first_digits_number) {
        first_digits_number = std::min(first_digits_number, kPrecision);
        return std::accumulate(digits_.begin(), digits_.begin() + first_digits_number, 0);
    }

    static UnsignedDecimalFloat GetMinimumNonZeroNumber() {
        UnsignedDecimalFloat result = 0;
        result.digits_[kPrecision - 1] = 1;
        return result;
    }

    static UnsignedDecimalFloat GetMinimumNonZeroNumberWithHalvedPrecision() {
        UnsignedDecimalFloat result = 0;
        result.digits_[kPrecision / 2 - 1] = 1;
        return result;
    }

  private:
    // digits_[0] is the integer part of the number, others are true digits after the point 
    std::vector<size_t> digits_;
};

const UnsignedDecimalFloat kEpsilon = UnsignedDecimalFloat::GetMinimumNonZeroNumber();
const UnsignedDecimalFloat kEpsilonSqrt = 
    UnsignedDecimalFloat::GetMinimumNonZeroNumberWithHalvedPrecision();

bool IsSquare(size_t number) {
    uint64_t root = std::sqrt(number);
    for (uint64_t index = root - 1; index < root + 2; ++index) {
        if (index * index == number) {
            return true;
        }
    }
    return false;
}

UnsignedDecimalFloat Sqrt(
        const UnsignedDecimalFloat& number,
        UnsignedDecimalFloat left,
        UnsignedDecimalFloat right,
        const UnsignedDecimalFloat& epsilon = kEpsilonSqrt)
{
    while (left + epsilon < right) {
        auto medium = (left + right) / 2;
        if (number < medium * medium) {
            right = medium;
        } else {
            left = medium;
        }
    }
    return left;
}



int main() {
    std::ofstream output_stream("output.txt");
    size_t digit_sum = 0;
    UnsignedDecimalFloat previous_root = 1;
    for (size_t index = 2; index < 100; ++index) {
        if (IsSquare(index)) {
            continue;
        }
        UnsignedDecimalFloat root = Sqrt(index, previous_root, index); 
        previous_root = root;
        digit_sum += root.ComputeNFirstDigitsSum(100);
    }
    output_stream << digit_sum;
    return 0;
}


