
#pragma once

#include <d3dx11.h>
#include "core/util/ComPtr.h"
#include "core/system/Containers.h"


OC_NS_BG;

class VertexBuffer
{
public:
    VertexBuffer();

    void Initialize(ID3D11Device* device, uint32 byteWidth, const void* data);

    template<typename T>
    void Initialize(ID3D11Device* device, const std::vector<T> vertices);

    operator ID3D11Buffer* () { return m_buffer.Get(); }
    operator ID3D11Buffer** () { return m_buffer.GetAddressOf(); }

private:
    ComPtr<ID3D11Buffer> m_buffer;
};

template<typename T>
void VertexBuffer::Initialize(ID3D11Device* device, const std::vector<T> vertices)
{
    Initialize(device, sizeof(T) * static_cast<uint32>(vertices.size()), &vertices[0]);
}

OC_NS_END;