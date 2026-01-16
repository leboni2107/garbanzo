#pragma once

/** @name Stores given Arguments
 */
class Arguments {
public:
    bool help = false;
    bool version = false;
    bool recursion = false;


    /** @return Returns initialized Arguments class
     */
    Arguments(int argc, char* argv[]);
};
