#include "../include/utils.h"
#include <algorithm>

bool IsItPowerOfTwo(unsigned int number) {
    int count_bits = 0;
    while (number) {
        if (number & 1) count_bits++;
        number >>= 1;
    }
    return count_bits == 1;
}

unsigned int CountPowerOfTwo(unsigned int number) {
    unsigned int i = 1;
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

bool IsCorrectNumber(std::wstring &str) {
    bool is_correct = true;
    for (wchar_t i: str) {
        if (i < (wchar_t) '0' || i > (wchar_t) '9')
            is_correct = false;
    }
    return is_correct;
}