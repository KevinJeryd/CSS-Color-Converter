#ifndef COLOR_CONVERTER_H
#define COLOR_CONVERTER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>

class ColorConverter {
    private:
        static std::vector<std::string> openFile(const std::string& fileName);
        static std::vector<std::string> parseColors(const std::vector<std::string>& cssFile);
        static void hexToRbg(const std::vector<std::string>& colors);
        static std::vector<float> hexToRgb3Dig(const std::string& color);
        static std::vector<float> hexToRgb6Dig(const std::string& color);
    public:
        static int convertFile(const std::string& fileName);
};

#endif