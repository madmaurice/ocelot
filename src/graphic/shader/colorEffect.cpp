

#include "colorEffect.h"

OC_NS_BG;

ColorEffect::ColorEffect()
    : Effect("Color")
{
}

bool ColorEffect::initialize(ID3D11Device* device)
{
    EffectDescription desc = { "color.hlsl", "VS", "PS" };
    return Effect::initialize(device, desc);
}

void ColorEffect::applyChanges(ID3D11DeviceContext* deviceContext)
{
    m_constantBuffer.applyChanges(deviceContext);
}

ColorEffect::Param& ColorEffect::getParam()
{
    return m_constantBuffer.m_data;
}

OC_NS_END;