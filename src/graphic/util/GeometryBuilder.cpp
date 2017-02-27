
#include "GeometryBuilder.h"
#include "graphic/Graphic.h"

OC_NS_BG;


GeometryBuilder::GeometryBuilder()
{
}

Cube GeometryBuilder::CreateCube(float width, float height, float depth)
{
    Cube cube(width, height, depth);
    cube.BuildMesh(Graphic::GetDevice().Get());
    return cube;
}

OC_NS_END;