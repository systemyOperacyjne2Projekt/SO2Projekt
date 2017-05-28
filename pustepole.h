#include <ncurses.h>

struct PustePole : IPionek
{
    void drukuj() const override
    {
        //drukowanie symbolu pustej planszy bez kolorowania
        printw("#");
        refresh();
    }
};


