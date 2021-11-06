#ifndef LINEARCODES_HAMMING_ENCODER_H
#define LINEARCODES_HAMMING_ENCODER_H

#include "encoder.h"

class HammingEncoder : public Encoder {
private:
    static const size_t decoded_block_size = 4;
    static const size_t encoded_block_size = 7;
public:
    TypeOfCode GetType() override;

    static CodeBlock<bool> EncodeCodeBlock(const CodeBlock<bool> &code_block_param);

    std::wstring Encode(const std::wstring &code_param) override;
};

#endif //LINEARCODES_HAMMING_ENCODER_H
