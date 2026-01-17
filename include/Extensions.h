#include <string>
#include <vector>

#pragma once

class Extensions {
public:
    enum Mode { Exclude, Include }; // Whether extensions in the vector will only be read or not be read

    std::vector<std::string> extensions;
    Mode mode;

    bool extension_help = false;
    bool extension_sensitive = false;

    void readExtensions(std::string argument);
    std::string extractExtension(std::string fileName);
    bool isLegalExtension(std::string extension);
};
