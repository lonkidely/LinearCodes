#include "hamming_decoder.h"
#include "../code/hamming_code.h"

TypeOfCode HammingDecoder::GetType() {
    return TypeOfCode::kHamming;
}

std::pair<CodeBlock<bool>, bool> HammingDecoder::DecodeCodeBlock(const CodeBlock<bool> &code_block_param) {
    CodeBlock<bool> result_block{};
    result_block.code.resize(decoded_block_size);

    bool h1 = code_block_param.code[0] ^ code_block_param.code[2] ^ code_block_param.code[4] ^ code_block_param.code[6];
    bool h2 = code_block_param.code[1] ^ code_block_param.code[2] ^ code_block_param.code[5] ^ code_block_param.code[6];
    bool h3 = code_block_param.code[3] ^ code_block_param.code[4] ^ code_block_param.code[5] ^ code_block_param.code[6];

    int index = h1 + 2 * h2 + 4 * h3;

    result_block.code[0] = code_block_param.code[2];
    result_block.code[1] = code_block_param.code[4];
    result_block.code[2] = code_block_param.code[5];
    result_block.code[3] = code_block_param.code[6];

    switch (index) {
        case 3:
            result_block.code[0] ^= 1;
            break;
        case 5:
            result_block.code[1] ^= 1;
            break;
        case 6:
            result_block.code[2] ^= 1;
            break;
        case 7:
            result_block.code[3] ^= 1;
            break;
        default:
            break;
    }

    return std::make_pair(result_block, index != 0);
}

std::pair<std::wstring, bool> HammingDecoder::Decode(const std::wstring &code_param) {
    HammingCode code(code_param, encoded_block_size);
    size_t count_blocks = code.GetBlocksCount();
    std::vector<CodeBlock<bool>> result_blocks(count_blocks);

    bool errors_have_been_found = false;
    for (size_t i = 0; i < count_blocks; ++i) {
        std::pair<CodeBlock<bool>, bool> res = DecodeCodeBlock(code.GetCodeBlock(i));
        result_blocks[i] = res.first;
        errors_have_been_found |= res.second;
    }

    HammingCode result(result_blocks);
    return std::make_pair(result.GetCodeWString(), errors_have_been_found);
}
