#ifndef LINEARCODES_DECODER_H
#define LINEARCODES_DECODER_H

#include "code.h"


class Decoder {
public:
    virtual TypeOfCode GetType() = 0;

    virtual int Decode(Code &) = 0;

    virtual ~Decoder() {}
};

#endif //LINEARCODES_DECODER_H
