
#pragma once

#include "app/application.h"
#include "core/util/pointer.h"
#include "graphic/dxUtil.h"
#include "graphic/graphicSystem.h"


OC_NS_BG;

struct Vertex
{
    XMFLOAT3 pos;
    XMFLOAT4 color;
};

class Square
{
public:
    Square();
    Vertex m_vertices[4];
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

    Square m_square;

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