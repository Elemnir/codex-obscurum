#include "befunge.h"

Befunge::Befunge()
{
    reset_stack();
}

Befunge::Befunge(std::istream& in)
{
    load(in);
}

Befunge::~Befunge()
{
}

void Befunge::load(std::istream& in)
{
    /*
    playfield.clear();
    playfield.push_back("");
    int i(0);
    char c;
    while (in.get(c))
    {
        if (c == '\n')
        {
            playfield.push_back("");
            ++i;
        }

        else
            playfield[i] += c;
    }
    */
}

void Befunge::reset_stack()
{
    playstack = std::make_shared<std::stack<int> >();
}

void Befunge::interpret()
{
    interpreter(std::cin, std::cout);
}

void Befunge::interpret(std::istream& in)
{
    interpreter(in, std::cout);
}

void Befunge::interpret(std::ostream& out)
{
    interpreter(std::cin, out);
}

void Befunge::interpret(std::istream& in, std::ostream& out)
{
    interpreter(in, out);
}

void Befunge::interpreter(std::istream &in, std::ostream &out)
{
}

Befunge::Playfield::Playfield()
{
}

Befunge::Playfield::Playfield(unsigned width, unsigned height)
{
}

Befunge::Playfield::Playfield(unsigned width, unsigned height, std::istream& in)
{
}

Befunge::Playfield::Playfield(std::istream& in)
{
}

char Befunge::Playfield::getInstruction(unsigned x, unsigned y)
{
}

void Befunge::Playfield::setInstruction(unsigned x, unsigned y, char val)
{
}

Befunge::FieldPointer::FieldPointer()
{
}

void Befunge::FieldPointer::setDirection(Direction dir)
{
}

CoordPair const& Befunge::FieldPointer::getPos()
{
}
