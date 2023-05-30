#include <fstream>

#include "filesystem.hpp"

int main()
{
    printDirectory(".");

    std::ofstream("test.ttt");

    changeExtension(".", ".*\\.ttt", ".txt");

    printDirectory(".");

    return 0;
}