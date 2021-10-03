#ifndef LINEARCODES_FACTORY_H
#define LINEARCODES_FACTORY_H

#include "encoder.h"
#include "decoder.h"
#include "hamming_encoder.h"
#include "hamming_decoder.h"
#include "ui.h"
#include "cli.h"
#include "statistics.h"

class Factory {
private:
    Encoder **encoders;
    Decoder **decoders;
    Statistics *statistics;
    UI *ui;

    TypeOfUserInterface ui_type;
    int encoders_size;
    int encoders_count;
    int decoders_size;
    int decoders_count;

    void ExpandEncoders();

    void ExpandDecoders();

    void AddEncoder(TypeOfCode code_type);

    void AddDecoder(TypeOfCode code_type);

public:
    Factory(TypeOfUserInterface);

    UI *GetUserInterface(Controller *controller);

    Encoder *GetEncoder(TypeOfCode code_type);

    Decoder *GetDecoder(TypeOfCode code_type);

    Statistics *GetStatistics();
};

#endif //LINEARCODES_FACTORY_H
