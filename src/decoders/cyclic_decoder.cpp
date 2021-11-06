#include "cyclic_decoder.h"
#include "../code/cyclic_code.h"

TypeOfCode CyclicDecoder::GetType() {
    return TypeOfCode::kCyclicCode;
}

std::tuple<bool, bool, bool> CyclicDecoder::DivPolynom(std::deque<bool> deq) {
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

std::pair<CodeBlock<bool>, bool> CyclicDecoder::DecodeCodeBlock(const CodeBlock<bool> &code_block_param) {
    CodeBlock<bool> result_block{};
    result_block.code.resize(decoded_block_size);

    for (size_t i = 0; i < decoded_block_size; ++i) {
        result_block.code[i] = code_block_param.code[i + 3];
    }

    std::deque<bool> dividend;
    for (size_t i = 0; i < code_block_param.code.size(); ++i) {
        dividend.push_back(code_block_param.code[i]);
    }

    int pos = GetPosOfIncorrectBit(DivPolynom(dividend));
    bool error_has_been_found = pos != -1;
    pos -= 3;
    if (pos >= 0)
        result_block.code[pos] ^= 1;

    return std::make_pair(result_block, error_has_been_found);
}

std::pair<std::wstring, bool> CyclicDecoder::Decode(const std::wstring &code_param) {
    CyclicCode code(code_param, encoded_block_size);
    size_t count_blocks = code.GetBlocksCount();
    std::vector<CodeBlock<bool>> result_blocks(count_blocks);

    bool errors_have_been_found = false;
    for (size_t i = 0; i < count_blocks; ++i) {
        std::pair<CodeBlock<bool>, bool> res = DecodeCodeBlock(code.GetCodeBlock(i));
        result_blocks[i] = res.first;
        errors_have_been_found |= res.second;
    }

    CyclicCode result(result_blocks);
    return std::make_pair(result.GetCodeWString(), errors_have_been_found);
}
