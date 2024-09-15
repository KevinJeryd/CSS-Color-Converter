#include "ColorConverter.h"

int ColorConverter::convertFile(const std::string& fileName) {
    std::vector<std::string> cssFile = openFile(fileName);

    if (cssFile.empty()) {
        return 1;
    }

    std::vector<std::string> newFile = parseColors(cssFile);
    writeContent(newFile, fileName);

    return 0; 
}

std::vector<std::string> ColorConverter::openFile(const std::string& fileName) {
    std::vector<std::string> cssData;
    std::fstream cssFile;
    std::string data;

    cssFile.open(fileName);

    if (!cssFile.is_open()) {
        return std::vector<std::string>{};
    }

    while (std::getline(cssFile, data)) {
        cssData.push_back(data);
    }

    cssFile.close();
    return cssData;
}

std::vector<std::string> ColorConverter::parseColors(std::vector<std::string>& cssFile) {
    int i = 0;

    for (auto line : cssFile) {
        size_t findHash = line.find("#");
        if (findHash != std::string::npos) {
            size_t findSemicol = line.find(";");
            if (findSemicol != std::string::npos) {
                std::string hex = line.substr(findHash+1, findSemicol-findHash-1);
                std::string rgb = hexToRbg(hex);
                line.replace(findHash, hex.size()+2, hexToRbg(hex));
                cssFile[i] = line;
            }
        }
        i++;
    }

    return cssFile;
}


std::string ColorConverter::hexToRbg(const std::string& color) {
    if (color.size() == 3 || color.size() == 4) { // For notations that repeat nums, 123 becomes 112233, 1234 becomes 11223344
        return hexToRgb3Dig(color).str();
    } else {
        return hexToRgb6Dig(color).str();
    }
}

std::stringstream ColorConverter::hexToRgb3Dig(const std::string& color) {
    std::stringstream decStream;
    if (color.size() == 3) {
        decStream << "RGB(";
    } else {
        decStream << "RGBA(";
    }

    for (int i = 0; i < color.size(); i++) {
        std::stringstream hexStream;
        unsigned int x;

        hexStream << std::hex << color[i] << color[i];
        hexStream >> x;

        if (i == 3) { // If alpha channel
            decStream << std::to_string((float) x/255); // Alpha channel, goes between 0 and 1 so need to div by 255
        } else {
            if (i == color.size() - 1) { // Don't want the num to have "," behind it
                decStream << std::to_string(x); 
            } else {
                decStream << std::to_string(x) << ", ";
            }
        }
    }
    
    decStream << ");";

    return decStream;
}

std::stringstream ColorConverter::hexToRgb6Dig(const std::string& color) {
    std::stringstream decStream;

    if (color.size() == 6) {
        decStream << "RGB(";
    } else {
        decStream << "RGBA(";
    }

    for (int i = 0; i < color.size(); i += 2) {
        std::stringstream ss;
        unsigned int x;

        ss << std::hex << color.substr(i, 2);
        ss >> x;

        if (i == 6) { // If alpha channel
            decStream << std::to_string((float) x/255); // Alpha channel, goes between 0 and 1 so need to div by 255
        } else {
            if (i == color.size() - 2) { // Don't want the num to have "," behind it
                decStream << std::to_string(x);
            } else {
                decStream << std::to_string(x) << ", ";
            }
        }
    }

    decStream << ");";

    return decStream;
}

void ColorConverter::writeContent(const std::vector<std::string>& newFile, const std::string& fileName) {
    std::ofstream file;
    file.open(fileName);

    for (auto line : newFile) {
        file << line << "\n";
    }

    file.close();
}