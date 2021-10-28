#ifndef LINEARCODES_DECODER_H
#define LINEARCODES_DECODER_H

#include "code.h"


class Decoder {
public:
    virtual TypeOfCode GetType() = 0;

    virtual std::pair<Code, bool> Decode(const Code &) = 0;

    virtual ~Decoder() = default;
};

#endif //LINEARCODES_DECODER_H
