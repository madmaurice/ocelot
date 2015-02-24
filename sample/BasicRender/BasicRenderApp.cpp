
#include "BasicRenderApp.h"
#include "graphic/model/geometryBuilder.h"

OC_NS_BG;

BasicRenderApp::BasicRenderApp()
    : Application("Basic render")
    , m_time(0)
    , m_inputLayout(nullptr)
{
    m_drawData.resize(3);

    m_drawData[0].m_material.m_ambient = Vector4(0.651f, 0.5f, 0.392f, 1.0f);
    m_drawData[0].m_material.m_diffuse = oc::Colors::Red;
    m_drawData[0].m_material.m_specular = Vector4(0.2f, 0.2f, 0.2f, 16.0f);

    m_drawData[1].m_material.m_ambient = Vector4(0.651f, 0.5f, 0.392f, 1.0f);
    m_drawData[1].m_material.m_diffuse = oc::Colors::Green;
    m_drawData[1].m_material.m_specular = Vector4(0.2f, 0.2f, 0.2f, 16.0f);

    m_drawData[2].m_material.m_ambient = Vector4(0.651f, 0.5f, 0.392f, 1.0f);
    m_drawData[2].m_material.m_diffuse = oc::Colors::Blue;
    m_drawData[2].m_material.m_specular = Vector4(0.2f, 0.2f, 0.2f, 16.0f);

    m_dirLights[0].m_ambient = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
    m_dirLights[0].m_diffuse = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
    m_dirLights[0].m_specular = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
    m_dirLights[0].m_direction = Vector3(0.57735f, -0.57735f, 0.57735f);

    m_dirLights[1].m_ambient = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    m_dirLights[1].m_diffuse = Vector4(0.20f, 0.20f, 0.20f, 1.0f);
    m_dirLights[1].m_specular = Vector4(0.25f, 0.25f, 0.25f, 1.0f);
    m_dirLights[1].m_direction = Vector3(-0.57735f, -0.57735f, 0.57735f);

    m_dirLights[2].m_ambient = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    m_dirLights[2].m_diffuse = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
    m_dirLights[2].m_specular = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    m_dirLights[2].m_direction = Vector3(0.0f, -0.707f, -0.707f);
}

BasicRenderApp::~BasicRenderApp()
{
}

bool BasicRenderApp::initializeImpl()
{
    m_dxDevice = m_graphic->getDevice();
    m_dxImmediateContext = m_graphic->getDeviceContext();

    // Create mesh
    std::shared_ptr<GeometryBuilder> geoBuilder = m_graphic->getGeometryBuilder();
    m_drawData[0].m_cubeMesh = geoBuilder->createCube(1, 1, 1);
    m_drawData[1].m_cubeMesh = geoBuilder->createCube(2, 2, 2);
    m_drawData[2].m_cubeMesh = geoBuilder->createCube(1, 1, 1);

    // Initialize the shaders
    m_basicEffect.initialize(m_dxDevice.Get());

    // Defined then create the vertex input layout.
    MeshVertexDeclaration vDecl = MeshVertex::getVertexDeclaration();
    m_inputLayout = m_basicEffect.createInputLayout(m_dxDevice.Get(), vDecl.m_desc, vDecl.m_numElements);

    // Initialize matrix
    m_drawData[0].m_world = Matrix4::translationMatrix(-5, -5, -5);
    m_drawData[1].m_world = Matrix4::translationMatrix(0, 0, 0);
    m_drawData[2].m_world = Matrix4::translationMatrix(5, 5, 5);

    // View
    Vector3 eye(0.0f, 2.0f, -10.0f);
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
}

void BasicRenderApp::renderImpl()
{
    m_dxImmediateContext->IASetInputLayout(m_inputLayout.Get());
    m_dxImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Update constant buffer
    // Why the transpose : http://www.gamedev.net/topic/574593-direct3d11-why-need-transpose/
    BasicEffect::FrameParam& frameParam = m_basicEffect.getFrameParam();
    frameParam.m_lights[0] = m_dirLights[0];
    frameParam.m_lights[1] = m_dirLights[1];
    frameParam.m_lights[2] = m_dirLights[2];
    frameParam.m_eyePosW = Vector3(0.0f, 2.0f, -10.0f);

    m_basicEffect.bindShaders(m_dxImmediateContext.Get());

    for (auto& drawData : m_drawData)
    {
        // Animate the cubes
        drawData.m_world = drawData.m_world * Matrix4::rotationMatrixY(0.04f);

        BasicEffect::ObjParam& objParam = m_basicEffect.getObjParam();
        objParam.m_world = drawData.m_world.transpose();
        objParam.m_worldInvTranspose = drawData.m_world.inverse(); // Don't think I need to transpose here
        objParam.m_worldViewProj = (drawData.m_world * m_view * m_projection).transpose();
        objParam.m_material = drawData.m_material;

        m_basicEffect.applyChanges(m_dxImmediateContext.Get());

        UINT stride = sizeof(MeshVertex);
        UINT offset = 0;
        m_dxImmediateContext->IASetVertexBuffers(0, 1, drawData.m_cubeMesh.getVertexBuffer(), &stride, &offset);
        //The only formats allowed for index buffer data are 16-bit (DXGI_FORMAT_R16_UINT) and 32-bit (DXGI_FORMAT_R32_UINT) integers.
        m_dxImmediateContext->IASetIndexBuffer(drawData.m_cubeMesh.getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

        m_dxImmediateContext->DrawIndexed(36, 0, 0);
    }
}

OC_NS_END;