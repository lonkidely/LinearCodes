#ifndef LINEARCODES_ENCODER_H
#define LINEARCODES_ENCODER_H

#include <string>
#include "code.h"


class Encoder {
public:
    virtual TypeOfCode GetType() = 0;

    virtual void Encode(Code &) = 0;

    virtual ~Encoder() {}
};

#endif //LINEARCODES_ENCODER_H
