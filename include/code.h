#ifndef LINEARCODES_CODE_H
#define LINEARCODES_CODE_H

#include <string>

enum TypeOfCode : int {
    kHamming,
    kCycleCode
};

class Code {
private:
    bool *code;
    int length;
    TypeOfCode code_type;
public:
    Code();

    Code(std::wstring code_param, TypeOfCode code_type_param);

    Code(Code &code_param);

    TypeOfCode GetCodeType();

    int GetLength();

    void SetLength(int length_param);

    bool *GetCode();

    std::wstring GetCodeWString();

    void SetCode(bool *code_param);

    int GetBit(int position);

    void SetBit(int position, bool value);

    bool AreCodesEqual(Code &left, Code &right);
};

#endif //LINEARCODES_CODE_H
