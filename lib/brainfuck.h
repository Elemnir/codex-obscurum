#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>

class Brainfuck
{
    public:
        Brainfuck();
        Brainfuck(unsigned MEMSIZE);
        Brainfuck(std::istream &in);
        Brainfuck(unsigned MEMSIZE, std::istream &in);
        virtual ~Brainfuck();

        void load(std::istream &in);
        void reset_memory(unsigned MEMSIZE=1024);

        void interpret();
        void interpret(std::istream &in);
        void interpret(std::ostream &out);
        void interpret(std::istream &in, std::ostream &out);

    protected:
        class Memory
        {//data storage and pointer logic
            public:
                Memory(unsigned memsize)
                {
                    data.resize(memsize, 0);
                    p = data.begin();
                }
                char &operator*() { return *p; }
                std::vector<char>::iterator operator++() { return ++p; }
                std::vector<char>::iterator operator--() { return --p; }

            private:
                std::vector<char> data;
                std::vector<char>::iterator p;
        };

    private:
        void interpreter(std::string::iterator i,
                         std::istream &in, std::ostream &out);

        std::string code;
        std::shared_ptr<Memory> memory;
};

#endif // BRAINFUCK_H
