

#pragma comment(lib, "D3D11.lib")

#include "Graphic.h"
#include "graphic/util/DxUtil.h"
#include "graphic/util/GeometryBuilder.h"


OC_NS_BG;

GraphicConfig Graphic::m_config;
ComPtr<IDXGISwapChain> Graphic::m_swapChain;
ComPtr<ID3D11RenderTargetView> Graphic::m_backBufferRTV;
ComPtr<ID3D11Texture2D> Graphic::m_depthStencilBuffer;
ComPtr<ID3D11DepthStencilView> Graphic::m_depthStencilView;

D3D11_VIEWPORT Graphic::m_viewport;

HWND Graphic::m_hwnd = 0;
uint32 Graphic::m_backBufferWidth = 0;
uint32 Graphic::m_backBufferHeigth = 0;

GraphicDevice Graphic::m_dxDevice;
GraphicDeviceContext Graphic::m_dxImmediateContext;

bool Graphic::Initialize(HWND hwnd, uint32 windowWidth, uint32 windowHeight)
{
    // No MSAA
    GraphicConfig config = { windowWidth, windowHeight, 1, 0, false, false, false };
    return Initialize(hwnd, config);
}

bool Graphic::Initialize(HWND hwnd, const GraphicConfig& config)
{
    OC_LOG_INFO("GraphicSystem initializing");

    m_hwnd = hwnd;
    m_config = config;

    m_backBufferWidth = m_config.m_windowWitdh;
    m_backBufferHeigth = m_config.m_windowHeight;

    OC_ASSERT_MSG(m_config.m_MSAASample > 0, "Invalid MSAA samples!"); // Minimum is 1

    // Create the device and device context.
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#if defined(OC_DEBUG)  
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hr = D3D11CreateDevice(
        0,                 // default adapter
        D3D_DRIVER_TYPE_HARDWARE,
        0,                 // no software device
        createDeviceFlags,
        0,                 // default feature level array (select greatest supported -> DX11)
        0,                 // number of feature level in the array above 
        D3D11_SDK_VERSION, //SDK version
        m_dxDevice.GetAddressOf(),  //Created device
        &featureLevel,              //Selected feature level
        m_dxImmediateContext.GetAddressOf());  //Device context

    if (FAILED(hr))
    {
        OC_LOG_ERROR("D3D11CreateDevice failed");
        return false;
    }

    if (featureLevel != D3D_FEATURE_LEVEL_11_0)
    {
        OC_LOG_ERROR("Direct3D Feature Level 11 unsupported");
        return false;
    }

#if defined(OC_DEBUG)
    ComPtr<ID3D11InfoQueue> infoQueue;
    DXCall(m_dxDevice->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)infoQueue.GetAddressOf()));
    infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_WARNING, TRUE);
    infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, TRUE);
#endif 

    // Check 4X MSAA quality support for our back buffer format.
    // All Direct3D 11 capable devices support 4X MSAA for all render 
    // target formats, so we only need to check quality support.
    UINT MSAAQuality;
    DXCall(m_dxDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, m_config.m_MSAASample, &MSAAQuality));

    // Validate quality
    OC_ASSERT(MSAAQuality > 0);
    OC_ASSERT_MSG(m_config.m_selectBestMSAAQuality || m_config.m_MSAAQuality <= MSAAQuality -1, "Invalid MSAA quality");

    if (m_config.m_selectBestMSAAQuality)
    {
        m_config.m_MSAAQuality = MSAAQuality - 1;
    }

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // Describe the back buffer
    sd.BufferDesc.Width = m_backBufferWidth;
    sd.BufferDesc.Height = m_backBufferHeigth;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Texture format of the back buffer ( 8 bits rgb + alpha)
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    // Multisampling (anti-aliasing), all DX11 device support at least 4X multisampling for all render target format
    sd.SampleDesc.Count = m_config.m_MSAASample;
    sd.SampleDesc.Quality = m_config.m_MSAAQuality - 1;

     // Describes the surface usage and CPU access options for the back buffer. 
    // The back buffer can be used for shader input or render-target output.
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = m_hwnd;
    sd.Windowed = !m_config.m_fullScreen;
    // Options for handling pixels in a display surface after calling IDXGISwapChain1::Present1.
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    // Options for swap-chain behavior.
    sd.Flags = 0;
    // NOTE : This flag can change the resolution...
    //sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // To correctly create the swap chain, we must use the IDXGIFactory that was
    // used to create the device.  If we tried to use a different IDXGIFactory instance
    // (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
    // This function is being called with a device from a different IDXGIFactory."
    ComPtr<IDXGIDevice> dxgiDevice = nullptr;
    DXCall(m_dxDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)dxgiDevice.GetAddressOf()));

    ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
    DXCall(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)dxgiAdapter.GetAddressOf()));

    ComPtr<IDXGIFactory> dxgiFactory = nullptr;
    DXCall(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)dxgiFactory.GetAddressOf()));

    DXCall(dxgiFactory->CreateSwapChain(m_dxDevice.Get(), &sd, m_swapChain.GetAddressOf()));

    // The remaining steps that need to be carried out for d3d creation
    // also need to be executed every time the window is resized.
    BindDefaultBuffers();

    OC_LOG_INFO("GraphicSystem initialize completed");
    return true;
}

void Graphic::Shutdown()
{
    // Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
    if (m_swapChain.Get() != nullptr)
    {
        m_swapChain->SetFullscreenState(false, NULL);
    }

    if (m_dxImmediateContext.Get() != nullptr)
    {
        //This method resets any device context to the default settings. 
        //This sets all input/output resource slots, shaders, input layouts, predications, scissor rectangles, 
        //depth-stencil state, rasterizer state, blend state, sampler state, and viewports to NULL. 
        //The primitive topology is set to UNDEFINED.
        m_dxImmediateContext->ClearState();
    }
}


void Graphic::Resize(uint32 width, uint32 heigth)
{
    OC_ASSERT(m_dxImmediateContext.Get());
    OC_ASSERT(m_dxDevice.Get());
    OC_ASSERT(m_swapChain.Get());

    m_backBufferWidth = width;
    m_backBufferHeigth = heigth;

    // Release the old views, as they hold references to the buffers we
    // will be destroying.  Also release the old depth/stencil buffer.
    m_backBufferRTV.Reset();
    m_depthStencilView.Reset();
    m_depthStencilBuffer.Reset();

    // Resize the swap chain and recreate the render target view.
    // NOTE: If we do not resize the buffers the display will be stretched to the window size
    DXCall(m_swapChain->ResizeBuffers(1, m_backBufferWidth, m_backBufferHeigth, DXGI_FORMAT_R8G8B8A8_UNORM, 0));

    BindDefaultBuffers();
}

// This complete the back buffer init or resize by setting the default render target and viewport.
void Graphic::BindDefaultBuffers()
{
    ComPtr<ID3D11Texture2D> backBuffer;
    DXCall(m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
    DXCall(m_dxDevice->CreateRenderTargetView(backBuffer.Get(), NULL, m_backBufferRTV.GetAddressOf()));

    // Create the depth/stencil buffer and view.
    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width = m_backBufferWidth;
    depthStencilDesc.Height = m_backBufferHeigth;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    // Must match swap chain MSAA values.
    depthStencilDesc.SampleDesc.Count = m_config.m_MSAASample;
    depthStencilDesc.SampleDesc.Quality = m_config.m_MSAAQuality - 1;

    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    DXCall(m_dxDevice->CreateTexture2D(&depthStencilDesc, 0, m_depthStencilBuffer.GetAddressOf()));
    DXCall(m_dxDevice->CreateDepthStencilView(m_depthStencilBuffer.Get(), 0, m_depthStencilView.GetAddressOf()));

    // Set default render targets
    m_dxImmediateContext->OMSetRenderTargets(1, m_backBufferRTV.GetAddressOf(), m_depthStencilView.Get());

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = static_cast<float>(m_backBufferWidth);
    vp.Height = static_cast<float>(m_backBufferHeigth);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_dxImmediateContext->RSSetViewports(1, &vp);
}

void Graphic::Clear()
{
    m_dxImmediateContext->ClearRenderTargetView(m_backBufferRTV.Get(), reinterpret_cast<const float*>(&Colors::SteelBlue));
    m_dxImmediateContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void Graphic::Present()
{
    uint32 interval = m_config.m_enableVSync ? 1 : 0;
    DXCall(m_swapChain->Present(interval, 0));
}

OC_NS_END;