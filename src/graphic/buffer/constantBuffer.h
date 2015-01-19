
#pragma once

#include "core\util\pointer.h"

OC_NS_BG;

template <class T>
class ConstantBuffer
{
public:
    explicit ConstantBuffer(bool dynamicUsage = true);

    void initialize(ID3D11Device* device);
    void applyChanges(ID3D11DeviceContext* deviceContext);

    operator ID3D11Buffer* () { return m_buffer.Get(); }
    operator ID3D11Buffer** () { return m_buffer.GetAddressOf(); }

    T m_data;

private:
    ComPtr<ID3D11Buffer> m_buffer;
    bool m_dynamicUsage;
};

OC_NS_END;

#include "constantBuffer.inl"