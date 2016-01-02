
#pragma once

#include "graphic/model/mesh.h"

OC_NS_BG;

class Cube : public Mesh
{
public:
    Cube();
    Cube(float width, float height, float depth);

    void BuildMesh(ID3D11Device* device);

    float m_width;
    float m_height;
    float m_depth;
};

class Sphere : public Mesh
{
public:
    Sphere();
    Sphere(float radius, uint32 sliceCount, uint32 stackCount);

    void BuildMesh(ID3D11Device* device);

    float m_radius;
    uint32 m_sliceCount;
    uint32 m_stackCount;
};

class Cylinder : public Mesh
{
public:
    Cylinder();
    Cylinder(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount);

    void BuildMesh(ID3D11Device* device);

    float m_bottomRadius;
    float m_topRadius;
    float m_height;
    uint32 m_sliceCount;
    uint32 m_stackCount;
};

class Grid : public Mesh
{
public:
    Grid();
    Grid(float width, float depth, uint32 rows, uint32 columns);

    void BuildMesh(ID3D11Device* device);

    float m_width;
    float m_depth;
    uint32 m_rows;
    uint32 m_columns;
};

OC_NS_END;

// TODO : others stuff from geometry builder