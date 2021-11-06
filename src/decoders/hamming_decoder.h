#ifndef LINEARCODES_HAMMING_DECODER_H
#define LINEARCODES_HAMMING_DECODER_H

#include "decoder.h"

class HammingDecoder : public Decoder {
private:
    static const size_t decoded_block_size = 4;
    static const size_t encoded_block_size = 7;
public:
    TypeOfCode GetType() override;

    static std::pair<CodeBlock<bool>, bool> DecodeCodeBlock(const CodeBlock<bool> &code_block_param);

    std::pair<std::wstring, bool> Decode(const std::wstring &code_param) override;
};

#endif //LINEARCODES_HAMMING_DECODER_H
