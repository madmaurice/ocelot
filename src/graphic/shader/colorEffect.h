
#pragma once

#include "graphic/buffer/constantBuffer.h"
#include "graphic/shader/effect.h"

struct ID3D11DeviceContext;

OC_NS_BG;

class ColorEffect : public Effect
{
public:
    struct Param
    {
        Matrix4 m_world;
        Matrix4 m_view;
        Matrix4 m_projection;
    };

    ColorEffect();

    bool initialize(ID3D11Device* device);

    void applyChanges(ID3D11DeviceContext* deviceContext);

    Param& getParam();

private:
    virtual void bindResources(ID3D11DeviceContext* context);

    ConstantBuffer<Param>  m_constantBuffer;
};

OC_NS_END;