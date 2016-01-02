
#pragma once

#include "core/util/ComPtr.h"
#include "graphic/util/DxUtil.h"

OC_NS_BG;

template <class T>
class ConstantBuffer : public NonCopyable
{
public:
    explicit ConstantBuffer(bool dynamicUsage = true);

    void Initialize(ID3D11Device* device);
    void ApplyChanges(ID3D11DeviceContext* deviceContext);

    operator ID3D11Buffer* () { return m_buffer.Get(); }
    operator ID3D11Buffer** () { return m_buffer.GetAddressOf(); }

    T m_data;

private:
    ComPtr<ID3D11Buffer> m_buffer;
    bool m_dynamicUsage;
};

OC_NS_END;

#include "constantBuffer.inl"