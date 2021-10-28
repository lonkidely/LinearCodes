#ifndef LINEARCODES_CONTROLLER_H
#define LINEARCODES_CONTROLLER_H

#include "factory.h"

class Controller {
private:
    Factory *factory;
public:
    explicit Controller(Factory *factory_param);

    void Work();

    void EncodeMessage(Code &code_param);

    int DecodeMessage(Code &code_param);
};

#endif //LINEARCODES_CONTROLLER_H
