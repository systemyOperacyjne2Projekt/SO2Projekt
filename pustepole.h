#include "interfacepionek.h"

struct PustePole : IPionek
{
    virtual std::string pobierzObraz() const override
    {
        return "[]";
    }
};
