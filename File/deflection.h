#ifndef DEFLECTION_H
#define DEFLECTION_H

#include "fopt.h"

class Deflection : public FOpt
{
public:
    Deflection();

    std::string getFileName();

    void readFileEvent(std::string &str);
    bool writeFileEvent(std::string &str);
};

#endif // DEFLECTION_H
