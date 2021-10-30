#ifndef LINEARCODES_CYCLIC_DECODER_H
#define LINEARCODES_CYCLIC_DECODER_H

#include "decoder.h"

class CyclicDecoder : public Decoder {
private:
    static const size_t block_size = 4;
public:
    TypeOfCode GetType() override;

    static int GetPosOfIncorrectBit(const std::tuple<bool, bool, bool> &reminder);

    static std::pair<CodeBlock, bool> DecodeCodeBlock(const CodeBlock &code_block_param);

    std::pair<Code, bool> Decode(const Code &code) override;
};

#endif //LINEARCODES_CYCLIC_DECODER_H
