#ifndef LINEARCODES_FACTORY_H
#define LINEARCODES_FACTORY_H

#include "encoder.h"
#include "decoder.h"
#include "ui.h"
#include <vector>

class Controller;

class Factory {
private:
    std::vector<Encoder *> encoders;
    std::vector<Decoder *> decoders;
    UI *ui;

    TypeOfUserInterface ui_type;

    void AddEncoder(TypeOfCode code_type);

    void AddDecoder(TypeOfCode code_type);

public:
    explicit Factory(TypeOfUserInterface ui_param_type);

    UI *GetUserInterface(Controller *controller);

    Encoder *GetEncoder(TypeOfCode code_type);

    Decoder *GetDecoder(TypeOfCode code_type);
};

#endif //LINEARCODES_FACTORY_H
