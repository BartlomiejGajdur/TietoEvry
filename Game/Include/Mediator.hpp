#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

extern std::string FileName;
extern std::string MapFile;
extern std::string StatusFile;
extern std::string ActionsFile;
extern size_t TimeLimit;

namespace mediator
{
    int checkGivenData(int argc, char *argv[]);
}
