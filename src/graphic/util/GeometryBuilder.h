
#pragma once

#include "graphic/model/Shape.h"

OC_NS_BG;

class GeometryBuilder
{
public:
    GeometryBuilder();

    Cube CreateCube(float width, float height, float depth);
};

OC_NS_END;

// TODO : others stuff from geometry builder