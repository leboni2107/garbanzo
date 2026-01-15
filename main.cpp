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

    for (int i = 1; i < argc; i++) { // Start at 1 for program name
        if (argv[i][0] == '"') { // Start of search input

            for (int j = 0; argv[i][j] != '\0'; j++) { // Copy true input into search
                if (argv[i][j] != '"')
                    search += argv[i][j];
            }
        }
    }

    return make_tuple(search, dir);
}

void printHelp() {

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
    }
    else if (search && dir) {

    }

    return amount;
}

int main(int argc, char* argv[]) {
    Arguments arguments(argc, argv);
    auto [dir, search] = getInput(argc, argv);

    int amount = workArguments(arguments, search, dir);

    cout << "Amount: " << amount << endl;
}
