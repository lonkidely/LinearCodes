#ifndef LINEARCODES_CODE_H
#define LINEARCODES_CODE_H

#include <string>

enum class TypeOfCode : int {
    kHamming,
    kCycleCode
};

class Code {
private:
    bool *code;
    size_t length;
    TypeOfCode code_type;
public:

    Code(std::wstring code_param, TypeOfCode code_type_param);

    Code(Code &code_param);

    TypeOfCode GetCodeType();

    size_t GetLength() const;

    void SetLength(size_t length_param);

    bool *GetCode();

    std::wstring GetCodeWString();

    void SetCode(bool *code_param);
};

#endif //LINEARCODES_CODE_H
