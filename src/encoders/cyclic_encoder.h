#ifndef LINEARCODES_CYCLIC_ENCODER_H
#define LINEARCODES_CYCLIC_ENCODER_H

#include "encoder.h"
#include <tuple>

class CyclicEncoder : public Encoder {
private:
    static const size_t decoded_block_size = 4;
    static const size_t encoded_block_size = 7;
public:
    TypeOfCode GetType() override;

    static std::tuple<bool, bool, bool> DivPolynom(std::deque<bool> deq);

    static CodeBlock<bool> EncodeCodeBlock(const CodeBlock<bool> &code_block_param);

    std::wstring Encode(const std::wstring &code_param) override;
};

#endif //LINEARCODES_CYCLIC_ENCODER_H
