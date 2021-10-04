#include "../include/controller.h"

Controller::Controller(Factory *factory_param) {
    factory = factory_param;
}

void Controller::Work() {
    factory->GetUserInterface(this)->Start();
}

void Controller::EncodeMessage(Code &code_param) {
    factory->GetEncoder(code_param.GetCodeType())->Encode(code_param);
}

int Controller::DecodeMessage(Code &code_param) {
    return factory->GetDecoder(code_param.GetCodeType())->Decode(code_param);
}

std::vector<Stats> Controller::GetStats(Code &code_param) {
    return factory->GetStatistics()->GetStats(
            code_param,
            factory->GetEncoder(code_param.GetCodeType()),
            factory->GetDecoder(code_param.GetCodeType())
            );
}