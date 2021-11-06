#include "binary_code.h"
#include <algorithm>

BinaryCode::BinaryCode() {
    blocks_count = 0;
    block_size = 0;
}

BinaryCode::BinaryCode(const std::wstring &code, size_t code_block_size) {
    std::wstring code_param = code;
    std::reverse(code_param.begin(), code_param.end());
    size_t length = code_param.length();

    blocks_count = (length + code_block_size - 1) / code_block_size;
    block_size = code_block_size;
    blocks.resize(blocks_count);

    size_t index = 0;
    for (size_t i = 0; i < blocks_count; ++i) {
        blocks[i].code.assign(block_size, false);
        for (size_t j = 0; j < std::min(code_block_size, length - index + j); ++j)
            blocks[i].code[j] = static_cast<bool>(code_param[index++] - '0');
    }
}

BinaryCode::BinaryCode(const std::vector<CodeBlock<bool>> &blocks_param) {
    blocks_count = blocks_param.size();
    block_size = blocks_param[0].code.size();
    blocks.resize(blocks_count);

    for (size_t i = 0; i < blocks_count; ++i) {
        blocks[i].code.resize(block_size);
        for (size_t j = 0; j < block_size; ++j) {
            blocks[i].code[j] = blocks_param[i].code[j];
        }
    }
}

size_t BinaryCode::GetBlocksCount() const {
    return blocks_count;
}

bool BinaryCode::IsCodeCorrect(const std::wstring &code_param) const {
    bool is_correct = code_param.length() > 0;
    for (wchar_t i: code_param) {
        if (i < static_cast<wchar_t>('0') || i > static_cast<wchar_t>('1'))
            is_correct = false;
    }
    return is_correct;
}

CodeBlock<bool> BinaryCode::GetCodeBlock(size_t index) const {
    return blocks[index];
}

std::wstring BinaryCode::GetCodeWString() const {
    std::wstring result;
    for (size_t i = 0; i < blocks_count; ++i) {
        for (size_t j = 0; j < block_size; ++j) {
            result += static_cast<wchar_t>(blocks[i].code[j] + '0');
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}
