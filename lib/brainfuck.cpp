#include "brainfuck.h"

#include <algorithm>

Brainfuck::Brainfuck() :
    in(std::cin), out(std::cout)
{
    initialize_dictionary();
    reset_memory();
}

Brainfuck::Brainfuck(std::string const& source, unsigned memsize) :
    in(std::cin), out(std::cout)
{
    initialize_dictionary();
    reset_memory(memsize);
    code = source;
}

void Brainfuck::parse_code()
{
    std::string temp;
    for_each(code.begin(), code.end(), [&] (char i) {
        if (mapped_operations.find(i) != std::string::npos)
            temp += i;
    });
    code = temp;
}

void Brainfuck::set_streams(std::istream& instream, std::ostream& outstream)
{
    in = std::ref(instream);
    out = std::ref(outstream);
}

void Brainfuck::set_istream(std::istream& instream)
{
    in = std::ref(instream);
}

void Brainfuck::set_ostream(std::ostream& outstream)
{
    out = std::ref(outstream);
}

void Brainfuck::reset_memory(unsigned memsize)
{
    memory = Memory<char>(memsize);
}

void Brainfuck::interpret()
{
    iter_stack.push(code.begin());
    interpreter();
}

void Brainfuck::interpret(std::istream& instream, std::ostream& outstream)
{
    set_streams(instream, outstream);
    iter_stack.push(code.begin());
    interpreter();
}

void Brainfuck::initialize_dictionary()
{
    dict.clear();
    mapped_operations = "+-><.,[]";

    dict['+'] = [&] () { ++*memory; };
    dict['-'] = [&] () { --*memory; };
    dict['>'] = [&] () { ++memory; };
    dict['<'] = [&] () { --memory; };
    dict['.'] = [&] () { out.get().put(*memory); };
    dict[','] = [&] () { in.get().get(*memory); };
    dict[']'] = [&] () { iter_stack.pop(); };
    dict['['] = [&] () {
        if (*memory) {
            --iter_stack.top();
            iter_stack.push(iter_stack.top());
            ++iter_stack.top();
        } else {
            int scopeCount(1);
            while (scopeCount) {
                ++iter_stack.top();
                if (*(iter_stack.top()) == '[') ++scopeCount;
                if (*(iter_stack.top()) == ']') --scopeCount;
            }
            ++iter_stack.top();
        } };
}

void Brainfuck::interpreter()
{
    while (iter_stack.top() != code.end())
    {
        char c = *iter_stack.top();
        ++iter_stack.top();
        if (dict.find(c) != dict.end())
            dict[c] ();
    }
}
