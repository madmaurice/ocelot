
#include "indexBuffer.h"
#include "graphic/util/DxUtil.h"

OC_NS_BG;

IndexBuffer::IndexBuffer()
    : m_buffer(nullptr)
{
}

void IndexBuffer::Initialize(ID3D11Device* device, const uint32* indices, uint64 numIndices)
{
    D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = static_cast<uint32>(sizeof(uint32) * numIndices);
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    ibd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
    ZeroMemory(&iinitData, sizeof(iinitData));
    iinitData.pSysMem = indices;
    DXCall(device->CreateBuffer(&ibd, &iinitData, m_buffer.GetAddressOf()));
}

void IndexBuffer::Initialize(ID3D11Device* device, const std::vector<uint32> indices)
{
    Initialize(device, &indices[0], static_cast<uint32>(indices.size()));
}

OC_NS_END;