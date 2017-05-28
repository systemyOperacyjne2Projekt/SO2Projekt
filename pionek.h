#include <ncurses.h>

struct Pionek : IPionek
{
    void drukuj() const override
    {
        init_pair( 2, COLOR_RED, COLOR_BLACK ); //stworzenie pary kolorow o nr 2
        attron( COLOR_PAIR( 2 ) ); //wybrenie pary kolorow o nr 2
        attron( A_BOLD ); // wlaczenie pogrubienie
        printw("A"); // symbol pionka
        attroff( A_BOLD); // wy?aczenie pogrubiania
        attroff( COLOR_PAIR( 2 ) ); //Wy??czenie koloru tekstu
        refresh();
    }

};
