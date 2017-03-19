
#include "BasicSceneApp.h"
#include "app/Input.h"
#include "graphic/shader/Shader.h"


OC_NS_BG;

// TODO : move all that
struct Material
{
    Material()
    {
        ZeroMemory(this, sizeof(this));
    }

    Vector4 m_ambient;
    Vector4 m_diffuse;
    Vector4 m_specular;
    Vector4 m_reflect;
};

static Material s_material;

// Note: Make sure structure alignment agrees with HLSL structure padding rules. 
//   Elements are packed into 4D vectors with the restriction that an element
//   cannot straddle a 4D vector boundary.
struct DirectionalLight
{
    DirectionalLight() { ZeroMemory(this, sizeof(this)); }

    Vector4 m_ambient;
    Vector4 m_diffuse;
    Vector4 m_specular;
    Vector3 m_direction;
    float pad; // pad the last float so we can set an array of lights if we wanted.
};

static DirectionalLight s_dirLights[3];


struct EffectDescription
{
    String m_name;
    String m_path;
    String m_vsFunc;
    String m_psFunc;
};

class BasicEffect
{
public:
    struct FrameParam
    {
        DirectionalLight m_lights[3];
        Vector3 m_eyePosW;
    };

    struct ObjParam
    {
        Matrix4 m_world;
        Matrix4 m_worldInvTranspose;
        Matrix4 m_worldViewProj;
        Material m_material;
    };

    BasicEffect();

    bool Initialize();

    void ApplyChanges();

    void BindShaders();

    ComPtr<ID3D11InputLayout> CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, uint32 numElements);

    FrameParam& GetFrameParam() { return m_cbFrame.m_data; }
    ObjParam& GetObjParam() { return m_cbObj.m_data; }

private:
    EffectDescription m_desc;

    ConstantBuffer<FrameParam> m_cbFrame;
    ConstantBuffer<ObjParam> m_cbObj;

    VertexShader        m_vs;
    PixelShader         m_ps;
};

BasicEffect::BasicEffect()
    : m_desc({ "Basic", "basicEffect.hlsl", "VS", "PS" })
{
}

bool BasicEffect::Initialize()
{
    OC_LOG_INFO("Initializing effect " << m_desc.m_name);

    if (m_desc.m_vsFunc.size() > 0)
    {
        m_vs = ShaderCompiler::CompileVS(m_desc.m_path.c_str(), m_desc.m_vsFunc.c_str());

        if (m_vs.IsNull())
            return false;
    }

    if (m_desc.m_psFunc.size() > 0)
    {
        m_ps = ShaderCompiler::CompilePS(m_desc.m_path.c_str(), m_desc.m_psFunc.c_str());

        if (m_ps.IsNull())
            return false;
    }

    m_cbFrame.Initialize();
    m_cbObj.Initialize();

    return true;
}

void BasicEffect::ApplyChanges()
{
    m_cbFrame.ApplyChanges();
    m_cbObj.ApplyChanges();
}

void BasicEffect::BindShaders()
{
    m_vs.BindVS();
    m_ps.BindPS();

    // TODO : What are the params?
    // Bind shader resources
    Graphic::GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cbFrame);
    Graphic::GetDeviceContext()->VSSetConstantBuffers(1, 1, m_cbObj);

    Graphic::GetDeviceContext()->PSSetConstantBuffers(0, 1, m_cbFrame);
    Graphic::GetDeviceContext()->PSSetConstantBuffers(1, 1, m_cbObj);
}

ComPtr<ID3D11InputLayout> BasicEffect::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* desc, uint32 numElements)
{
    OC_ASSERT_MSG(!m_vs.IsNull(), "Cannot create input layout : No vertex shader is set!");

    ComPtr<ID3D11InputLayout> inputLayout;
    DXCall(Graphic::GetDevice()->CreateInputLayout(desc, numElements, m_vs.GetBlob()->GetBufferPointer(),
        m_vs.GetBlob()->GetBufferSize(), inputLayout.GetAddressOf()));
    return inputLayout;
}

static BasicEffect s_effect;

BasicSceneApp::BasicSceneApp()
    : Application("Scene app")
    , m_camera((float)m_window.GetWidth() / (float)m_window.GetHeight(), OC_PIDIV2, 0.01f, 1000.0f)
{
    // Material
    s_material.m_ambient = Vector4(0.651f, 0.5f, 0.392f, 1.0f);
    s_material.m_diffuse = OC::Colors::Green;
    s_material.m_specular = Vector4(0.2f, 0.2f, 0.2f, 16.0f);

    // Lights
    s_dirLights[0].m_ambient = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
    s_dirLights[0].m_diffuse = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
    s_dirLights[0].m_specular = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
    s_dirLights[0].m_direction = Vector3(0.57735f, -0.57735f, 0.57735f);

    s_dirLights[1].m_ambient = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    s_dirLights[1].m_diffuse = Vector4(0.20f, 0.20f, 0.20f, 1.0f);
    s_dirLights[1].m_specular = Vector4(0.25f, 0.25f, 0.25f, 1.0f);
    s_dirLights[1].m_direction = Vector3(-0.57735f, -0.57735f, 0.57735f);

    s_dirLights[2].m_ambient = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    s_dirLights[2].m_diffuse = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
    s_dirLights[2].m_specular = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    s_dirLights[2].m_direction = Vector3(0.0f, -0.707f, -0.707f);
}

BasicSceneApp::~BasicSceneApp()
{
}

bool BasicSceneApp::InitializeImpl()
{
    m_dxDevice = Graphic::GetDevice();
    m_dxImmediateContext = Graphic::GetDeviceContext();

    // TODO : Make mesh class lightweight to copy

    // TODO : Geo builder, put mesh construction in it
    GeometryBuilder geoBuilder;
    m_cube = geoBuilder.CreateCube(10, 10, 10);

    // Shader
    s_effect.Initialize();

    // Input layout 
    static D3D11_INPUT_ELEMENT_DESC vertexDeclaration[3] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    m_inputLayout = s_effect.CreateInputLayout(vertexDeclaration, 3);

    // Initialize matrix
    m_world = Matrix4::TranslationMatrix(Vector3(0, 0, 10));

    // Camera
    Vector3 eye(0.0f, 2.0f, -20.0f);
    Vector3 at(0.0f, -1.0f, 0.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);
    // TODO : resize break the projection matrix
    m_camera.SetPosition(eye);

    return true;
}

void BasicSceneApp::ShutdownImpl()
{
}

void BasicSceneApp::UpdateImpl(float elapsed)
{
    // Rotate cube
    float rot = 2 * elapsed;
    m_world = Matrix4::RotationY(rot) * m_world;

    // Process input
    MouseState mouseState = MouseState::GetMouseState(m_window.GetHandle());
    KeyboardState kbState = KeyboardState::GetKeyboardState(m_window.GetHandle());

    float camMoveSpeed = 20.0f * elapsed;
    const float camRotSpeed = 0.1f * elapsed;

    // Move the camera with keyboard input
    if (kbState.IsKeyDown(Key::LeftShift))
        camMoveSpeed *= 0.25f;

    Vector3 camPos = m_camera.GetPosition();
    if (kbState.IsKeyDown(Key::W))
        camPos += m_camera.Forward() * camMoveSpeed;
    else if (kbState.IsKeyDown(Key::S))
        camPos += m_camera.Back() * camMoveSpeed;
    if (kbState.IsKeyDown(Key::A))
        camPos += m_camera.Left() * camMoveSpeed;
    else if (kbState.IsKeyDown(Key::D))
        camPos += m_camera.Right() * camMoveSpeed;
    if (kbState.IsKeyDown(Key::Q))
        camPos += m_camera.Up() * camMoveSpeed;
    else if (kbState.IsKeyDown(Key::E))
        camPos += m_camera.Down() * camMoveSpeed;

    m_camera.SetPosition(camPos);

    // Rotate camera
    if (mouseState.RButton.IsPressed && mouseState.IsOverWindow)
    {
        float xRot = m_camera.GetXRotation();
        float yRot = m_camera.GetYRotation();
        xRot += mouseState.DY * camRotSpeed;
        yRot += mouseState.DX * camRotSpeed;
        OC_LOG_DEBUG("xRot=" << xRot << "yRot=" << yRot);
        m_camera.SetXRotation(xRot);
        m_camera.SetYRotation(yRot);
    }
}

void BasicSceneApp::RenderImpl()
{
    m_dxImmediateContext->IASetInputLayout(m_inputLayout.Get());
    m_dxImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Update constant buffer
    BasicEffect::FrameParam& frameParam = s_effect.GetFrameParam();
    frameParam.m_lights[0] = s_dirLights[0];
    frameParam.m_lights[1] = s_dirLights[1];
    frameParam.m_lights[2] = s_dirLights[2];

    // TODO : ?????
    frameParam.m_eyePosW = Vector3(0.0f, 2.0f, -20.0f);

    s_effect.BindShaders();

    // Why the transpose : http://www.gamedev.net/topic/574593-direct3d11-why-need-transpose/
    BasicEffect::ObjParam& objParam = s_effect.GetObjParam();
    objParam.m_world = m_world.Transpose();

    // World inverse transpose : used to keep normal vector orthogonal in case of non-uniform scaling matrix
    // If uniform scaling : the world matrix works
    objParam.m_worldInvTranspose = m_world.Inverse(); //.Transpose(); // Don't think I need to transpose here
    objParam.m_worldViewProj = (m_world * m_camera.GetViewProjection()).Transpose();
    objParam.m_material = s_material;

    s_effect.ApplyChanges();

    UINT stride = sizeof(MeshVertex);
    UINT offset = 0;
    m_dxImmediateContext->IASetVertexBuffers(0, 1, m_cube.GetVertexBuffer(), &stride, &offset);
    //The only formats allowed for index buffer data are 16-bit (DXGI_FORMAT_R16_UINT) and 32-bit (DXGI_FORMAT_R32_UINT) integers.
    m_dxImmediateContext->IASetIndexBuffer(m_cube.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

    m_dxImmediateContext->DrawIndexed(36, 0, 0);
}

void BasicSceneApp::OnResize(uint32 width, uint32 height)
{
    Application::OnResize(width, height);
    float aspect = static_cast<float>(Graphic::GetBackBufferWidth()) / static_cast<float>(Graphic::GetBackBufferHeigth());
    m_camera.SetAspectRatio(aspect);
}

OC_NS_END;