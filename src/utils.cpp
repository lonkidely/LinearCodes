#include "../include/utils.h"
#include <algorithm>

bool IsItPowerOfTwo(int number) {
    int count_bits = 0;
    while (number) {
        if (number & 1) count_bits++;
        number >>= 1;
    }
    return count_bits == 1;
}

int CountPowerOfTwo(int number) {
    int i = 1;
    int step = 1;
    while (i * 2 <= number) {
        i *= 2;
        step++;
    }
    return step;
}

int Power(int num, int degree) {
    if (degree == 0)
        return 1;
    if (degree == 1)
        return num;
    if (degree & 1)
        return num * Power(num, degree - 1);
    int tmp = Power(num, degree / 2);
    return tmp * tmp;
}

int Factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int CountCombinations(int n, int k) {
    if (k == 1) return n;
    int result = 1;
    for (int i = std::max(n - k, k) + 1; i <= n; ++i)
        result *= i;
    result /= Factorial(std::min(n - k, k));
    return result;
}

bool IsCorrectNumber(std::wstring &str) {
    bool is_correct = true;
    for (wchar_t i: str) {
        if (i < (wchar_t) '0' || i > (wchar_t) '9')
            is_correct = false;
    }
    return is_correct;
}