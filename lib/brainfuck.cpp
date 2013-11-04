#include "brainfuck.h"

Brainfuck::Brainfuck()
{
    reset_memory(1024);
}

Brainfuck::Brainfuck(unsigned MEMSIZE)
{
    reset_memory(MEMSIZE);
}

Brainfuck::Brainfuck(unsigned MEMSIZE, std::istream& in)
{
    reset_memory(MEMSIZE);
    load(in);
}

Brainfuck::Brainfuck(std::istream& in)
{
    reset_memory(1024);
    load(in);
}

Brainfuck::~Brainfuck()
{
}

void Brainfuck::load(std::istream& in)
{
    code.clear();
    std::string s("<>+-[].,");
    char c;
    while (in.get(c))
    {//store brainfuck operations in a string
        if (s.find(c) != std::string::npos)
            code += c;
    }
}

void Brainfuck::reset_memory(unsigned MEMSIZE)
{
    memory = std::make_shared<Memory>(MEMSIZE);
}

void Brainfuck::interpret()
{
    interpreter(code.begin(), std::cin, std::cout);
}

void Brainfuck::interpret(std::istream& in)
{
    interpreter(code.begin(), in, std::cout);
}

void Brainfuck::interpret(std::ostream& out)
{
    interpreter(code.begin(), std::cin, out);
}

void Brainfuck::interpret(std::istream& in, std::ostream& out)
{
    interpreter(code.begin(), in, out);
}

void Brainfuck::interpreter(std::string::iterator i,
                            std::istream &in, std::ostream &out)
{
    while (i != code.end())
    {
        char c = *i;
        ++i;
        switch(c)
        {
            case '+': //increment data value
                ++*(*memory);
                break;
            case '-': //decrement data value
                --*(*memory);
                break;
            case '>': //increment data pointer
                ++(*memory);
                break;
            case '<': //decrement data pointer
                --(*memory);
                break;
            case '.': //print out data value
                out.put(*(*memory));
                break;
            case ',': //set data value to input
				in.get(*(*memory));
                break;
			case '[': //execute conditional statement
                if (*(*memory))
                {
					interpreter(i, in, out);
					--i; //return the code iterator to the '[' symbol
				}
				else
				{//advance the code iterator to the symbol after the ']'
					int scopeCount = 1;
					while (scopeCount) {
						++i;
						if (*i == '[') ++scopeCount;
						if (*i == ']') --scopeCount;
					}
					++i;
				}
				break;
            case ']': //end conditional statement
                return;
        }
    }
}
