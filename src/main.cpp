#include "../include/controller.h"

int main() {

    setlocale(LC_ALL, "ru_RU.UTF8");

    auto *factory = new Factory(kCLI);
    Controller controller(factory);
    controller.Work();

    return 0;
}
