#include "../include/cyclic_encoder.h"
#include "../include/utils.h"

TypeOfCode CyclicEncoder::GetType() {
    return TypeOfCode::kCycleCode;
}

CodeBlock CyclicEncoder::EncodeCodeBlock(const CodeBlock &code_block_param) {
    CodeBlock result_block{};
    result_block.size = block_size;
    result_block.code = new bool[block_size];

    std::deque<bool> dividend;
    for (size_t i = 0; i < code_block_param.size; ++i) {
        dividend.push_back(code_block_param.code[i]);
        result_block.code[i + 3] = code_block_param.code[i];
    }
    dividend.push_front(false);
    dividend.push_front(false);
    dividend.push_front(false);

    auto rem = DivPolynom(dividend);
    result_block.code[0] = std::get<0>(rem);
    result_block.code[1] = std::get<1>(rem);
    result_block.code[2] = std::get<2>(rem);

    return result_block;
}

Code CyclicEncoder::Encode(const Code &code) {
    size_t count_blocks = code.GetBlocksCount();
    auto *result_blocks = new CodeBlock[count_blocks];
    for (size_t i = 0; i < count_blocks; ++i) {
        result_blocks[i] = EncodeCodeBlock(code.GetCodeBlock(i));
    }
    Code result(result_blocks, count_blocks, code.GetCodeType());
    return result;
}
