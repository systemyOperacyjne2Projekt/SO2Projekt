#include <ncurses.h>

struct Pionek : IPionek
{
    void drukuj() const override
    {
        init_pair( 2, COLOR_RED, COLOR_BLACK ); //3
        attron( COLOR_PAIR( 2 ) ); //4
        attron( A_BOLD );
        printw("A");
        attroff( A_BOLD);
        attroff( COLOR_PAIR( 2 ) ); //Wy??czenie koloru tekstu
        refresh();
    }

};
