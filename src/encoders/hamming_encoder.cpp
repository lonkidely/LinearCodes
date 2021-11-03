#include "hamming_encoder.h"

TypeOfCode HammingEncoder::GetType() {
    return TypeOfCode::kHamming;
}

CodeBlock HammingEncoder::EncodeCodeBlock(const CodeBlock &code_block_param) {
    CodeBlock result_block{};
    result_block.size = block_size;
    result_block.code = new bool[block_size];

    result_block.code[2] = code_block_param.code[0];
    result_block.code[4] = code_block_param.code[1];
    result_block.code[5] = code_block_param.code[2];
    result_block.code[6] = code_block_param.code[3];
    result_block.code[0] = result_block.code[2] ^ result_block.code[4] ^ result_block.code[6];
    result_block.code[1] = result_block.code[2] ^ result_block.code[5] ^ result_block.code[6];
    result_block.code[3] = result_block.code[4] ^ result_block.code[5] ^ result_block.code[6];

    return result_block;
}

Code HammingEncoder::Encode(const Code &code) {
    size_t count_blocks = code.GetBlocksCount();
    auto *result_blocks = new CodeBlock[count_blocks];
    for (size_t i = 0; i < count_blocks; ++i) {
        result_blocks[i] = EncodeCodeBlock(code.GetCodeBlock(i));
    }
    Code result(result_blocks, count_blocks, code.GetCodeType());
    return result;
}
