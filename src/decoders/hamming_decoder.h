#ifndef LINEARCODES_HAMMING_DECODER_H
#define LINEARCODES_HAMMING_DECODER_H

#include "decoder.h"

class HammingDecoder : public Decoder {
private:
    static const size_t block_size = 4;
public:
    TypeOfCode GetType() override;

    static std::pair<CodeBlock, bool> DecodeCodeBlock(const CodeBlock &code_block_param);

    std::pair<Code, bool> Decode(const Code &code) override;
};

#endif //LINEARCODES_HAMMING_DECODER_H
