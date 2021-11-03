#include "cyclic_decoder.h"
#include "../utils.h"

TypeOfCode CyclicDecoder::GetType() {
    return TypeOfCode::kCycleCode;
}

int CyclicDecoder::GetPosOfIncorrectBit(const std::tuple<bool, bool, bool> &reminder) {
    bool h1 = std::get<0>(reminder), h2 = std::get<1>(reminder), h3 = std::get<2>(reminder);
    int syndrome = 4 * h3 + 2 * h2 + h1;
    int pos;
    switch (syndrome) {
        case 1:
            pos = 0;
            break;
        case 2:
            pos = 1;
            break;
        case 3:
            pos = 3;
            break;
        case 4:
            pos = 2;
            break;
        case 5:
            pos = 6;
            break;
        case 6:
            pos = 4;
            break;
        case 7:
            pos = 5;
            break;
        default:
            pos = -1;
            break;
    }
    return pos;
}

std::pair<CodeBlock, bool> CyclicDecoder::DecodeCodeBlock(const CodeBlock &code_block_param) {
    CodeBlock result_block{};
    result_block.size = block_size;
    result_block.code = new bool[block_size];

    for (size_t i = 0; i < block_size; ++i) {
        result_block.code[i] = code_block_param.code[i + 3];
    }

    std::deque<bool> dividend;
    for (size_t i = 0; i < code_block_param.size; ++i) {
        dividend.push_back(code_block_param.code[i]);
    }

    int pos = GetPosOfIncorrectBit(DivPolynom(dividend));
    bool error_has_been_found = pos != -1;
    pos -= 3;
    if (pos >= 0)
        result_block.code[pos] ^= 1;

    return std::make_pair(result_block, error_has_been_found);
}

std::pair<Code, bool> CyclicDecoder::Decode(const Code &code) {
    size_t count_blocks = code.GetBlocksCount();
    auto *result_blocks = new CodeBlock[count_blocks];
    bool errors_have_been_found = false;
    for (size_t i = 0; i < count_blocks; ++i) {
        std::pair<CodeBlock, bool> res = DecodeCodeBlock(code.GetCodeBlock(i));
        result_blocks[i] = res.first;
        errors_have_been_found |= res.second;
    }
    return std::make_pair(Code(result_blocks, count_blocks, code.GetCodeType()), errors_have_been_found);
}
