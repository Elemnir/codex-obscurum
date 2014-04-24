#include "codex.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
/*
	Brainfuck bf;
	bf.code = "++++++[>++++++<-]>.";
	bf.interpret();
*/
    std::ifstream in("hw_befunge.txt");
    Befunge bf;
    if (in.fail())
        return -1;
    bf.load(in);
    bf.interpret();

    std::string junk;
    getline(std::cin, junk);
    return 0;
}
