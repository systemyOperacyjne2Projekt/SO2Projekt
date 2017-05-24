#include <string>

struct IPionek
{
    virtual ~IPionek(){}
    virtual std::string pobierzObraz() const = 0;
};
