//
//  Mar_entity.cpp
//  swarm
//
//  Created by Laszlo Blazovics on 12/15/12.
//
//

#include "Mar_entity.h"
#include "place.h"
#include "field.h"

bool Mar_entity::imagesLoaded = false;
CIw2DImage* Mar_entity::images[] = {NULL,NULL,NULL,NULL,NULL,NULL};

Mar_entity::Mar_entity()
{
    if(imagesLoaded == false)
    {
        initImages();
    }
    
}


void Mar_entity::initImages()
{

    images[0] = Iw2DCreateImageResource("tiger_0");
    images[1] = Iw2DCreateImageResource("tiger_1");
    images[2] = Iw2DCreateImageResource("t34_2");
    images[3] = Iw2DCreateImageResource("t34_3");
    images[4] = Iw2DCreateImageResource("t34_4");
    images[5] = Iw2DCreateImageResource("t34_5");
}

void Mar_entity::Draw()
{
    if(this->currentPlace == NULL)
        return;
    
    float unit = 40;
    float height = sqrt(3)/2*unit;
    
    Point2f placePos = this->currentPlace->getOnScreenPos();
    Point2i offset = this->currentPlace->getParentField()->getOffset();
    
    CIwSVec2 Position(placePos.x-offset.x, placePos.y-offset.y);
     
    
    // Build the transform
	// Set the rotation transform
	Transform.SetRot(0);
	// Scale the transform
	Transform.ScaleRot(IW_GEOM_ONE);
	// Translate the transform
	Transform.SetTrans(Position);
	// Set this transform as the active transform for Iw2D
	Iw2DSetTransformMatrix(Transform);

    Iw2DSetColour(0xffffffff); // Set red
    
    //Iw2DFillArc(CIwSVec2(height, unit), CIwSVec2((unit/2), (unit/2)), 0, IW_ANGLE_2PI);
    Iw2DDrawImage(images[0], CIwSVec2(0, 0), CIwSVec2(2*unit, 2*unit));
}