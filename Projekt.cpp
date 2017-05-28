#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "plansza.hpp"
#include <queue>
#include <thread>
#include <mutex>
#include <ncurses.h>

Plansza * g_plansza;
std::queue<int> kolejka_X;
std::queue<int> kolejka_Y;
std::mutex mx;

void producent(const int rozimar_x, const int rozimar_y)
{
    while(true)//nieskonczona petla
    {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        //lososwanie 2 liczb oraz dodawanie ich do kolejki
        std::lock_guard<std::mutex> lock(mx);
        auto wyloswowany_x = std::rand() % rozimar_x;
        auto wyloswowany_y =  std::rand() % rozimar_y ;

        kolejka_X.push(wyloswowany_x);
        kolejka_Y.push(wyloswowany_y);
    }
}

void przetwarzacz()
{
    while(true)//nieskonczona petla
    {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mx); // mx.lock()
        if ((!kolejka_X.empty()) && (!kolejka_Y.empty()))
        {
            // w przypadku gdy obie kolejki zawieraja jakies liczby dodanie nowego pionka na planszy
            g_plansza->dodajPionka(kolejka_X.front(), kolejka_Y.front());
            kolejka_X.pop();// usuniecie liczb z kolejki
            kolejka_Y.pop();
        }
        g_plansza->przesynPionki();
    }
}

void drukuj()
{
    initscr();//inicjalizacja dla biblioteki ncurses
    start_color();// wlaczenie kolorowania
    while(true)//nieskonczona petla
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::lock_guard<std::mutex> lock(mx); // mx.lock()
        g_plansza->drukuj();
    }
    endwin();// wy?aczenie  biblioteki ncurses
}



int main(int argc, char *argv[])
{
    if(argc != 3)// sprawdzanie ilosci parametrow wejsciowych
    {
        std::cout << "Bledne parametry wejsciowe";
        return 0;
    }

    std::cout << "Rozmiar macierzy ";
    for(auto i =1; i < argc; i++)
    {
        std::cout << argv[i] << "  ";
    }
    std::cout << std::endl;

    const int rozimar_x = std::stoi(argv[1]);
    const int rozimar_y = std::stoi(argv[2]);

    g_plansza = new Plansza(rozimar_x, rozimar_y); // stworzenie macierzy

    srand (time(NULL));// uruchomienie czasu dla - niezbedne do losowania

    std::vector<std::thread> threads; // stworzenie vectora watkow oraz dodanie 3 watkow
    threads.push_back(std::thread( producent, rozimar_x, rozimar_y));
    threads.push_back(std::thread( przetwarzacz));
    threads.push_back(std::thread( drukuj));

    for (auto & thread : threads)
    {
        thread.join(); // synchronizacja watkow
    }

    return 0;
}
