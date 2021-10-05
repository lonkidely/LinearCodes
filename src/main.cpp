#include <iostream>
#include <io.h>
#include <fcntl.h>

#include "../include/controller.h"

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    Factory *factory = new Factory(kCLI);
    Controller controller(factory);
    controller.Work();

    return 0;
}
