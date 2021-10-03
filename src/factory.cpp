#include "../include/factory.h"

Factory::Factory(TypeOfUserInterface ui_type_param) {
    encoders_count = 0;
    encoders_size = 1;
    encoders = new Encoder *[encoders_size];

    decoders_count = 0;
    decoders_size = 1;
    decoders = new Decoder *[decoders_size];

    ui_type = ui_type_param;
}


UI *Factory::GetUserInterface(Controller *controller) {
    switch (ui_type) {
        case kCLI:
            ui = new CLI(controller);
            break;
        default:

            break;
    }
    return ui;
}

void Factory::ExpandEncoders() {
    Encoder **new_encoders = new Encoder *[2 * encoders_size];
    for (int i = 0; i < encoders_size; ++i) {
        new_encoders[i] = encoders[i];
    }
    delete[] encoders;
    encoders = new_encoders;
    encoders_size *= 2;
}

void Factory::AddEncoder(TypeOfCode code_type) {
    if (encoders_size == encoders_count)
        ExpandEncoders();
    switch (code_type) {
        case kHamming:
            encoders[encoders_count] = new HammingEncoder();
            break;
        default:

            break;
    }
    encoders_count++;
}

Encoder *Factory::GetEncoder(TypeOfCode code_type) {
    int index_of_encoder = -1;
    if (encoders_count > 0) {
        for (int i = 0; i < encoders_count; ++i) {
            if (encoders[i]->GetType() == code_type) {
                index_of_encoder = i;
                break;
            }
        }
    }
    if (index_of_encoder != -1)
        return encoders[index_of_encoder];

    AddEncoder(code_type);

    return encoders[encoders_count - 1];
}

void Factory::ExpandDecoders() {
    Decoder **new_decoders = new Decoder *[2 * decoders_size];
    for (int i = 0; i < decoders_size; ++i) {
        new_decoders[i] = decoders[i];
    }
    delete[] decoders;
    decoders = new_decoders;
    decoders_size *= 2;
}

void Factory::AddDecoder(TypeOfCode code_type) {
    if (decoders_size == decoders_count)
        ExpandDecoders();
    switch (code_type) {
        case kHamming:
            decoders[decoders_count] = new HammingDecoder();
            break;
        default:

            break;
    }
    decoders_count++;
}

Decoder *Factory::GetDecoder(TypeOfCode code_type) {
    int index_of_decoder = -1;
    if (decoders_count > 0) {
        for (int i = 0; i < decoders_count; ++i) {
            if (decoders[i]->GetType() == code_type) {
                index_of_decoder = i;
                break;
            }
        }
    }
    if (index_of_decoder != -1)
        return decoders[index_of_decoder];

    AddDecoder(code_type);

    return decoders[decoders_count - 1];
}

Statistics *Factory::GetStatistics() {
    if (statistics == nullptr){
        statistics = new Statistics();
    }
    return statistics;
}