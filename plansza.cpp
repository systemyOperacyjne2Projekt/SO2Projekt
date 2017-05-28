#include "plansza.hpp"
#include "pustepole.h"
#include "pionek.h"
#include "iostream"
#include "ncurses.h"

Plansza::Plansza(int rozimar_x, int rozimar_y)
   : max(rozimar_x*rozimar_y),
     limit(0.5 * max),// limit ilosci pionkow na planszy 50%
     licznik(0)
{
    //tworzenie tablicy skladajacej sie z pustych pol
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
    if(licznik> limit)// dodawenie pionkow do okreslonego limitu, jesli limit przekroczony - czyszczenie planszy
    {
        licznik = 0;// zerowanie liczniak
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
            auto pole = macierz.at(i).at(j); // usuwanie po kolei pol z planszy
            delete pole;  // usuwanie po kolei pol z planszy
            macierz.at(i).at(j) = new PustePole(); // dodawanie pustego pola na miejsze usunietego pola
        }
    }
}

void Plansza::przesynPionki()
{
    //pionki sa przesuwane o jedna pozycje w prawo
    IPionek * pionekDousunieca = macierz.at(macierz.size() - 1).at(macierz.at(0).size() - 1);
    delete pionekDousunieca; //ostatni pionek wychodzi po za plansze wiec jest usuwany

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
                    macierz.at(pozycja_x).at(pozycja_y) = macierz.at(pozycja_x - 1).at(macierz.at(pozycja_x).size() - 1); // gdy pionek na poczatku lini pobierany pionek z porzedniej lini
                }
                else
                {
                    macierz.at(pozycja_x).at(pozycja_y) = macierz.at(pozycja_x).at(pozycja_y - 1); // pobieranie poprzeniego pionka
               }
            }
            else
            {
                macierz.at(0).at(0) = new PustePole(); // dodanie nowego pola na poczatku planszy
            }
        }
    }
}

void Plansza::drukuj()
{
    clear();
    init_pair( 1, COLOR_GREEN, COLOR_BLACK ); // stworzenie pary kolorow nr
    attron( COLOR_PAIR( 1 ) ); // wybranie pary nr 1 - wlaczenie kolorowania
    printw("  ");

    for(int i = 0 ; i < macierz.at(0).size(); i++) // drukowanie górnego obramowania planszy
    {
        printw("-");
    }
    printw("\n");


    for(const auto & linia : macierz)
    {
        printw("| "); // drukowanie bocznego odbramowania planszy
        attroff( COLOR_PAIR( 1 ) );//wylacznie kolorowania

        for(const auto & komorka : linia)
        {
            komorka->drukuj(); // drukowanie pojedynczego pola z planszy
        }
        printw("\n");
    }
}

