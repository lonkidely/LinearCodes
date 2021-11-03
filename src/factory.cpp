#include "factory.h"
#include "ui/cli.h"
#include "decoders/hamming_decoder.h"
#include "encoders/hamming_encoder.h"
#include "decoders/cyclic_decoder.h"
#include "encoders/cyclic_encoder.h"


Factory::Factory(TypeOfUserInterface ui_type_param) {
    encoders = std::vector<std::shared_ptr<Encoder>>();
    decoders = std::vector<std::shared_ptr<Decoder>>();
    ui_type = ui_type_param;
    ui = nullptr;
}

std::shared_ptr<UI> Factory::GetUserInterface(std::shared_ptr<Controller> controller) {
    if (ui_type == kCLI) {
        if (ui == nullptr) {
            ui = std::make_shared<CLI>(CLI(std::move(controller)));
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
        encoders.push_back(std::make_shared<HammingEncoder>());
    } else {
        encoders.push_back(std::make_shared<CyclicEncoder>());
    }
}

std::shared_ptr<Encoder> Factory::GetEncoder(TypeOfCode code_type) {
    for (auto &encoder: encoders) {
        if (encoder->GetType() == code_type)
            return encoder;
    }
    AddEncoder(code_type);
    return encoders.back();
}

void Factory::AddDecoder(TypeOfCode code_type) {
    if (code_type == TypeOfCode::kHamming) {
        decoders.push_back(std::make_shared<HammingDecoder>());
    } else {
        decoders.push_back(std::make_shared<CyclicDecoder>());
    }
}

std::shared_ptr<Decoder> Factory::GetDecoder(TypeOfCode code_type) {
    for (auto &decoder: decoders) {
        if (decoder->GetType() == code_type)
            return decoder;
    }
    AddDecoder(code_type);
    return decoders.back();
}
