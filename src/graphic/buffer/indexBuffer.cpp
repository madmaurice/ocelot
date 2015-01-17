
#include "indexBuffer.h"
#include "graphic/dxUtil.h"

OC_NS_BG;

IndexBuffer::IndexBuffer()
    : m_buffer(nullptr)
{
}

void IndexBuffer::initialize(ID3D11Device* device, const uint32* indices, uint32 numIndices)
{
    D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = sizeof(uint32) * numIndices;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    ibd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
    ZeroMemory(&iinitData, sizeof(iinitData));
    iinitData.pSysMem = indices;
    DXCall(device->CreateBuffer(&ibd, &iinitData, m_buffer.GetAddressOf()));
}

void IndexBuffer::initialize(ID3D11Device* device, const std::vector<uint32> indices)
{
    initialize(device, &indices[0], indices.size());
}

OC_NS_END;