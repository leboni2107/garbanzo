#pragma once

/** @name Stores given Arguments
 */
class Arguments {
public:
    bool help = false;
    bool recursion = false;

    Arguments(int argc, char* argv[]);
};
