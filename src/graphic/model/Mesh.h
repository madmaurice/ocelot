
#pragma once

#include "math/Vector2.h"
#include "math/Vector3.h"
#include "graphic/buffer/IndexBuffer.h"
#include "graphic/buffer/VertexBuffer.h"
#include <d3d11.h>


OC_NS_BG;

struct MeshVertexDeclaration
{
    D3D11_INPUT_ELEMENT_DESC* m_desc;
    uint8 m_numElements;
};

struct MeshVertex
{
    MeshVertex() = default;
    MeshVertex(const Vector3& p, const Vector3& n, const Vector2& uv)
        : m_position(p), m_normal(n), m_texCoord(uv){}
    MeshVertex(float px, float py, float pz,
        float nx, float ny, float nz,
        float u, float v)
        : m_position(px, py, pz), m_normal(nx, ny, nz),
        m_texCoord(u, v){}

    static MeshVertexDeclaration getVertexDeclaration();

    Vector3 m_position;
    Vector3 m_normal;
    Vector2 m_texCoord;
};

class Mesh
{
public:

    VertexBuffer GetVertexBuffer();
    IndexBuffer GetIndexBuffer();

    DXGI_FORMAT GetIndexBufferFormat() const;

protected:

    void buildBuffers(ID3D11Device* device);

    VertexBuffer    m_vertexBuffer;
    IndexBuffer     m_indexBuffer;

    Vector<MeshVertex> m_vertices;
    Vector<uint32> m_indices;
};

OC_NS_END;