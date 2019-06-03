#ifndef DISPLACEMENT_H
#define DISPLACEMENT_H

#include "fopt.h"

class Displacement : public FOpt
{
public:
    Displacement();

    std::string getFileName();

    void readFileEvent(std::string &str);
    bool writeFileEvent(std::string &str);
};

#endif // DISPLACEMENT_H
