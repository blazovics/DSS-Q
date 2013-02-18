#ifndef TARGETENTITY_H
#define TARGETENTITY_H

#include "entity.h"

class TargetEntity : public Entity
{
protected:
    int getType();

public:
    TargetEntity();

};

#endif // TARGETENTITY_H
