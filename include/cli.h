#ifndef LINEARCODES_CLI_H
#define LINEARCODES_CLI_H

#include "ui.h"
#include <string>

class Controller;

class CLI : public UI {
private:
    std::wstring input_message;
    Controller *controller;

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
