#include "cyclic_code.h"
#include <algorithm>

CyclicCode::CyclicCode() : BinaryCode() {}

CyclicCode::CyclicCode(const std::wstring &code_param, size_t code_block_size) : BinaryCode(code_param,
                                                                                            code_block_size) {}

CyclicCode::CyclicCode(const std::vector<CodeBlock<bool>> &blocks_param) : BinaryCode(blocks_param) {}

TypeOfCode CyclicCode::GetCodeType() const {
    return code_type;
}

bool CyclicCode::IsCodeCorrect(const std::wstring &code_param) const {
    return BinaryCode::IsCodeCorrect(code_param);
}

size_t CyclicCode::GetBlocksCount() const {
    return BinaryCode::GetBlocksCount();
}

CodeBlock<bool> CyclicCode::GetCodeBlock(size_t index) const {
    return BinaryCode::GetCodeBlock(index);
}

std::wstring CyclicCode::GetCodeWString() const {
    return BinaryCode::GetCodeWString();
}
