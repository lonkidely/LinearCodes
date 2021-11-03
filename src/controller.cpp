#include "../include/controller.h"

Controller::Controller(std::shared_ptr<Factory> factory_param) {
    factory = std::move(factory_param);
}

void Controller::Work() {
    factory->GetUserInterface(std::make_shared<Controller>(*this))->Start();
}

Code Controller::EncodeMessage(Code &code_param) {
    return factory->GetEncoder(code_param.GetCodeType())->Encode(code_param);
}

std::pair<Code, bool> Controller::DecodeMessage(Code &code_param) {
    return factory->GetDecoder(code_param.GetCodeType())->Decode(code_param);
}
