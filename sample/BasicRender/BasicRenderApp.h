
#pragma once

#include "app/application.h"
#include "core/util/pointer.h"
#include "graphic/dxUtil.h"
#include "graphic/graphicSystem.h"
#include "graphic/buffer/constantBuffer.h"
#include "graphic/buffer/indexBuffer.h"
#include "graphic/buffer/vertexBuffer.h"
#include "graphic/model/shape.h"
#include "graphic/shader/basicEffect.h"
#include "math/math.h"


OC_NS_BG;

struct DrawData
{
    Cube m_cubeMesh;
    Material m_material;
    Matrix4 m_world;
};

class BasicRenderApp : public Application
{
public:
    BasicRenderApp();
    virtual ~BasicRenderApp();

private:
    virtual bool initializeImpl();
    virtual void shutdownImpl();

    virtual void updateImpl(float elapsed);
    virtual void renderImpl();

    std::vector<DrawData> m_drawData;
    DirectionalLight m_dirLights[3];

    float m_time;
    Matrix4 m_view;
    Matrix4 m_projection;

    BasicEffect m_basicEffect;

    // NOTE : temporary...
    ComPtr<ID3D11Device> m_dxDevice;
    ComPtr<ID3D11DeviceContext> m_dxImmediateContext;

    ComPtr<ID3D11InputLayout>           m_inputLayout;
};

OC_NS_END;