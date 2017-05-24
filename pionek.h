#include "interfacepionek.h"

struct Pionek : IPionek
{
    virtual std::string pobierzObraz() const override
    {

        return "^";
    }

};
