
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

Square::Square()
{
    m_vertices[0].pos = XMFLOAT3(-0.5f, 0.5f, 0.5f);
    m_vertices[0].color = (const float*)&Colors::Green;
    m_vertices[1].pos = XMFLOAT3(0.5f, 0.5f, 0.5f);
    m_vertices[1].color = (const float*)&Colors::Cyan;
    m_vertices[2].pos = XMFLOAT3(0.5f, -0.5f, 0.5f);
    m_vertices[2].color = (const float*)&Colors::Red;
    m_vertices[3].pos = XMFLOAT3(-0.5f, -0.5f, 0.5f);
    m_vertices[3].color = (const float*)&Colors::Yellow;
}

BasicRenderApp::BasicRenderApp()
    : Application("Basic render")
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
    bd.ByteWidth = sizeof(Vertex) * 4;  // Square
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = m_square.m_vertices;
    DXCall(m_dxDevice->CreateBuffer(&bd, &initData, m_vertexBuffer.GetAddressOf()));

    // Create the indice buffers for the square
    UINT indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = sizeof(UINT) * 6;
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

    return true;
}

void BasicRenderApp::shutdownImpl()
{
}

void BasicRenderApp::updateImpl(float elapsed)
{
    OC_UNUSED(elapsed);
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
    m_dxImmediateContext->PSSetShader(m_pixelShader.Get(), NULL, 0);

    m_dxImmediateContext->DrawIndexed(6, 0, 0);
}

OC_NS_END;