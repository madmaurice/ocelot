
#include "BasicRenderApp.h"
#include <d3dcompiler.h>

OC_NS_BG;

namespace 
{
    bool CompileShaderFromFile(char* szFileName, const char* szEntryPoint, const char* szShaderModel, ID3DBlob** ppBlobOut)
    {
        HRESULT hr = S_OK;
        bool retVal = true;

        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
    #if defined( DEBUG ) || defined( _DEBUG )
        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience, but still allows 
        // the shaders to be optimized and to run exactly the way they will run in 
        // the release configuration of this program.
        dwShaderFlags |= D3DCOMPILE_DEBUG;
    #endif

        ID3DBlob* pErrorBlob;
        hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
            dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);

        if (FAILED(hr))
        {
            retVal = false;

            if (pErrorBlob != NULL)
                OC_LOG_ERROR((char*)pErrorBlob->GetBufferPointer());
        }

        if (pErrorBlob) 
            pErrorBlob->Release();

        return retVal;
    }
}

Cube::Cube()
{
    // Top vertices
    m_vertices[0].pos = XMFLOAT3(-1.0f, 1.0f, -1.0f);
    m_vertices[0].color = (const float*)&Colors::Green;
    m_vertices[1].pos = XMFLOAT3(1.0f, 1.0f, -1.0f);
    m_vertices[1].color = (const float*)&Colors::Cyan;
    m_vertices[2].pos = XMFLOAT3(1.0f, 1.0f, 1.0f);
    m_vertices[2].color = (const float*)&Colors::Red;
    m_vertices[3].pos = XMFLOAT3(-1.0f, 1.0f, 1.0f);
    m_vertices[3].color = (const float*)&Colors::Yellow;

    // Bottom vertices
    m_vertices[4].pos = XMFLOAT3(-1.0f, -1.0f, -1.0f);
    m_vertices[4].color = (const float*)&Colors::Pink;
    m_vertices[5].pos = XMFLOAT3(1.0f, -1.0f, -1.0f);
    m_vertices[5].color = (const float*)&Colors::Blue;
    m_vertices[6].pos = XMFLOAT3(1.0f, -1.0f, 1.0f);
    m_vertices[6].color = (const float*)&Colors::Gray;
    m_vertices[7].pos = XMFLOAT3(-1.0f, -1.0f, 1.0f);
    m_vertices[7].color = (const float*)&Colors::Brown;
}

BasicRenderApp::BasicRenderApp()
    : Application("Basic render")
    , m_time(0)
    , m_vertexBuffer(nullptr)
    , m_indexBuffer(nullptr)
    , m_inputLayout(nullptr)
    , m_vertexShader(nullptr)
    , m_pixelShader(nullptr)
{
}

BasicRenderApp::~BasicRenderApp()
{
}

bool BasicRenderApp::initializeImpl()
{
    m_dxDevice = m_graphicSystem->getDevice();
    m_dxImmediateContext = m_graphicSystem->getDeviceContext();

    // Create vertex buffer
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Vertex) * 8;  // Cube
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = m_cube.m_vertices;
    DXCall(m_dxDevice->CreateBuffer(&bd, &initData, m_vertexBuffer.GetAddressOf()));

    // Create the indice buffers for the cube
    UINT indices[] =
    {
        3, 1, 0,
        2, 1, 3,

        0, 5, 4,
        1, 5, 0,

        3, 4, 7,
        0, 4, 3,

        1, 6, 5,
        2, 6, 1,

        2, 7, 6,
        3, 7, 2,

        6, 4, 5,
        7, 4, 6,
    };

    D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = sizeof(UINT) * 36;        // 36 vertices needed for 12 triangles in a triangle list
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    ibd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = indices;
    DXCall(m_dxDevice->CreateBuffer(&ibd, &iinitData, m_indexBuffer.GetAddressOf()));

    // Compile the vertex shader
    ComPtr<ID3DBlob> pVSBlob = nullptr;
    DXCall(CompileShaderFromFile("shader.hlsl", "VS", "vs_4_0", pVSBlob.GetAddressOf()));

    // Create the vertex shader
    DXCall(m_dxDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, m_vertexShader.GetAddressOf()));

    // Defined then create the vertex input layout.
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    // Create the input layout to describe the input-buffer data for the input-assembler stage.
    // This map our vertex structure to the corresponding input of the vertex shader
    m_dxDevice->CreateInputLayout(vertexDesc, 2, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), m_inputLayout.GetAddressOf());

    // Compile the pixel shader
    ComPtr<ID3DBlob> pPSBlob = nullptr;
    DXCall(CompileShaderFromFile("shader.hlsl", "PS", "ps_4_0", pPSBlob.GetAddressOf()));

    // Create pixel shader
    DXCall(m_dxDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, m_pixelShader.GetAddressOf()));

    // Create constant buffer
    D3D11_BUFFER_DESC cbd;
    cbd.Usage = D3D11_USAGE_DEFAULT;
    cbd.ByteWidth = sizeof(ConstantBuffer);
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = 0;
    cbd.MiscFlags = 0;
    cbd.StructureByteStride = 0;
    // TODO : set init data?
    //D3D11_SUBRESOURCE_DATA cbInitData;
    //cbInitData.pSysMem = ;
    DXCall(m_dxDevice->CreateBuffer(&cbd, NULL, m_constantBuffer.GetAddressOf()));

    // Initialize matrix
    m_world = XMMatrixIdentity();

    // View
    XMVECTOR eye = XMVectorSet(0.0f, 2.0f, -4.0f, 0.0f);
    XMVECTOR at = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    m_view = XMMatrixLookAtLH(eye, at, up);

    // TODO : resize break the projection matrix

    // Initialize the projection matrix
    const float aspectRatio = (float)m_graphicSystem->getBackBufferWidth() / (float)m_graphicSystem->getBackBufferHeigth();
    m_projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, aspectRatio, 0.01f, 100.0f);

    return true;
}

void BasicRenderApp::shutdownImpl()
{
}

void BasicRenderApp::updateImpl(float elapsed)
{
    m_time += elapsed;

    // Animate the cube
    m_world = XMMatrixRotationY(m_time);

    // Update constant buffer
    ConstantBuffer cb;
    // Why the transpose : http://www.gamedev.net/topic/574593-direct3d11-why-need-transpose/
    cb.m_world = XMMatrixTranspose(m_world);
    cb.m_view = XMMatrixTranspose(m_view);
    cb.m_projection = XMMatrixTranspose(m_projection);
    m_dxImmediateContext->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cb, 0, 0);
}

void BasicRenderApp::renderImpl()
{
    m_dxImmediateContext->IASetInputLayout(m_inputLayout.Get());
    m_dxImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_dxImmediateContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
    //The only formats allowed for index buffer data are 16-bit (DXGI_FORMAT_R16_UINT) and 32-bit (DXGI_FORMAT_R32_UINT) integers.
    m_dxImmediateContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

    m_dxImmediateContext->VSSetShader(m_vertexShader.Get(), NULL, 0);
    m_dxImmediateContext->VSSetConstantBuffers(0, 1, m_constantBuffer.GetAddressOf());
    m_dxImmediateContext->PSSetShader(m_pixelShader.Get(), NULL, 0);

    m_dxImmediateContext->DrawIndexed(36, 0, 0);
}

OC_NS_END;