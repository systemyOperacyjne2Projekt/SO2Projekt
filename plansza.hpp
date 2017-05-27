
#include "interfacepionek.h"
#include <vector>

class Plansza
{
public:

    Plansza(int rozimar_x, int rozimar_y);

    void dodajPionka(int pozycja_x, int pozycja_y);

    void wyczyscPlansze();

    void przesynPionki();

    void drukuj();

private:

    std::vector<std::vector<IPionek *>> macierz;
};
