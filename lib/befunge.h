#ifndef BEFUNGE_H
#define BEFUNGE_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <utility>

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
                CoordPair();
                CoordPair(int xsize, int ysize);
                CoordPair &operator+=(CoordPair const& rhs);
                int x, y;
                int xmax, ymax;
        };

        class FieldPointer
        {
            public:
                FieldPointer();
                FieldPointer(int xsize, int ysize);

                void setDirection(Direction dir);
                std::pair<int,int> const getPos();

                FieldPointer &operator++() { pos += vel; return *this;}

            private:
                CoordPair pos;
                CoordPair vel;
        };

    private:
        void interpreter(std::istream &in, std::ostream &out);

        std::vector<std::string> playfield;
        std::stack<int> playstack;
        FieldPointer ptr;
};

#endif // BEFUNGE_H
