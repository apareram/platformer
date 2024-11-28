#include "engine/Core.h"
#include <iostream>

int main() {
    try {
        Core core;
        core.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}