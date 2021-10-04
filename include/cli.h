#ifndef LINEARCODES_CLI_H
#define LINEARCODES_CLI_H

#include "ui.h"
#include <string>

class Controller;

class CLI : public UI {
private:
    static const int kMaxLengthCodeForStats = 11;

    std::wstring input_message;
    Controller *controller;

    void Encode();

    void Decode();

    void GetStatistic();

    bool IsCodeCorrect(std::wstring &message);

    void ReadCode(std::wstring &message);

public:

    CLI(Controller *controller_param);

    void PrintMessage(std::wstring message) override;

    std::wstring ReadMessage() override;

    void Start() override;
};

#endif //LINEARCODES_CLI_H
