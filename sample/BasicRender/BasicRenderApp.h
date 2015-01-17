
#pragma once

#include "app/application.h"
#include "core/util/pointer.h"
#include "graphic/dxUtil.h"
#include "graphic/graphicSystem.h"
#include "math/math.h"


OC_NS_BG;

struct ConstantBuffer
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
    ComPtr<ID3D11Buffer>  m_constantBuffer;

    // NOTE : temporary...
    ComPtr<ID3D11Device> m_dxDevice;
    ComPtr<ID3D11DeviceContext> m_dxImmediateContext;

    ComPtr<ID3D11Buffer>           m_vertexBuffer;
    ComPtr<ID3D11Buffer>           m_indexBuffer;
    ComPtr<ID3D11InputLayout>      m_inputLayout;
    ComPtr<ID3D11VertexShader>     m_vertexShader;
    ComPtr<ID3D11PixelShader>      m_pixelShader;
};

OC_NS_END;