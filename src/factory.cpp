#include "../include/factory.h"
#include "../include/cli.h"
#include "../include/hamming_decoder.h"
#include "../include/hamming_encoder.h"
#include "../include/cyclic_decoder.h"
#include "../include/cyclic_encoder.h"


Factory::Factory(TypeOfUserInterface ui_type_param) {
    encoders = std::vector<Encoder *>();
    decoders = std::vector<Decoder *>();
    ui_type = ui_type_param;
    ui = nullptr;
}


UI *Factory::GetUserInterface(Controller *controller) {
    if (ui_type == kCLI) {
        if (ui == nullptr) {
            ui = new CLI(controller);
        }
    } else {
        if (ui == nullptr) {
            //ui = new GUI(controller);
        }
    }
    return ui;
}

void Factory::AddEncoder(TypeOfCode code_type) {
    if (code_type == TypeOfCode::kHamming) {
        encoders.push_back(new HammingEncoder());
    } else {
        encoders.push_back(new CyclicEncoder());
    }
}

Encoder *Factory::GetEncoder(TypeOfCode code_type) {
    auto iter = encoders.begin();
    while (iter != encoders.end()) {
        if ((*iter)->GetType() == code_type)
            return *iter;
    }
    AddEncoder(code_type);
    return encoders.back();
}

void Factory::AddDecoder(TypeOfCode code_type) {
    if (code_type == TypeOfCode::kHamming) {
        decoders.push_back(new HammingDecoder());
    } else {
        decoders.push_back(new CyclicDecoder());
    }
}

Decoder *Factory::GetDecoder(TypeOfCode code_type) {
    auto iter = decoders.begin();
    while (iter != decoders.end()) {
        if ((*iter)->GetType() == code_type)
            return *iter;
    }
    AddDecoder(code_type);
    return decoders.back();
}
