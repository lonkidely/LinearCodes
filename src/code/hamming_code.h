#ifndef LINEARCODES_HAMMING_CODE_H
#define LINEARCODES_HAMMING_CODE_H

#include "binary_code.h"
#include <vector>

class HammingCode : public BinaryCode {
private:
    static const TypeOfCode code_type = TypeOfCode::kHamming;
public:
    HammingCode();

    HammingCode(const std::wstring &code_param, size_t code_block_size);

    explicit HammingCode(const std::vector<CodeBlock<bool>> &blocks_param);

    TypeOfCode GetCodeType() const override;

    bool IsCodeCorrect(const std::wstring &code_param) const override;

    size_t GetBlocksCount() const override;

    CodeBlock<bool> GetCodeBlock(size_t index) const override;

    std::wstring GetCodeWString() const override;
};

#endif //LINEARCODES_HAMMING_CODE_H
