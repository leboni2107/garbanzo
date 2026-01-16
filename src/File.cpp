#include "../include/File.h"

using namespace std;

File::File(string path, Arguments arguments) {
    if (arguments.file_name)
        name = filesystem::path(path).filename().string();

    if (arguments.file_content) {
        ifstream file(path);
        if (file) {
            string line;
            string fullContent;
            while (getline(file, line))
                fullContent += line + "\n";
            content = fullContent;
        }
    }
}

int File::readFileName(string search, Arguments arguments) {
    if (!name.has_value() || !arguments.file_name)
        return 0;

    int amount = 0;
    string curName = name.value();

    if (search.length() > curName.length())
        return 0;

    for (int i = 0; i <= (int)(curName.length() - search.length()); i++) {
        if (search == curName.substr(i, search.length()))
            amount++;
    }

    return amount;
}

int File::readFileContent(string search, Arguments arguments) {
    if (!content.has_value() || !arguments.file_content)
        return 0;

    int amount = 0;
    string curContent = content.value();

    if (search.length() > curContent.length())
        return 0;

    for (int i = 0; i <= (int)(curContent.length() - search.length()); i++) {
        if (search == curContent.substr(i, search.length()))
            amount++;
    }

    return amount;
}
