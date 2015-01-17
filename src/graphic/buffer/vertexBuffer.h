
#pragma once

#include <d3dx11.h>
#include "core\util\pointer.h"


OC_NS_BG;

class VertexBuffer
{
public:
    VertexBuffer();

    void initialize(ID3D11Device* device, size_t byteWidth, const void* data);

    template<typename T>
    void initialize(ID3D11Device* device, const std::vector<T> vertices);

    operator ID3D11Buffer* () { return m_buffer.Get(); }
    operator ID3D11Buffer** () { return m_buffer.GetAddressOf(); }

private:
    ComPtr<ID3D11Buffer> m_buffer;
};

template<typename T>
void oc::VertexBuffer::initialize(ID3D11Device* device, const std::vector<T> vertices)
{
    initialize(device, sizeof(T) * vertices.size(), &vertices[0]);
}

OC_NS_END;