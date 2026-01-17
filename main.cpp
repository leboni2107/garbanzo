#include <cstring>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>
#include <filesystem>

#include "include/Arguments.h"
#include "include/File.h"
#include "include/TaskPooler.h"

using namespace std;

#pragma region Menus
void printHelp() {
    cout << "Usage: @[SEARCH] [DIRECTORY, FILE] [OPTIONS] (Not in a specific order!)"
            "\n   or: [-h, --help]"
            "\nSearch for a string within files in a directory"
            "\n"
            "\nArguments:"
            "\n-h      --help                Display help message (this!)"
            "\n-v      --version             Display version message"
            "\n-h      --recursion           Search recursively through subdirectories"
            "\n-c      --no-file-content     Doesn't read file content"
            "\n-n      --no-file-name        Doesn't read file names"
            "\n-i      --ignore-case         Disable case-sensitive search"
            "\n-e      --extension-sensitive Enable extension sensitive reading. More help with --extension-help"
            "\n"
            "\nExample Usage: ./garbanzo @ninja ../Testing/ --recursion"
            "\n               ./garbanzo --help"
            "\n               ./garbanzo --recursion @ninja ninja.txt"
    << endl;
}

void printExtensionHelp() {
    cout << "Usage: --extension-sensitive [MODE] [EXTENSIONS]"
            "\n   or: -e [MODE] [EXTENSIONS]"
            "\n"
            "\nMode: E: ignores given extensions"
            "\n      I: only reads given extensions"
            "\n"
            "\nExtension Syntax: Seperated by ','. Space isnt needed"
            "\nExample:          .sh, .cpp,.txt"
            "\n"
            "\nExample Usage: ./garbanzo @ninja ../Testing/ --extension-sensitive E .sh     Ignores shell files, only"
            "                                                                               reads other files"
    << endl;
}

void printVersion() {
    cout << "Garbanzo 0.1"
    << endl;
}
#pragma endregion Menus

vector<string> collectFilePaths(string dir, Arguments arguments) {
    vector<string> filePaths;

    try {
        filesystem::path fsPath(dir);

        if (!filesystem::exists(fsPath)) {
            cerr << "Filesystem error: Path does not exist" << endl;
            return filePaths;
        }

        if (filesystem::is_regular_file(fsPath)) {
            string ext = arguments.extensions.extractExtension(fsPath.string());
            if (arguments.extensions.isLegalExtension(ext)) {
                filePaths.push_back(dir);
            }
        } else if (filesystem::is_directory(fsPath)) {
            if (arguments.recursion) {
                for (const auto& entry : filesystem::recursive_directory_iterator(fsPath)) {
                    if (entry.is_regular_file()) {
                        string ext = arguments.extensions.extractExtension(entry.path().string());
                        if (arguments.extensions.isLegalExtension(ext)) {
                            filePaths.push_back(entry.path().string());
                        }
                    }
                }
            } else {
                for (const auto& entry : filesystem::directory_iterator(fsPath)) {
                    if (entry.is_regular_file()) {
                        string ext = arguments.extensions.extractExtension(entry.path().string());
                        if (arguments.extensions.isLegalExtension(ext)) {
                            filePaths.push_back(entry.path().string());
                        }
                    }
                }
            }
        }

    } catch (const filesystem::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << endl;
    }

    return filePaths;
}

tuple<optional<string>, optional<string>> splitInput(int argc, char* argv[]) {
    string search = "", dir;

    for (int i = 1; i < argc; i++) {
        switch (argv[i][0]) {
            case '@':           // search input
                for (int j = 1; argv[i][j] != '\0'; j++) { // Start at j=1 for @
                    search += argv[i][j];
                }
                break;
            case '-':           // Flag
                continue;
            default:            // Potential dir input
                if ((strchr(argv[i], '/') != nullptr) ||
                    (argv[i][0] == '.' && argv[i][1] == '.')) {
                    dir = argv[i];
                    }
                break;
        }
    }
    return make_tuple(search, dir);
}

int workArguments(Arguments arguments, optional<string> search, optional<string> dir) {
    int amount = 0;

    if (arguments.help)
        printHelp();

    if (arguments.version)
        printVersion();

    if (arguments.extensions.extension_help)
        printExtensionHelp();

    if (search.has_value() && dir.has_value()) {
        auto filePaths = collectFilePaths(dir.value(), arguments);

        if (!arguments.case_sensitive) {
            std::transform(search.value().begin(), search.value().end(),
                           search.value().begin(),
                           [](unsigned char c){ return std::tolower(c); });
        }

        for (int i = 0; i < filePaths.size(); i++) {
            File currentFile(filePaths[i], arguments);

            amount += currentFile.readFileContent(search.value(), arguments);
            amount += currentFile.readFileName(search.value(), arguments);
        }
    }

    return amount;
}

int main(int argc, char* argv[]) {
    Arguments arguments(argc, argv);
    auto [search, dir] = splitInput(argc, argv);
    int amount = workArguments(arguments, search, dir);

    cout << amount << endl;

    exit(amount);
}
