#ifndef LINEARCODES_UTILS_H
#define LINEARCODES_UTILS_H

#include <string>
#include <tuple>
#include <deque>

bool IsCorrectNumber(const std::wstring &str);

std::tuple<bool, bool, bool> DivPolynom(std::deque<bool> deq);

#endif //LINEARCODES_UTILS_H
