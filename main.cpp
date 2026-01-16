#include <cstring>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>

#include "include/Arguments.h"
#include "include/File.h"

using namespace std;
2
#pragma region Menus
void printHelp() {
    cout << "Usage: @[SEARCH] [DIRECTORY, FILE] [OPTIONS] (Not in a specific order!)"
            "\n   or: [-h, --help]"
            "\nSearch for a string within files in a directory"
            "\n"
            "\nArguments:"
            "\n-h      --help               Display help message (this!)"
            "\n-v      --version            Display version message"
            "\n-h      --recursion          Search recursively through subdirectories"
            "\n-c      --no-file-content    Doesn't read file content"
            "\n-n      --no-file-name       Doesn't read file names"
            "\n"
            "\nExample Usage: ./garbanzo @ninja /../Testing/ --recursion"
            "\n               ./garbanzo --help"
            "\n               ./garbanzo --recursion @ninja ninja.txt"
    << endl;
}

void printVersion() {
    cout << "Garbanzo 0.1"
    << endl;
}
#pragma endregion Menus

tuple<optional<string>, optional<string>> getInput(int argc, char* argv[]) {
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
                if (strchr(argv[i], '.') || strchr(argv[i], '/')) {
                    dir = argv[i];
                }
                break;
        }
    }
    return make_tuple(search, dir);
}

int workArguments(Arguments arguments, optional<string> search, optional<string> dir) {
    int amount = 0;

    if (arguments.help) {
        printHelp();
    } else if (arguments.version) {
        printVersion();
    } else if (search.has_value() && dir.has_value()) {
        File inputFile(dir.value(), arguments);
        amount += inputFile.readFileContent(search.value(), arguments);
        amount += inputFile.readFileName(search.value(), arguments);
    }

    return amount;
}

int main(int argc, char* argv[]) {
    Arguments arguments(argc, argv);
    auto [search, dir] = getInput(argc, argv);
    int amount = workArguments(arguments, search, dir);
    cout << "Amount: " << amount << endl;
    exit(amount);
}
