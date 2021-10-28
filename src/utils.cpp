#include "../include/utils.h"
#include <algorithm>

bool IsCorrectNumber(const std::wstring &str) {
    bool is_correct = true;
    for (wchar_t i: str) {
        if (i < (wchar_t) '0' || i > (wchar_t) '9')
            is_correct = false;
    }
    return is_correct;
}
