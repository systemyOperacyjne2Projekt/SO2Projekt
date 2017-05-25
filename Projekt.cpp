#include <iostream>
#include <vector>
#include "plansza.hpp"

int main(int argc, char *argv[])
{
    if(argc != 3)
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

    Plansza l_plansza = Plansza(rozimar_x, rozimar_y);

    return 0;
}
