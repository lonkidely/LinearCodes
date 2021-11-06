#ifndef LINEARCODES_CYCLIC_CODE_H
#define LINEARCODES_CYCLIC_CODE_H

#include "binary_code.h"
#include <vector>

class CyclicCode : public BinaryCode {
private:
    static const TypeOfCode code_type = TypeOfCode::kCyclicCode;
public:
    CyclicCode();

    CyclicCode(const std::wstring &code_param, size_t code_block_size);

    explicit CyclicCode(const std::vector<CodeBlock<bool>> &blocks_param);

    TypeOfCode GetCodeType() const override;

    bool IsCodeCorrect(const std::wstring &code_param) const override;

    size_t GetBlocksCount() const override;

    CodeBlock<bool> GetCodeBlock(size_t index) const override;

    std::wstring GetCodeWString() const override;
};

#endif //LINEARCODES_CYCLIC_CODE_H
