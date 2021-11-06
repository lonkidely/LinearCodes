#ifndef LINEARCODES_CYCLIC_DECODER_H
#define LINEARCODES_CYCLIC_DECODER_H

#include "decoder.h"
#include <tuple>

class CyclicDecoder : public Decoder {
private:
    static const size_t decoded_block_size = 4;
    static const size_t encoded_block_size = 7;
public:
    TypeOfCode GetType() override;

    static std::tuple<bool, bool, bool> DivPolynom(std::deque<bool> deq);

    static int GetPosOfIncorrectBit(const std::tuple<bool, bool, bool> &reminder);

    static std::pair<CodeBlock<bool>, bool> DecodeCodeBlock(const CodeBlock<bool> &code_block_param);

    std::pair<std::wstring, bool> Decode(const std::wstring &code_param) override;
};

#endif //LINEARCODES_CYCLIC_DECODER_H
