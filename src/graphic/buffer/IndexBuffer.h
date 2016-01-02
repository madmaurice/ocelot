
#pragma once

#include <d3dx11.h>
#include "core/util/ComPtr.h"

OC_NS_BG;

class IndexBuffer
{
public:
    IndexBuffer();

    void Initialize(ID3D11Device* device, const uint32* indices, uint32 numIndices);
    void Initialize(ID3D11Device* device, const std::vector<uint32> indices);

    operator ID3D11Buffer* () { return m_buffer.Get(); }

private:
    ComPtr<ID3D11Buffer> m_buffer;
};

OC_NS_END;
