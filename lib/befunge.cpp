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
    playfield.clear();
    playfield.push_back("");
    char c;
    while (in.get(c))
    {
        if (c == '\n')
            playfield.push_back("");
        else
            playfield[playfield.size() - 1] += c;
    }
}

void Befunge::reset_stack()
{
    playstack = std::stack<int>();
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

Befunge::CoordPair::CoordPair()
{
    xmax = 0;
    ymax = 0;
}

Befunge::CoordPair::CoordPair(int xsize, int ysize)
{
    xmax = xsize;
    ymax = ysize;
}

Befunge::CoordPair &Befunge::CoordPair::operator+=(CoordPair const& rhs)
{
    x += rhs.x;
    y += rhs.y;

    if (x >= xmax) x = 0;
    else if (x < 0) x = xmax - 1;

    if (y >= ymax) y = 0;
    else if (y < 0) y = ymax - 1;

    return *this;
}

void Befunge::interpreter(std::istream &in, std::ostream &out)
{
    bool stringmode = false;
    while (true)
    {
        std::pair<int,int> c = ptr.getPos();
        if (stringmode)
        {
            if (playfield[c.first][c.second] == '"')
                stringmode = false;
            else
                playstack.push(playfield[c.first][c.second]);
        }
        else
        {
            switch(playfield[c.first][c.second])
            {
                case ' ':
                {
                    break;
                }
                case '>':
                {
                    ptr.setDirection(EAST);
                    break;
                }
                case '<':
                {
                    ptr.setDirection(WEST);
                    break;
                }
                case '^':
                {
                    ptr.setDirection(NORTH);
                    break;
                }
                case 'v':
                {
                    ptr.setDirection(SOUTH);
                    break;
                }
                case '"':
                {
                    stringmode = true;
                    break;
                }
                case '+':
                {
                    auto a = playstack.top();
                    playstack.pop();
                    auto b = playstack.top();
                    playstack.pop();
                    playstack.push(a + b);
                    break;
                }
                case '-':
                {
                    auto a = playstack.top();
                    playstack.pop();
                    auto b = playstack.top();
                    playstack.pop();
                    playstack.push(b - a);
                    break;
                }
                case '*':
                {
                    auto a = playstack.top();
                    playstack.pop();
                    auto b = playstack.top();
                    playstack.pop();
                    playstack.push(a * b);
                    break;
                }
                case '/':
                {
                    auto a = playstack.top();
                    playstack.pop();
                    auto b = playstack.top();
                    playstack.pop();
                    playstack.push(b / a);
                    break;
                }
                case '%':
                {
                    auto a = playstack.top();
                    playstack.pop();
                    auto b = playstack.top();
                    playstack.pop();
                    playstack.push(b % a);
                    break;
                }
                case '!':
                {
                    auto a = playstack.top();
                    playstack.pop();
                    if (a)
                        playstack.push(1);
                    else
                        playstack.push(0);
                    break;
                }
                case '`':
                {
                    auto a = playstack.top();
                    playstack.pop();
                    auto b = playstack.top();
                    playstack.pop();
                    if (b > a)
                        playstack.push(1);
                    else
                        playstack.push(0);
                    break;
                }
                case '_':
                {
                    if (playstack.top())
                        ptr.setDirection(WEST);
                    else
                        ptr.setDirection(EAST);
                    playstack.pop();
                    break;
                }
                case '|':
                {
                    if (playstack.top())
                        ptr.setDirection(NORTH);
                    else
                        ptr.setDirection(SOUTH);
                    playstack.pop();
                    break;
                }
                case ':':
                {
                    playstack.push(playstack.top());
                    break;
                }
                case '\\':
                {
                    auto a = playstack.top();
                    playstack.pop();
                    auto b = playstack.top();
                    playstack.pop();
                    playstack.push(a);
                    playstack.push(b);
                    break;
                }
                case '$':
                {
                    playstack.pop();
                    break;
                }
                case '.':
                {
                    out << playstack.top();
                    playstack.pop();
                    break;
                }
                case ',':
                {
                    out << char(playstack.top());
                    playstack.pop();
                    break;
                }
                case '#':
                {
                    ++ptr;
                    break;
                }
                case '0':
                {
                    playstack.push(0);
                    break;
                }
                case '1':
                {
                    playstack.push(1);
                    break;
                }
                case '2':
                {
                    playstack.push(2);
                    break;
                }
                case '3':
                {
                    playstack.push(3);
                    break;
                }
                case '4':
                {
                    playstack.push(4);
                    break;
                }
                case '5':
                {
                    playstack.push(5);
                    break;
                }
                case '6':
                {
                    playstack.push(6);
                    break;
                }
                case '7':
                {
                    playstack.push(7);
                    break;
                }
                case '8':
                {
                    playstack.push(8);
                    break;
                }
                case '9':
                {
                    playstack.push(9);
                    break;
                }
                case 'p':
                {
                    auto y = playstack.top();
                    playstack.pop();
                    auto x = playstack.top();
                    playstack.pop();
                    auto v = playstack.top();
                    playstack.pop();
                    playfield[y][x] = v;
                    break;
                }
                case 'g':
                {
                    auto y = playstack.top();
                    playstack.pop();
                    auto x = playstack.top();
                    playstack.pop();
                    playstack.push(playfield[y][x]);
                    break;
                }
                case '&':
                {
                    int temp;
                    in >> temp;
                    playstack.push(temp);
                    break;
                }
                case '~':
                {
                    char temp;
                    in >> temp;
                    playstack.push(temp);
                    break;
                }
                case '@':
                {
                    return;
                }
                default:
                {
                    break;
                }
            }
        }
        ++ptr;
    }
}

Befunge::FieldPointer::FieldPointer()
{
    pos = CoordPair(80, 24);
    setDirection(EAST);
}

Befunge::FieldPointer::FieldPointer(int xsize, int ysize)
{
    pos = CoordPair(xsize, ysize);
    setDirection(EAST);
}

void Befunge::FieldPointer::setDirection(Direction dir)
{
    switch(dir)
    {
        case NORTH:
            vel.x = 0;
            vel.y = 1;
            break;

        case SOUTH:
            vel.x = 0;
            vel.y = -1;
            break;

        case EAST:
            vel.x = 1;
            vel.y = 0;
            break;

        case WEST:
            vel.x = -1;
            vel.y = 0;
            break;
    }
}

std::pair<int,int> const Befunge::FieldPointer::getPos()
{
    auto rval = std::make_pair<int&,int&>(pos.x,pos.y);
    return rval;
}
