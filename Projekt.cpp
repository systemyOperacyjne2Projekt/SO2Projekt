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
    while(true)
    {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mx);
        auto wyloswowany_x = std::rand() % rozimar_x;
        auto wyloswowany_y =  std::rand() % rozimar_y ;

        kolejka_X.push(wyloswowany_x);
        kolejka_Y.push(wyloswowany_y);
    }
}

void przetwarzacz()
{
    while(true)
    {
        //std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mx);
        if ((!kolejka_X.empty()) && (!kolejka_Y.empty()))
        {
            g_plansza->dodajPionka(kolejka_X.front(), kolejka_Y.front());
            kolejka_X.pop();
            kolejka_Y.pop();
        }
        g_plansza->przesynPionki();
    }
}

void drukuj()
{
    initscr();
    start_color();
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mx);
        g_plansza->drukuj();
    }
    endwin();
}



int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        std::cout << "Bledne parametry wejsciowe" << std::endl;
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

    g_plansza = new Plansza(rozimar_x, rozimar_y);

    srand (time(NULL));

    std::vector<std::thread> threads;
    threads.push_back(std::thread( producent, rozimar_x, rozimar_y));
    threads.push_back(std::thread( przetwarzacz));
    threads.push_back(std::thread( drukuj));

    for (auto & thread : threads)
    {
        thread.join();
    }

    return 0;
}
