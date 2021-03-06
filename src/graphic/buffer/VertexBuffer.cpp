
#include "vertexBuffer.h"
#include "graphic/util/DxUtil.h"

OC_NS_BG;


VertexBuffer::VertexBuffer()
    : m_buffer(nullptr)
{
}

void VertexBuffer::Initialize(ID3D11Device* device, uint32 byteWidth, const void* data)
{
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = byteWidth;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = data;
    DXCall(device->CreateBuffer(&bd, &initData, m_buffer.GetAddressOf()));
}

OC_NS_END;