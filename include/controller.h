#ifndef LINEARCODES_CONTROLLER_H
#define LINEARCODES_CONTROLLER_H

#include "factory.h"
#include "statistics.h"
#include "ui.h"

class Controller {
private:
    Factory *factory;
    UI *ui;
public:
    Controller(Factory *factory_param);

    void Work();

    void EncodeMessage(Code &code_param);

    int DecodeMessage(Code &code_param);

    std::vector<Stats> GetStats(Code &code_param);
};

#endif //LINEARCODES_CONTROLLER_H
