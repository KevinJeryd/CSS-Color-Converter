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
        static std::vector<std::string> parseColors(std::vector<std::string>& cssFile);
        static std::string hexToRbg(const std::string& colors);
        static std::stringstream hexToRgb3Dig(const std::string& color);
        static std::stringstream hexToRgb6Dig(const std::string& color);
        static void writeContent(const std::vector<std::string>& newFile, const std::string& fileName);
    public:
        static int convertFile(const std::string& fileName);
};

#endif