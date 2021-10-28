#include "../include/code.h"
#include <algorithm>

Code::Code(std::wstring &code_param, TypeOfCode code_type_param, size_t code_block_size) {
    size_t length = code_param.length();
    blocks_count = (length + code_block_size - 1) / code_block_size;
    code_blocks = new CodeBlock[blocks_count];

    size_t index = 0;
    for (size_t i = 0; i < blocks_count; ++i) {
        code_blocks[i].code = new bool[code_block_size];
        code_blocks[i].size = code_block_size;

        std::fill(code_blocks[i].code, code_blocks[i].code + code_block_size, false);

        for (size_t j = 0; j < std::min(code_block_size, length - index + j); ++j)
            code_blocks[i].code[j] = static_cast<bool>(code_param[index++] - '0');
    }
    code_type = code_type_param;
}

Code::Code(CodeBlock *blocks_param, size_t blocks_count_param, TypeOfCode code_type_param) {
    blocks_count = blocks_count_param;
    code_blocks = new CodeBlock[blocks_count];

    for (size_t i = 0; i < blocks_count; ++i) {
        code_blocks[i].size = blocks_param[i].size;
        code_blocks[i].code = new bool[code_blocks[i].size];

        for (size_t j = 0; j < code_blocks[i].size; ++j) {
            code_blocks[i].code[j] = blocks_param[i].code[j];
        }
    }

    code_type = code_type_param;
}

Code::Code(const Code &code_param) {
    blocks_count = code_param.blocks_count;
    code_blocks = new CodeBlock[blocks_count];

    for (size_t i = 0; i < blocks_count; ++i) {
        code_blocks[i].size = code_param.code_blocks[i].size;
        code_blocks[i].code = new bool[code_blocks[i].size];

        for (size_t j = 0; j < code_blocks[i].size; ++j) {
            code_blocks[i].code[j] = code_param.code_blocks[i].code[j];
        }
    }

    code_type = code_param.code_type;
}

TypeOfCode Code::GetCodeType() const {
    return code_type;
}

std::wstring Code::GetCodeWString() const {
    std::wstring result;
    for (size_t i = 0; i < blocks_count; ++i) {
        for (size_t j = 0; j < code_blocks[i].size; ++j) {
            result += (wchar_t) (code_blocks[i].code[j] + '0');
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}

size_t Code::GetBlocksCount() const {
    return blocks_count;
}

CodeBlock &Code::GetCodeBlock(size_t index) const {
    return code_blocks[index];
}
