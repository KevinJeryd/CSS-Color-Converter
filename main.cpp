#include <iostream> 
#include <string>

#include "include/ColorConverter.h"

int main() {
    std::cout << "Hello :)" << std::endl;
    std::string filePath = "../../color-convert/simple.css";

    int res = ColorConverter::convertFile(filePath);

    return 0;
}