#include "hamming_encoder.h"
#include "../code/hamming_code.h"

TypeOfCode HammingEncoder::GetType() {
    return TypeOfCode::kHamming;
}

CodeBlock<bool> HammingEncoder::EncodeCodeBlock(const CodeBlock<bool> &code_block_param) {
    CodeBlock<bool> result_block{};
    result_block.code.resize(encoded_block_size);

    result_block.code[2] = code_block_param.code[0];
    result_block.code[4] = code_block_param.code[1];
    result_block.code[5] = code_block_param.code[2];
    result_block.code[6] = code_block_param.code[3];
    result_block.code[0] = result_block.code[2] ^ result_block.code[4] ^ result_block.code[6];
    result_block.code[1] = result_block.code[2] ^ result_block.code[5] ^ result_block.code[6];
    result_block.code[3] = result_block.code[4] ^ result_block.code[5] ^ result_block.code[6];

    return result_block;
}

std::wstring HammingEncoder::Encode(const std::wstring &code_param) {
    HammingCode code(code_param, decoded_block_size);
    size_t count_blocks = code.GetBlocksCount();
    std::vector<CodeBlock<bool>> result_blocks(count_blocks);

    for (size_t i = 0; i < count_blocks; ++i) {
        result_blocks[i] = EncodeCodeBlock(code.GetCodeBlock(i));
    }

    HammingCode result(result_blocks);
    return result.GetCodeWString();
}
