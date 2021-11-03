#ifndef LINEARCODES_FACTORY_H
#define LINEARCODES_FACTORY_H

#include "encoder.h"
#include "decoder.h"
#include "ui.h"
#include <vector>
#include <memory>

class Controller;

class Factory {
private:
    std::vector<std::shared_ptr<Encoder>> encoders;
    std::vector<std::shared_ptr<Decoder>> decoders;
    std::shared_ptr<UI> ui;

    TypeOfUserInterface ui_type;

    void AddEncoder(TypeOfCode code_type);

    void AddDecoder(TypeOfCode code_type);

public:
    explicit Factory(TypeOfUserInterface ui_param_type);

    std::shared_ptr<UI> GetUserInterface(std::shared_ptr<Controller> controller);

    std::shared_ptr<Encoder> GetEncoder(TypeOfCode code_type);

    std::shared_ptr<Decoder> GetDecoder(TypeOfCode code_type);
};

#endif //LINEARCODES_FACTORY_H
