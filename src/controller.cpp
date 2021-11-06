#include "controller.h"

Controller::Controller(std::shared_ptr<Factory> factory_param) {
    factory = std::move(factory_param);
}

void Controller::Work() {
    factory->GetUserInterface(std::make_shared<Controller>(*this))->Start();
}

bool Controller::IsCodeCorrect(const std::wstring &code_param, TypeOfCode code_type) {
    return factory->GetCode(code_type)->IsCodeCorrect(code_param);
}

std::wstring Controller::EncodeMessage(const std::wstring &code_param, TypeOfCode code_type) {
    return factory->GetEncoder(code_type)->Encode(code_param);
}

std::pair<std::wstring, bool> Controller::DecodeMessage(const std::wstring &code_param, TypeOfCode code_type) {
    return factory->GetDecoder(code_type)->Decode(code_param);
}
