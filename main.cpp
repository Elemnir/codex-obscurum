#include "brainfuck.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
    std::string fname;
    if (argc == 1)
    {//no command line args
        std::cout << "Source file: ";
        std::cin >> fname;
    }
    else
    {//run whatever was specified in the command line
       fname = argv[1];
    }

    //open the file
    std::ifstream in(fname.c_str());
    if (in.fail())
    {
		std::cout << "Error: File not found.\n";
		return 0;
	}

	Brainfuck bf(in);
	bf.interpret();

    std::cin >> fname;
    return 0;
}
