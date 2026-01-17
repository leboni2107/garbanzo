#include "../include/Extensions.h"
#include <sstream>

void Extensions::readExtensions(std::string argument) {
    if (argument.empty())
        return;

    std::stringstream ss(argument);
    std::string modeStr;

    ss >> modeStr;

    if (modeStr.empty())
        return;

    char modeChar = modeStr[0];
    if (modeChar == 'E' || modeChar == 'e') {
        mode = Mode::Exclude;
    } else if (modeChar == 'I' || modeChar == 'i') {
        mode = Mode::Include;
    } else {
        return;
    }

    std::string remaining;
    std::getline(ss, remaining);

    std::stringstream extStream(remaining);
    std::string token;

    while (std::getline(extStream, token, ',')) {
        size_t start = token.find_first_not_of(" \t");
        size_t end = token.find_last_not_of(" \t");

        if (start != std::string::npos) {
            token = token.substr(start, end - start + 1);
            if (!token.empty()) {
                extensions.push_back(token);
            }
        }
    }

    if (extensions.empty()) {
        extStream.clear();
        extStream.str(remaining);
        while (extStream >> token) {
            if (!token.empty()) {
                extensions.push_back(token);
            }
        }
    }
}

std::string Extensions::extractExtension(std::string fileName) {
    size_t dotPos = fileName.find_last_of('.');

    if (dotPos == std::string::npos || dotPos == 0) {
        return "";
    }

    size_t slashPos = fileName.find_last_of("/\\");
    if (slashPos != std::string::npos && slashPos > dotPos) {
        return "";
    }

    return fileName.substr(dotPos);
}

bool Extensions::isLegalExtension(std::string extension) {
    if (!extension_sensitive) {
        return true;
    }

    bool found = std::find(extensions.begin(), extensions.end(), extension) != extensions.end();

    if (mode == Mode::Exclude)
        return !found;
    return found;
}
