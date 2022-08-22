#include "Colors.h"

std::ostream& operator<<(std::ostream& os, const Color::Code color) {
    std::string myGenerat = "\033[";
    myGenerat += std::to_string((int)color) + "m";
    os << myGenerat;
    return os;
}