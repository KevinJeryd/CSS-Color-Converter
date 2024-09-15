#include "ColorConverter.h"

int ColorConverter::convertFile(const std::string& fileName) {

    std::vector<std::string> cssData = openFile(fileName);

    if (cssData.empty()) {
        return 1;
    }

    std::vector<std::string> colors = parseColors(cssData);
    hexToRbg(colors);
    return 0;
}

std::vector<std::string> ColorConverter::openFile(const std::string& fileName) {
    std::vector<std::string> cssData;
    std::fstream cssFile;

    cssFile.open(fileName);

    if (!cssFile.is_open()) {
        return std::vector<std::string>{};
    }

    std::string data;

    while (std::getline(cssFile, data)) {
        cssData.push_back(data);
    }

    cssFile.close();
    return cssData;
}

std::vector<std::string> ColorConverter::parseColors(const std::vector<std::string>& cssFile) {
    std::vector<std::string> colorHex;

    for (auto line : cssFile) {
        size_t findHash = line.find("#");
        if (findHash != std::string::npos) {
            size_t findSemicol = line.find(";");
            if (findSemicol != std::string::npos) {
                std::string hex = line.substr(findHash+1, findSemicol-findHash-1);
                colorHex.push_back(hex);
            }
        }
    }

    return colorHex;
}


void ColorConverter::hexToRbg(const std::vector<std::string>& colors) {
    std::vector<std::vector<float>> res;
    for (auto color : colors) {
        if (color.size() == 3 || color.size() == 4) { // For notations that repeat nums, 123 becomes 112233, 1234 becomes 11223344
            res.push_back(hexToRgb3Dig(color));
        } else {
            res.push_back(hexToRgb6Dig(color));
        }
    }
}

std::vector<float> ColorConverter::hexToRgb3Dig(const std::string& color) {
    std::vector<float> rgb;
    
    for (int i = 0; i < color.size(); i++) {
        std::stringstream ss;
        unsigned int x;

        ss << std::hex << color[i] << color[i];
        ss >> x;

        if (i == 3) { // If alpha channel
            rgb.push_back((float) x/255); // Alpha channel, goes between 0 and 1 so need to div by 255
        } else {
            rgb.push_back(x);
        }
    }

    return rgb;
}

std::vector<float> ColorConverter::hexToRgb6Dig(const std::string& color) {
    std::vector<float> rgb;
    for (int i = 0; i < color.size(); i += 2) {
        std::stringstream ss;
        unsigned int x;

        ss << std::hex << color.substr(i, 2);
        ss >> x;

        if (i == 6) { // If alpha channel
            rgb.push_back((float) x/255); // Alpha channel, goes between 0 and 1 so need to div by 255
        } else {
            rgb.push_back(x);
        }
    }

    return rgb;
}