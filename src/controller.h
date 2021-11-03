#ifndef LINEARCODES_CONTROLLER_H
#define LINEARCODES_CONTROLLER_H

#include "factory.h"

class Controller {
private:
    std::shared_ptr<Factory> factory;
public:
    explicit Controller(std::shared_ptr<Factory> factory_param);

    void Work();

    Code EncodeMessage(Code &code_param);

    std::pair<Code, bool> DecodeMessage(Code &code_param);
};

#endif //LINEARCODES_CONTROLLER_H