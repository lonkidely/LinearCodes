#ifndef LINEARCODES_HAMMING_DECODER_H
#define LINEARCODES_HAMMING_DECODER_H

#include "decoder.h"

class HammingDecoder : public Decoder {
public:
    TypeOfCode GetType() override;

    int Decode(Code &code) override;
};

#endif //LINEARCODES_HAMMING_DECODER_H
