#include "factory.h"
#include "ui/cli.h"
#include "decoders/hamming_decoder.h"
#include "encoders/hamming_encoder.h"
#include "decoders/cyclic_decoder.h"
#include "encoders/cyclic_encoder.h"
#include "code/hamming_code.h"
#include "code/cyclic_code.h"

Factory::Factory(TypeOfUserInterface ui_type_param) {
    codes = std::vector<std::shared_ptr<Code>>();
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

void Factory::AddCode(TypeOfCode code_type) {
    switch (code_type) {
        case TypeOfCode::kHamming:
            codes.push_back(std::make_shared<HammingCode>());
            break;
        case TypeOfCode::kCyclicCode:
            codes.push_back(std::make_shared<CyclicCode>());
            break;
    }
}

std::shared_ptr<Code> Factory::GetCode(TypeOfCode code_type) {
    for (auto &code: codes) {
        if (code->GetCodeType() == code_type)
            return code;
    }
    AddCode(code_type);
    return codes.back();
}

void Factory::AddEncoder(TypeOfCode code_type) {
    switch (code_type) {
        case TypeOfCode::kHamming:
            encoders.push_back(std::make_shared<HammingEncoder>());
            break;
        case TypeOfCode::kCyclicCode:
            encoders.push_back(std::make_shared<CyclicEncoder>());
            break;
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
    switch (code_type) {
        case TypeOfCode::kHamming:
            decoders.push_back(std::make_shared<HammingDecoder>());
            break;
        case TypeOfCode::kCyclicCode:
            decoders.push_back(std::make_shared<CyclicDecoder>());
            break;
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
