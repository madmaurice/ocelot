

#include "effect.h"
#include "graphic/dxUtil.h"

OC_NS_BG;

Effect::Effect(const EffectDescription& desc)
    : m_desc(desc)
{
}

Effect::~Effect()
{
}

bool Effect::initialize(ID3D11Device* device)
{
    OC_LOG_INFO("Initializing effect " << m_desc.m_name);

    if (m_desc.m_vsFunc.size() > 0)
    {
        m_vs = ShaderCompiler::compileVS(device, m_desc.m_path.c_str(), m_desc.m_vsFunc.c_str());

        if (m_vs.isNull())
            return false;
    }

    if (m_desc.m_psFunc.size() > 0)
    {
        m_ps = ShaderCompiler::compilePS(device, m_desc.m_path.c_str(), m_desc.m_psFunc.c_str());

        if (m_ps.isNull())
            return false;
    }

    return true;
}

void Effect::bindShaders(ID3D11DeviceContext* context)
{
    if (!m_vs.isNull())
    {
        m_vs.bindVS(context);
    }

    if (!m_ps.isNull())
    {
        m_ps.bindPS(context);
    }

    bindResources(context);
}

ComPtr<ID3D11InputLayout> Effect::createInputLayout(ID3D11Device* device, D3D11_INPUT_ELEMENT_DESC* desc, uint32 numElements)
{
    OC_ASSERT_MSG(!m_vs.isNull(), "Cannot create input layout : No vertex shader is set!");

    ComPtr<ID3D11InputLayout> inputLayout;
    DXCall(device->CreateInputLayout(desc, numElements, m_vs.getBlob()->GetBufferPointer(),
        m_vs.getBlob()->GetBufferSize(), inputLayout.GetAddressOf()));
    return inputLayout;
}

OC_NS_END;