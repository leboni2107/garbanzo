#include "../include/Arguments.h"
#include <string>
#include <unordered_map>

using namespace std;

Arguments::Arguments(int argc, char *argv[]) {
    if (argc > 1) {
        unordered_map<string, int> optionMap = {
            {"-h", 1}, {"--help", 1},
            {"-v", 2}, {"--version", 2},
            {"-r", 3}, {"--recursion", 3}
        };


        for (int i = 0; i < argc; i++) {
            auto it = optionMap.find(argv[i]);

            if (it != optionMap.end()) {
                switch (it->second) {
                    case 1: help = true; break;
                    case 2: version = true; break;
                    case 3: recursion = true; break;
                }
            }
        }
    }
}
