
#pragma once

#include "app/application.h"
#include "core/util/pointer.h"
#include "graphic/dxUtil.h"
#include "graphic/graphicSystem.h"
#include "graphic/buffer/constantBuffer.h"
#include "graphic/buffer/indexBuffer.h"
#include "graphic/buffer/vertexBuffer.h"
#include "math/math.h"


OC_NS_BG;

struct ConstantBufferData
{
    Matrix4 m_world;
    Matrix4 m_view;
    Matrix4 m_projection;
};

struct Vertex
{
    Vector3 pos;
    Vector4 color;
};

class Cube
{
public:
    Cube();
    Vertex m_vertices[8];
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

    Cube m_cube;
    float m_time;
    Matrix4 m_world;
    Matrix4 m_view;
    Matrix4 m_projection;

    // NOTE : temporary...
    ComPtr<ID3D11Device> m_dxDevice;
    ComPtr<ID3D11DeviceContext> m_dxImmediateContext;

    VertexBuffer                        m_vertexBuffer;
    IndexBuffer                         m_indexBuffer;
    ConstantBuffer<ConstantBufferData>  m_constantBuffer;
    ComPtr<ID3D11InputLayout>           m_inputLayout;
    ComPtr<ID3D11VertexShader>          m_vertexShader;
    ComPtr<ID3D11PixelShader>           m_pixelShader;
};

OC_NS_END;