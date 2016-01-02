
#pragma once

#include "app/Application.h"
#include "core/util/ComPtr.h"
#include "graphic/util/DxUtil.h"
#include "graphic/GraphicSystem.h"
#include "graphic/buffer/ConstantBuffer.h"
#include "graphic/buffer/IndexBuffer.h"
#include "graphic/buffer/VertexBuffer.h"
#include "graphic/model/Shape.h"
#include "math/Math.h"


OC_NS_BG;

class BasicSceneApp : public Application
{
public:
    BasicSceneApp();
    virtual ~BasicSceneApp();

private:
    virtual bool InitializeImpl();
    virtual void ShutdownImpl();

    virtual void UpdateImpl(float elapsed);
    virtual void RenderImpl();


    float m_time;
    Matrix4 m_view;
    Matrix4 m_projection;

    ComPtr<ID3D11Device> m_dxDevice;
    ComPtr<ID3D11DeviceContext> m_dxImmediateContext;

    ComPtr<ID3D11InputLayout>           m_inputLayout;
};

OC_NS_END;