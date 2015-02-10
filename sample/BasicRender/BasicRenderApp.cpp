
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

ColorCube::ColorCube()
{
    // Top vertices
    m_vertices[0].pos = Vector3(-1.0f, 1.0f, -1.0f);
    m_vertices[0].color = Colors::Green;
    m_vertices[1].pos = Vector3(1.0f, 1.0f, -1.0f);
    m_vertices[1].color = Colors::Cyan;
    m_vertices[2].pos = Vector3(1.0f, 1.0f, 1.0f);
    m_vertices[2].color = Colors::Red;
    m_vertices[3].pos = Vector3(-1.0f, 1.0f, 1.0f);
    m_vertices[3].color = Colors::Yellow;

    // Bottom vertices
    m_vertices[4].pos = Vector3(-1.0f, -1.0f, -1.0f);
    m_vertices[4].color = Colors::Pink;
    m_vertices[5].pos = Vector3(1.0f, -1.0f, -1.0f);
    m_vertices[5].color = Colors::Blue;
    m_vertices[6].pos = Vector3(1.0f, -1.0f, 1.0f);
    m_vertices[6].color = Colors::Gray;
    m_vertices[7].pos = Vector3(-1.0f, -1.0f, 1.0f);
    m_vertices[7].color = Colors::Brown;
}

BasicRenderApp::BasicRenderApp()
    : Application("Basic render")
    , m_time(0)
    , m_inputLayout(nullptr)
{
}

BasicRenderApp::~BasicRenderApp()
{
}

bool BasicRenderApp::initializeImpl()
{
    m_dxDevice = m_graphic->getDevice();
    m_dxImmediateContext = m_graphic->getDeviceContext();

    // Create vertex buffer
    m_vertexBuffer.initialize(m_dxDevice.Get(), sizeof(Vertex) * 8, m_cube.m_vertices);

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

    // 36 vertices needed for 12 triangles in a triangle list
    m_indexBuffer.initialize(m_dxDevice.Get(), indices, 36);

    // Initialize the shaders
    m_colorEffect.initialize(m_dxDevice.Get());

    // Defined then create the vertex input layout.
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    m_inputLayout = m_colorEffect.createInputLayout(m_dxDevice.Get(), vertexDesc, 2);

    // Initialize matrix
    m_world = Matrix4::identity();

    // View
    Vector3 eye(0.0f, 2.0f, -4.0f);
    Vector3 at(0.0f, -1.0f, 0.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);
    m_view = Matrix4::lookAtLHMatrix(eye, at, up);

    // TODO : resize break the projection matrix

    // Initialize the projection matrix
    const float aspectRatio = (float)m_graphic->getBackBufferWidth() / (float)m_graphic->getBackBufferHeigth();
    m_projection = Matrix4::perspectiveFovLHMatrix(OC_PIDIV2, aspectRatio, 0.01f, 100.0f);

    return true;
}

void BasicRenderApp::shutdownImpl()
{
}

void BasicRenderApp::updateImpl(float elapsed)
{
    m_time += elapsed;

    // Animate the cube
    m_world = Matrix4::rotationMatrixY(m_time);

    // Update constant buffer
    // Why the transpose : http://www.gamedev.net/topic/574593-direct3d11-why-need-transpose/
    ColorEffect::Param& effectParam = m_colorEffect.getParam();
    effectParam.m_world = m_world.transpose();
    effectParam.m_view = m_view.transpose();
    effectParam.m_projection = m_projection.transpose();

    m_colorEffect.applyChanges(m_dxImmediateContext.Get());
}

void BasicRenderApp::renderImpl()
{
    m_dxImmediateContext->IASetInputLayout(m_inputLayout.Get());
    m_dxImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    m_dxImmediateContext->IASetVertexBuffers(0, 1, m_vertexBuffer, &stride, &offset);
    //The only formats allowed for index buffer data are 16-bit (DXGI_FORMAT_R16_UINT) and 32-bit (DXGI_FORMAT_R32_UINT) integers.
    m_dxImmediateContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    m_colorEffect.bindShaders(m_dxImmediateContext.Get());

    m_dxImmediateContext->DrawIndexed(36, 0, 0);
}

OC_NS_END;