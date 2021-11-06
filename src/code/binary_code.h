#ifndef LINEARCODES_BINARY_CODE_H
#define LINEARCODES_BINARY_CODE_H

#include "code.h"
#include <vector>

class BinaryCode : public Code {
private:
    std::vector<CodeBlock<bool>> blocks;
    size_t block_size;
    size_t blocks_count;
public:
    BinaryCode();

    BinaryCode(const std::wstring &code_param, size_t code_block_size);

    explicit BinaryCode(const std::vector<CodeBlock<bool>> &blocks_param);

    bool IsCodeCorrect(const std::wstring &code_param) const override;

    size_t GetBlocksCount() const override;

    virtual CodeBlock<bool> GetCodeBlock(size_t index) const;

    std::wstring GetCodeWString() const override;
};

#endif //LINEARCODES_BINARY_CODE_H
