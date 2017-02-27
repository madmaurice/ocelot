
#pragma once

#include "app/Application.h"
#include "core/util/ComPtr.h"
#include "graphic/util/DxUtil.h"
#include "graphic/Graphic.h"
#include "graphic/buffer/ConstantBuffer.h"
#include "graphic/buffer/IndexBuffer.h"
#include "graphic/buffer/VertexBuffer.h"
#include "graphic/util/GeometryBuilder.h"
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


    Matrix4 m_view;
    Matrix4 m_projection;

    GraphicDevice m_dxDevice;
    GraphicDeviceContext m_dxImmediateContext;

    ComPtr<ID3D11InputLayout>           m_inputLayout;

    Cube m_cube;
    Matrix4 m_world;
};

OC_NS_END;