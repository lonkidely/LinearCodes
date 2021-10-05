#ifndef LINEARCODES_CLI_H
#define LINEARCODES_CLI_H

#include "ui.h"
#include "code.h"

class Controller;

class CLI : public UI {
private:
    static const int kMaxLengthCodeForStats = 11;

    Controller *controller;

    bool GetChoiceResult(int lower_bound, int upper_bound, int &choice);

    bool IsCodeCorrect(std::wstring &message);

    std::wstring ReadCodeString();

    Code GetCodeFromString(std::wstring &message, TypeOfCode &code_type);

    Code ReadCode(TypeOfCode &code_type);

    void Encode();

    void Decode();

    void GetStatistic();


public:

    CLI(Controller *controller_param);

    void PrintMessage(std::wstring message) override;

    std::wstring ReadMessage() override;

    void Start() override;
};

#endif //LINEARCODES_CLI_H
