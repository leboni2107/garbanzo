#include "../include/Arguments.h"

#include <string>


Arguments::Arguments(int argc, char *argv[]) {
    int argvLength = sizeof(argv) / sizeof(argv[0]);

    if (argvLength > 1) {
        for (int i = 0; i < argc; i++) {
            if (argv[i] == std::string("-h") || argv[i] == std::string("--help"))
                help = true;
            else if (argv[i] == std::string("-r") || argv[i] == std::string("--recursion"))
                recursion = true;
        }
    }
}
