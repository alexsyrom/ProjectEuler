#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

template <class Class>
void Print(Class instance) {
    std::cout << instance << std::endl;
}

void Print() {
    std::cout << std::endl;
}

class UnsignedLongInteger {
  public:
    const size_t kBase = 10;

    UnsignedLongInteger(size_t number) {
        do {
            digits_.push_back(number % kBase);
            number /= kBase;
        } while (number > 0);
    }

    size_t ComputeSumOfDigits() const {
        return std::accumulate(digits_.begin(), digits_.end(), 0);
    }

    UnsignedLongInteger& operator *=(size_t number) {
        digits_[0] *= number;
        for (size_t index = 1; index < digits_.size(); ++index) {
            digits_[index] = digits_[index] * number + digits_[index - 1] / kBase;
            digits_[index - 1] %= kBase;
        }
        for (size_t last_digit = digits_.size() - 1; digits_[last_digit] >= kBase; ++last_digit) {
            digits_.push_back(digits_[last_digit] / kBase);
            digits_[last_digit] %= kBase;
        }
        return *this;
    }

  private:
    std::vector<size_t> digits_;
};

int main() {
    std::ofstream output_stream("output.txt");
    size_t power = 1000;
    size_t multiplier_power = 10;
    size_t multiplier = 1 << multiplier_power;
    UnsignedLongInteger long_integer = 1;
    for (size_t index = 0; index < power / multiplier_power; ++index) {
        long_integer *= multiplier;
    }
    size_t sum_of_digits = long_integer.ComputeSumOfDigits();
    output_stream << sum_of_digits;
    return 0;
}


