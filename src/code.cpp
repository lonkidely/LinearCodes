#include "../include/code.h"
#include <algorithm>

Code::Code() {
    code = nullptr;
    length = 0;
}

Code::Code(std::wstring code_param, TypeOfCode code_type_param) {
    length = code_param.length();
    code = new bool[length];
    for (int i = 0; i < length; ++i) {
        code[i] = (int) code_param[i] - '0';
    }
    code_type = code_type_param;
}

Code::Code(Code &code_param) {
    length = code_param.GetLength();
    code_type = code_param.GetCodeType();
    bool *temp_code = code_param.GetCode();
    code = new bool[length];
    for (int i = 0; i < length; ++i) {
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
    for (int i = 0; i < length; ++i) {
        result += (wchar_t) (code[i] + '0');
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int Code::GetLength() {
    return length;
}

void Code::SetLength(int length_param) {
    length = length_param;
}

void Code::SetCode(bool *code_param) {
    code = code_param;
}

int Code::GetBit(int position) {
    if (position >= length || position < 0) return -1;
    return code[position];
}

void Code::SetBit(int position, bool value) {
    if (position >= length || position < 0) return;
    code[position] = value;
}

bool Code::AreCodesEqual(Code &left, Code &right) {
    if (left.length != right.length)
        return false;
    bool equal = true;
    for (int i = 0; i < left.length; ++i) {
        if (left.code[i] != right.code[i])
            equal = false;
    }
    return equal;
}