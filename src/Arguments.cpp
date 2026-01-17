#include "../include/Arguments.h"
#include <string>
#include <unordered_map>

using namespace std;

Arguments::Arguments(int argc, char *argv[]) {
    if (argc > 1) {
        unordered_map<string, int> optionMap = {
            {"-h", 1}, {"--help", 1},
            {"-v", 2}, {"--version", 2},
            {"-r", 3}, {"--recursion", 3},
            {"-c", 4}, {"--no-file-content", 4},
            {"-n", 5}, {"--no-file-name", 5},
            {"-i", 6}, {"--ignore-case", 6},
            {"-e", 7}, {"--extension-sensitive", 7},
            {"--extension-help", 8}
        };

        for (int i = 0; i < argc; i++) {
            auto it = optionMap.find(argv[i]);

            if (it != optionMap.end()) {
                switch (it->second) {
                    case 1: help = true; break;
                    case 2: version = true; break;
                    case 3: recursion = true; break;
                    case 4: file_content = false; break;
                    case 5: file_name = false; break;
                    case 6: case_sensitive = false; break;
                    case 7: extensions.extension_sensitive = true;
                        if (i + 1 < argc) {
                            string extArgs = "";
                            if (i + 1 < argc && argv[i + 1][0] != '-') {
                                extArgs += argv[i + 1];
                                i++;
                                while (i + 1 < argc && argv[i + 1][0] != '-' && argv[i + 1][0] != '@') {
                                    extArgs += " " + string(argv[i + 1]);
                                    i++;
                                }

                                extensions.readExtensions(extArgs);
                            }
                        }
                        break;
                    case 8: extensions.extension_help = true; break;
                }
            }
        }
    }
}