#include <ncurses.h>

struct Pionek : IPionek
{
    void drukuj() const override
    {
        init_pair( 2, COLOR_RED, COLOR_BLACK );
        attron( COLOR_PAIR( 2 ) );
        attron( A_BOLD );
        printw("A");
        attroff( A_BOLD);
        attroff( COLOR_PAIR( 2 ) );
        refresh();
    }
};
