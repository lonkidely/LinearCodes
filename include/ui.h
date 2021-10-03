#ifndef LINEARCODES_UI_H
#define LINEARCODES_UI_H

#include <string>

enum TypeOfUserInterface : int {
    kCLI,
    kGUI
};

class UI {
public:
    virtual void PrintMessage(std::wstring message) = 0;

    virtual std::wstring ReadMessage() = 0;

    virtual void Start() = 0;

    virtual ~UI() {}
};

#endif //LINEARCODES_UI_H
