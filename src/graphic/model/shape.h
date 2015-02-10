
#pragma once

#include "graphic/buffer/indexBuffer.h"
#include "graphic/buffer/vertexBuffer.h"
#include "graphic/model/mesh.h"

OC_NS_BG;

class GeometryBuilder;

class Shape
{
public:

    VertexBuffer getVertexBuffer();
    IndexBuffer getIndexBuffer();

protected:
    Shape();

    void buildBuffers(ID3D11Device* device);

    ComPtr<ID3D11Device> m_dxDevice;

    Mesh            m_mesh;
    VertexBuffer    m_vertexBuffer;
    IndexBuffer     m_indexBuffer;

    friend GeometryBuilder;
};


class Cube : public Shape
{
public:
    Cube();
    Cube(float width, float height, float depth);

    void buildMesh(ID3D11Device* device);

    float m_width;
    float m_height;
    float m_depth;
};

OC_NS_END;

// TODO : others stuff from geometry builder