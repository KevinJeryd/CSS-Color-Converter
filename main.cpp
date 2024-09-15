#include <iostream> 
#include <string>

#include "include/ColorConverter.h"

int main() {
    std::string filePath = "../../color-convert/advanced.css";
    int res = ColorConverter::convertFile(filePath);
    return 0;
}