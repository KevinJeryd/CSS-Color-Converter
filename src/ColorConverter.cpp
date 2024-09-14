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
    std::vector<std::vector<int>> res;
    for (auto color : colors) {
        std::cout << color << std::endl;
        switch (color.size())
        {
        case 3:

            break;
        case 4:

            break;
        case 8:

            break;
        default:
            std::vector<int> rgb;
            for (int i = 0; i < color.size(); i += 2) {
                std::stringstream ss;
                unsigned int x;

                ss << std::hex << color.substr(i, 2);
                ss >> x;

                rgb.push_back(x);
            }

            res.push_back(rgb);
            break;
        }
    }

    for (auto rgb : res) {
        for (auto num : rgb) {
            std::cout << num << " ";
        }

        std::cout << std::endl;
    }
}