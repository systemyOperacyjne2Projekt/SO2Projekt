#include <iostream>
#include <vector>
#include "interfacepionek.h"

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

    const auto rozimar_x = argv[1];
    const auto rozimaryx = argv[2];

    std::vector<std::vector<IPionek *>> macierz;

    return 0;
}
