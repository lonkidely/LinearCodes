#ifndef LINEARCODES_CODE_H
#define LINEARCODES_CODE_H

#include <string>

enum class TypeOfCode : int {
    kHamming,
    kCycleCode
};

struct CodeBlock {
    bool *code;
    size_t size;
};

class Code {
private:
    CodeBlock *code_blocks;
    size_t blocks_count;
    TypeOfCode code_type;
public:

    Code(const std::wstring &code_param, TypeOfCode code_type_param, size_t code_block_size);

    Code(const CodeBlock *blocks_param, size_t blocks_count_param, TypeOfCode code_type_param);

    Code(const Code &code_param);

    TypeOfCode GetCodeType() const;

    size_t GetBlocksCount() const;

    CodeBlock &GetCodeBlock(size_t index) const;

    std::wstring GetCodeWString() const;
};

#endif //LINEARCODES_CODE_H