#include "hamming_code.h"
#include <algorithm>

HammingCode::HammingCode() : BinaryCode() {}

HammingCode::HammingCode(const std::wstring &code_param, size_t code_block_size) : BinaryCode(code_param,
                                                                                              code_block_size) {}

HammingCode::HammingCode(const std::vector<CodeBlock<bool>> &blocks_param) : BinaryCode(blocks_param) {}

TypeOfCode HammingCode::GetCodeType() const {
    return code_type;
}

bool HammingCode::IsCodeCorrect(const std::wstring &code_param) const {
    return BinaryCode::IsCodeCorrect(code_param);
}

size_t HammingCode::GetBlocksCount() const {
    return BinaryCode::GetBlocksCount();
}

CodeBlock<bool> HammingCode::GetCodeBlock(size_t index) const {
    return BinaryCode::GetCodeBlock(index);
}

std::wstring HammingCode::GetCodeWString() const {
    return BinaryCode::GetCodeWString();
}
