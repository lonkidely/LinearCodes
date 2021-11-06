#ifndef LINEARCODES_CODE_H
#define LINEARCODES_CODE_H

#include <deque>
#include <string>

enum class TypeOfCode : int {
    kHamming,
    kCyclicCode
};

template<typename T>
struct CodeBlock {
    std::deque<T> code;
};

class Code {
public:
    virtual TypeOfCode GetCodeType() const = 0;

    virtual bool IsCodeCorrect(const std::wstring &code_param) const = 0;

    virtual size_t GetBlocksCount() const = 0;

    virtual std::wstring GetCodeWString() const = 0;

    virtual ~Code() = default;
};

#endif //LINEARCODES_CODE_H
