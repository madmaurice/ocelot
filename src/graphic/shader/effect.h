
#pragma once

#include "core/util/nonCopyable.h"
#include "graphic/shader/shader.h"

OC_NS_BG;

struct EffectDescription
{
    String m_path;
    String m_vsFunc;
    String m_psFunc;
};


class Effect
{
public:

    // Set all compiled shader
    void bindShaders(ID3D11DeviceContext* context);

protected:

    explicit Effect(const String& name);

    bool initialize(ID3D11Device* device, const EffectDescription& desc);

    String              m_name;
    String              m_path;

    VertexShader        m_vs;
    PixelShader         m_ps;
};



OC_NS_END;