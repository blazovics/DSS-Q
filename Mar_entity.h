//
//  Mar_entity.h
//  swarm
//
//  Created by Laszlo Blazovics on 12/15/12.
//
//

#ifndef __swarm__Mar_entity__
#define __swarm__Mar_entity__

#include "entity.h"
#include "common.h"

class CIwImage;

class Mar_entity : public Entity
{
public:
    static CIw2DImage* images[6];
    static bool imagesLoaded;
public:
    Mar_entity();
    void initImages();
    void Draw();
};

#endif /* defined(__swarm__Mar_entity__) */
