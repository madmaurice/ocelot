

#include "basicEffect.h"

OC_NS_BG;

BasicEffect::BasicEffect()
    : Effect({ "Basic", "basicEffect.hlsl", "VS", "PS" })
{
}

bool BasicEffect::initialize(ID3D11Device* device)
{
    if (!Effect::initialize(device))
        return false;

    m_cbFrame.initialize(device);
    m_cbObj.initialize(device);

    return true;
}

void BasicEffect::applyChanges(ID3D11DeviceContext* deviceContext)
{
    m_cbFrame.applyChanges(deviceContext);
    m_cbObj.applyChanges(deviceContext);
}

void BasicEffect::bindResources(ID3D11DeviceContext* context)
{
    context->VSSetConstantBuffers(0, 1, m_cbFrame);
    context->VSSetConstantBuffers(1, 1, m_cbObj);

    context->PSSetConstantBuffers(0, 1, m_cbFrame);
    context->PSSetConstantBuffers(1, 1, m_cbObj);
}

BasicEffect::FrameParam& BasicEffect::getFrameParam()
{
    return m_cbFrame.m_data;
}

BasicEffect::ObjParam& BasicEffect::getObjParam()
{
    return m_cbObj.m_data;
}

OC_NS_END;