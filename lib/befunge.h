#ifndef BEFUNGE_H
#define BEFUNGE_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <memory>

enum Direction
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class CoordPair
{
    public:
        CoordPair &operator+=(CoordPair const& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        int x, y;
};

class Befunge
{
    public:
        Befunge();
        Befunge(std::istream &in);
        virtual ~Befunge();

        void load(std::istream &in);
        void reset_stack();

        void interpret();
        void interpret(std::istream &in);
        void interpret(std::ostream &out);
        void interpret(std::istream &in, std::ostream &out);

    protected:
        class Playfield
        {
            public:
                Playfield();
                Playfield(unsigned width, unsigned height);
                Playfield(unsigned width, unsigned height, std::istream &in);
                Playfield(std::istream &in);

                void load(std::istream &in);
                char getInstruction(unsigned x, unsigned y);
                void setInstruction(unsigned x, unsigned y, char val);

            private:
                std::vector<std::string> field;

        };

        class FieldPointer
        {
            public:
                FieldPointer();

                void setDirection(Direction dir);
                CoordPair const& getPos();

                FieldPointer &operator++() { pos += vel; return *this;}

            private:
                CoordPair pos;
                CoordPair vel;
        };

    private:
        void interpreter(std::istream &in, std::ostream &out);

        std::shared_ptr<Playfield> playfield;
        std::shared_ptr<std::stack<int> > playstack;
        FieldPointer ptr;
};

#endif // BEFUNGE_H
