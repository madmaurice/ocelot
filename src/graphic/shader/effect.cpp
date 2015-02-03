

#include "effect.h"

OC_NS_BG;

Effect::Effect(const String& name)
    : m_name(name)
{
}

bool Effect::initialize(ID3D11Device* device, const EffectDescription& desc)
{
    OC_LOG_INFO("Initializing effect " << m_name);
    m_path = desc.m_path;

    if (desc.m_vsFunc.size() > 0)
    {
        m_vs = ShaderCompiler::compileVS(device, m_path.c_str(), desc.m_vsFunc.c_str());

        if (m_vs.isNull())
            return false;
    }

    if (desc.m_psFunc.size() > 0)
    {
        m_ps = ShaderCompiler::compilePS(device, m_path.c_str(), desc.m_psFunc.c_str());

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
}


OC_NS_END;