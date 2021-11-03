#ifndef LINEARCODES_CLI_H
#define LINEARCODES_CLI_H

#include "ui.h"
#include "../code/code.h"
#include <memory>

class Controller;

class CLI : public UI {
private:

    std::shared_ptr<Controller> controller;

    bool GetChoiceResult(int lower_bound, int upper_bound, int &choice);

    static bool IsCodeCorrect(std::wstring &message);

    std::wstring ReadCodeString();

    static Code GetCodeFromString(std::wstring &message, TypeOfCode &code_type, size_t code_block_size);

    Code ReadCode(TypeOfCode &code_type, size_t code_block_size);

    void Encode();

    void Decode();

public:

    explicit CLI(std::shared_ptr<Controller> controller_param);

    void PrintMessage(const std::wstring &message) override;

    std::wstring ReadMessage() override;

    void Start() override;
};

#endif //LINEARCODES_CLI_H
