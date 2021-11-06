#ifndef LINEARCODES_ENCODER_H
#define LINEARCODES_ENCODER_H

#include "../code/code.h"

class Encoder {
public:
    virtual TypeOfCode GetType() = 0;

    virtual std::wstring Encode(const std::wstring &code_param) = 0;

    virtual ~Encoder() = default;
};

#endif //LINEARCODES_ENCODER_H
