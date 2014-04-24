#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <functional>
#include <stack>

class Brainfuck
{
    template <typename T>
    class Memory
    {//data storage and pointer logic
        public:
            Memory() {}
            Memory(unsigned memsize)
            {
                data.resize(memsize, 0);
                p = data.begin();
            }
            T &operator*() { return *p; }
            Memory &operator++() { ++p; return *this; }
            Memory &operator--() { --p; return *this; }

        private:
            std::vector<T> data;
            typename std::vector<T>::iterator p;
    };

  public:
    Brainfuck();
    Brainfuck(std::string const& source, unsigned memsize=1024);

    void parse_code();
    void reset_memory(unsigned memsize=1024);

    void set_streams(std::istream &instream, std::ostream& outstream);
    void set_istream(std::istream &instream);
    void set_ostream(std::ostream &outstream);


    void interpret();
    void interpret(std::istream &instream, std::ostream &outstream);

    std::string code;
    Memory<char> memory;

  private:
    void initialize_dictionary();
    void interpreter();

    std::string mapped_operations;
    std::unordered_map<char, std::function<void()> > dict;

    std::reference_wrapper<std::istream> in;
    std::reference_wrapper<std::ostream> out;

    std::stack<std::string::iterator> iter_stack;
};

#endif // BRAINFUCK_H
