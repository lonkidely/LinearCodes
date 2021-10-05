#ifndef LINEARCODES_HAMMING_ENCODER_H
#define LINEARCODES_HAMMING_ENCODER_H

#include "encoder.h"

class HammingEncoder : public Encoder {
public:
    TypeOfCode GetType() override;

    void Encode(Code &code) override;
};

#endif //LINEARCODES_HAMMING_ENCODER_H
