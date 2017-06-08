#include "plansza.hpp"
#include "pustepole.h"
#include "pionek.h"
#include "iostream"
#include "ncurses.h"

Plansza::Plansza(int rozimar_x, int rozimar_y)
   : max(rozimar_x*rozimar_y),
     limit(0.5 * max),
     licznik(0)
{
    for(auto i = 0 ; i < rozimar_x; i ++)
    {
        macierz.push_back({});
        for(auto j = 0; j < rozimar_y; j++)
        {
            macierz.at(i).push_back(new PustePole());
        }
    }
}

void Plansza::dodajPionka(int pozycja_x, int pozycja_y)
{
    if(licznik> limit)
    {
        licznik = 0;
        wyczyscPlansze();
    }
    auto pole = macierz.at(pozycja_x).at(pozycja_y);
    delete pole;
    macierz.at(pozycja_x).at(pozycja_y) = new Pionek();
    licznik++;
}

void Plansza::wyczyscPlansze()
{
    for(auto i = 0 ; i < macierz.size(); i ++)
    {
        for(auto j = 0; j < macierz.at(macierz.size() - 1).size(); j++)
        {
            auto pole = macierz.at(i).at(j);
            delete pole;
            macierz.at(i).at(j) = new PustePole();
        }
    }
}

void Plansza::przesynPionki()
{
    IPionek * pionekDousunieca = macierz.at(macierz.size() - 1).at(macierz.at(0).size() - 1);
    delete pionekDousunieca;

    for(auto i = 0 ; i < macierz.size(); i ++)
    {
        for(auto j = 0; j < macierz.at(macierz.size() - 1).size(); j++)
        {
            int pozycja_x = macierz.size() - 1 - i;
            int pozycja_y = macierz.at(pozycja_x).size() - 1 -j;

            if(!((pozycja_y == 0) && (pozycja_x == 0)))
            {
                if(pozycja_y == 0)
                {
                    macierz.at(pozycja_x).at(pozycja_y) = macierz.at(pozycja_x - 1).at(macierz.at(pozycja_x).size() - 1);
                }
                else
                {
                    macierz.at(pozycja_x).at(pozycja_y) = macierz.at(pozycja_x).at(pozycja_y - 1);
               }
            }
            else
            {
                macierz.at(0).at(0) = new PustePole();
            }
        }
    }
}

void Plansza::drukuj()
{
    clear();
    init_pair( 1, COLOR_GREEN, COLOR_BLACK );
    attron( COLOR_PAIR( 1 ) );
    printw("  ");

    for(int i = 0 ; i < macierz.at(0).size(); i++)
    {
        printw("-");
    }
    printw("\n");
    attroff( COLOR_PAIR( 1 ) );


    for(const auto & linia : macierz)
    {
        attron( COLOR_PAIR( 1 ) );
        printw("| ");
        attroff( COLOR_PAIR( 1 ) );

        for(const auto & komorka : linia)
        {
            komorka->drukuj();
        }
        printw("\n");
    }
}

