

OC_NS_BG;

// Constant buffer packing rules http://msdn.microsoft.com/en-us/library/windows/desktop/bb509632(v=vs.85).aspx
// Data must be multiple of 16 bytes

// Buffer usage : http://msdn.microsoft.com/en-us/library/windows/desktop/ff476259%28v=vs.85%29.aspx
// D3D11_USAGE_DYNAMIC must have D3D11_CPU_ACCESS_WRITE and use map/unmap (better for frequent update ex: every frames)
// D3D11_USAGE_DEFAULT use UpdateSubResources

template <class T>
ConstantBuffer<T>::ConstantBuffer(bool dynamicUsage)
    : m_dynamicUsage(dynamicUsage)
{
    ZeroMemory(&m_data, sizeof(T));
}

template <class T>
void ConstantBuffer<T>::Initialize(ID3D11Device* device)
{
    D3D11_BUFFER_DESC cbd;
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    // Add padding if necessary
    cbd.ByteWidth = static_cast<uint32>(sizeof(ConstantBuffer) + (16 - (sizeof(ConstantBuffer) % 16)));
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0;
    cbd.StructureByteStride = 0;

    if (!m_dynamicUsage)
    {
        cbd.Usage = D3D11_USAGE_DEFAULT;
        cbd.CPUAccessFlags = 0;
    }

    DXCall(device->CreateBuffer(&cbd, nullptr, m_buffer.GetAddressOf()));
}

template <class T>
void ConstantBuffer<T>::ApplyChanges(ID3D11DeviceContext* deviceContext)
{
    OC_ASSERT(m_buffer.Get() != nullptr);

    // Constant buffers only have 1 subresource which is the whole buffer (index 0).
    if (m_dynamicUsage)
    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        DXCall(deviceContext->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource));
        CopyMemory(mappedResource.pData, &m_data, sizeof(T));
        deviceContext->Unmap(m_buffer.Get(), 0);
    }
    else
    {
        deviceContext->UpdateSubresource(m_buffer.Get(), 0, nullptr, &m_data, 0, 0);
    }
}

OC_NS_END;