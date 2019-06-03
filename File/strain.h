#ifndef STRAIN_H
#define STRAIN_H

#include "fopt.h"

class strain : public FOpt
{
public:
    strain();

    std::string getFileName();

    void readFileEvent(std::string &str);
    bool writeFileEvent(std::string &str);
};

#endif // STRAIN_H
