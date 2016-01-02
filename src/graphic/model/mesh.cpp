
#include "Mesh.h"

OC_NS_BG;

namespace
{
    static D3D11_INPUT_ELEMENT_DESC vertexDeclaration[3] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
}

MeshVertexDeclaration MeshVertex::getVertexDeclaration()
{
    return {vertexDeclaration, 3};
}


void Mesh::buildBuffers(ID3D11Device* device)
{
    m_vertexBuffer.Initialize(device, m_vertices);
    m_indexBuffer.Initialize(device, m_indices);
}

VertexBuffer Mesh::GetVertexBuffer()
{
    return m_vertexBuffer;
}

IndexBuffer Mesh::GetIndexBuffer()
{
    return m_indexBuffer;
}

DXGI_FORMAT Mesh::GetIndexBufferFormat() const
{
    return DXGI_FORMAT_R32_UINT;
}

OC_NS_END;