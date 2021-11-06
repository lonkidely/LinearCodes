#ifndef LINEARCODES_CONTROLLER_H
#define LINEARCODES_CONTROLLER_H

#include "factory.h"

class Controller {
private:
    std::shared_ptr<Factory> factory;
public:
    explicit Controller(std::shared_ptr<Factory> factory_param);

    void Work();

    bool IsCodeCorrect(const std::wstring &code_param, TypeOfCode code_type);

    std::wstring EncodeMessage(const std::wstring &code_param, TypeOfCode code_type);

    std::pair<std::wstring, bool> DecodeMessage(const std::wstring &code_param, TypeOfCode code_type);
};

#endif //LINEARCODES_CONTROLLER_H
