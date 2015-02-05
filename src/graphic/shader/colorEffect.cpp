

#include "colorEffect.h"

OC_NS_BG;

ColorEffect::ColorEffect()
    : Effect({ "Color", "color.hlsl", "VS", "PS" })
{
}

bool ColorEffect::initialize(ID3D11Device* device)
{
    if (!Effect::initialize(device))
        return false;

    m_constantBuffer.initialize(device);

    return true;
}

void ColorEffect::applyChanges(ID3D11DeviceContext* deviceContext)
{
    m_constantBuffer.applyChanges(deviceContext);
}

ColorEffect::Param& ColorEffect::getParam()
{
    return m_constantBuffer.m_data;
}

void ColorEffect::bindResources(ID3D11DeviceContext* context)
{
    context->VSSetConstantBuffers(0, 1, m_constantBuffer);
}

OC_NS_END;