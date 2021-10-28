#include "../include/code.h"
#include <algorithm>


Code::Code(std::wstring code_param, TypeOfCode code_type_param) {
    length = code_param.length();
    code = new bool[length];
    for (size_t i = 0; i < length; ++i) {
        code[i] = (int) code_param[i] - '0';
    }
    code_type = code_type_param;
}

Code::Code(Code &code_param) {
    length = code_param.GetLength();
    code_type = code_param.GetCodeType();
    bool *temp_code = code_param.GetCode();
    code = new bool[length];
    for (size_t i = 0; i < length; ++i) {
        code[i] = temp_code[i];
    }
}

TypeOfCode Code::GetCodeType() {
    return code_type;
}

bool *Code::GetCode() {
    return code;
}

std::wstring Code::GetCodeWString() {
    std::wstring result;
    for (size_t i = 0; i < length; ++i) {
        result += (wchar_t) (code[i] + '0');
    }
    std::reverse(result.begin(), result.end());
    return result;
}

size_t Code::GetLength() const {
    return length;
}

void Code::SetLength(size_t length_param) {
    length = length_param;
}

void Code::SetCode(bool *code_param) {
    code = code_param;
}
