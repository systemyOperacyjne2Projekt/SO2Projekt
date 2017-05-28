#include <ncurses.h>

struct PustePole : IPionek
{
    void drukuj() const override
    {
        printw("#");
        refresh();
    }
};


