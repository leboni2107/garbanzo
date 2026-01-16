#include <string>
#include <optional>
#include <filesystem>
#include <fstream>

#include "Arguments.h"
#pragma once

using namespace std;

class File {
public:
    string path;
    optional<string> name;
    optional<string> content;

    File(string path, Arguments arguments);

    int readFileName(string search, Arguments arguments);
    int readFileContent(string search, Arguments arguments);
};
