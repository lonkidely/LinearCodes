#ifndef LINEARCODES_CYCLIC_ENCODER_H
#define LINEARCODES_CYCLIC_ENCODER_H

#include "encoder.h"

class CyclicEncoder : public Encoder {
private:
    static const size_t block_size = 7;
public:
    TypeOfCode GetType() override;

    static CodeBlock EncodeCodeBlock(const CodeBlock &code_block_param);

    Code Encode(const Code &code) override;
};

#endif //LINEARCODES_CYCLIC_ENCODER_H
