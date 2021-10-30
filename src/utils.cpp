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

std::tuple<bool, bool, bool> DivPolynom(std::deque<bool> deq) {
    std::deque<bool> divider, remainder;
    divider.push_back(true);
    divider.push_back(true);
    divider.push_back(false);
    divider.push_back(true);

    while (deq.size() > 3) {
        for (size_t i = 0; i < 4; ++i) {
            remainder.push_front(deq.back() ^ divider[3 - i]);
            deq.pop_back();
        }

        while (!remainder.empty()) {
            if (remainder.size() == 1 && !remainder.front()) {
                remainder.pop_front();
                break;
            }
            deq.push_back(remainder.front());
            remainder.pop_front();
        }
    }

    std::tuple<bool, bool, bool> result = std::make_tuple(deq[0], deq[1], deq[2]);
    return result;
}
