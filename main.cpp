#include <cstring>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>

#include "include/Arguments.h"

using namespace std;

/**
 * Return values Directory, Search (if found)
 * @return
 */
tuple<optional<string>, optional<string>> getInput(int argc, char* argv[]) {
    string search = "", dir;

    for (int i = 1; i < argc; i++) {
        switch (argv[i][0]) {
            case '@': // search input
                for (int j = 1; argv[i][j] != '\0'; j++) { // Start at j=1 for "
                    search += argv[i][j];
                }
                break;
            case '-': // Flag
                continue;
            default: // Potential directory
                if (strchr(argv[i], '.') || strchr(argv[i], '/')) {
                    dir = argv[i];
                }
                break;
        }
    }
    return make_tuple(search, dir);
}

void printHelp() {
    cout << "Usage: @[SEARCH] [DIRECTORY] [OPTIONS] (Not in a specific order!)"
            "\n   or: [-h, --help]"
            "\nSearch for a string within files in a directory"
            "\n"
            "\nArguments:"
            "\n-h      --help          Display help message (this!)"
            "\n-h      --recursion     Search recursively through subdirectories"
            "\n"
            "\nExample Usage: ./garbanzo @ninja /../Testing/ --recursion"
            "\n               ./garbanzo --help"
            "\n               ./garbanzo --recursion @ninja ninja.txt"
    << endl;
}

void printVersion() {
    cout << "Garbanzo 0.1" << endl;
}

/**
 *
 * @param search String to search
 * @param dir Directory to search in (can be a file)
 * @return
 */
int workArguments(Arguments arguments, optional<string> search, optional<string> dir) {
    int amount = 0;

    if (arguments.help) {
        printHelp();
    } else if (arguments.version) {
        printVersion();
    } else if (search && dir) {
        amount = 1;
    }

    return amount;
}

int main(int argc, char* argv[]) {
    Arguments arguments(argc, argv);
    auto [search, dir] = getInput(argc, argv);

    int amount = workArguments(arguments, search, dir);

    cout << "Search: " << search.value_or("(none)") << endl;
    cout << "Directory: " << dir.value_or("(none)") << endl;

    cout << "Amount: " << amount << endl;
}
