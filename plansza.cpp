#include "plansza.hpp"
#include "pustepole.h"
#include "pionek.h"


Plansza::Plansza(int rozimar_x, int rozimar_y)
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
    auto pole = macierz.at(pozycja_x).at(pozycja_y);
    delete pole;
    macierz.at(pozycja_x).at(pozycja_y) = new Pionek();
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

            if(!(pozycja_y == pozycja_x == 0))
            {
                if(pozycja_y == 0)
                {
                    macierz.at(pozycja_x).at(pozycja_y) = macierz.at(pozycja_x - 1).at(macierz.at(pozycja_x).size() - 1);
                }
                else
                {
                    macierz.at(pozycja_x).at(pozycja_y) = macierz.at(pozycja_x).at(pozycja_y);
               }
            }
            else
            {
                macierz.at(0).at(0) = new PustePole();
            }
        }
    }
}

