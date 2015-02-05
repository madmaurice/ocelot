
#pragma once

#include "core/util/nonCopyable.h"
#include "graphic/shader/shader.h"

OC_NS_BG;

struct EffectDescription
{
    String m_name;
    String m_path;
    String m_vsFunc;
    String m_psFunc;
};


class Effect
{
public:

    virtual ~Effect();

    // Set all compiled shader
    void bindShaders(ID3D11DeviceContext* context);

    ComPtr<ID3D11InputLayout> createInputLayout(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* desc, uint32 numElements);

protected:

    explicit Effect(const EffectDescription& desc);

    virtual void bindResources(ID3D11DeviceContext* context) = 0;

    bool initialize(ID3D11Device* device);

    EffectDescription   m_desc;

    VertexShader        m_vs;
    PixelShader         m_ps;
};



OC_NS_END;