#include "cyclic_encoder.h"
#include "../code/cyclic_code.h"

TypeOfCode CyclicEncoder::GetType() {
    return TypeOfCode::kCyclicCode;
}

std::tuple<bool, bool, bool> CyclicEncoder::DivPolynom(std::deque<bool> deq) {
    std::deque<bool> divider, remainder;
    divider.push_back(true);
    divider.push_back(true);
    divider.push_back(false);
    divider.push_back(true);

    while (deq.size() > 3) {
        for (size_t i = 0; i < 4; ++i) {
            remainder.push_front(deq.back() ^ divider[3 - i]);
            deq.pop_back();
        }

        while (!remainder.empty()) {
            if (remainder.size() == 1 && !remainder.front()) {
                remainder.pop_front();
                break;
            }
            deq.push_back(remainder.front());
            remainder.pop_front();
        }
    }

    std::tuple<bool, bool, bool> result = std::make_tuple(deq[0], deq[1], deq[2]);
    return result;
}

CodeBlock<bool> CyclicEncoder::EncodeCodeBlock(const CodeBlock<bool> &code_block_param) {
    CodeBlock<bool> result_block{};
    result_block.code.resize(encoded_block_size);

    std::deque<bool> dividend;
    for (size_t i = 0; i < decoded_block_size; ++i) {
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

std::wstring CyclicEncoder::Encode(const std::wstring &code_param) {
    CyclicCode code(code_param, decoded_block_size);
    size_t count_blocks = code.GetBlocksCount();
    std::vector<CodeBlock<bool>> result_blocks(count_blocks);

    for (size_t i = 0; i < count_blocks; ++i) {
        result_blocks[i] = EncodeCodeBlock(code.GetCodeBlock(i));
    }

    CyclicCode result(result_blocks);
    return result.GetCodeWString();
}
