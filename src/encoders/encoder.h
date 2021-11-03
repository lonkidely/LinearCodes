#ifndef LINEARCODES_ENCODER_H
#define LINEARCODES_ENCODER_H

#include "../code/code.h"


class Encoder {
public:
    virtual TypeOfCode GetType() = 0;

    virtual Code Encode(const Code &code_param) = 0;

    virtual ~Encoder() = default;
};

#endif //LINEARCODES_ENCODER_H
