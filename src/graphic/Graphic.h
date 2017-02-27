
#pragma once

#include "core/util/NonCopyable.h"
#include "core/util/ComPtr.h"
#include <d3d11.h>

OC_NS_BG;

struct GraphicConfig
{
    uint32 m_windowWitdh;
    uint32 m_windowHeight;
    uint32 m_MSAASample;
    uint32 m_MSAAQuality;

    bool m_fullScreen;
    bool m_enableVSync;
    bool m_selectBestMSAAQuality;
};

typedef ComPtr<ID3D11Device> GraphicDevice;
typedef ComPtr<ID3D11DeviceContext> GraphicDeviceContext;

class Graphic
{
public:

    static bool Initialize(HWND hwnd, uint32 windowWidth = 1024, uint32 windowHeight = 768);
    static bool Initialize(HWND hwnd, const GraphicConfig& config);
    static void Shutdown();

    static const GraphicConfig& GetConfig() { return m_config; }

    static GraphicDevice GetDevice() { return m_dxDevice; }
    static GraphicDeviceContext GetDeviceContext() { return m_dxImmediateContext; }

    static void Resize(uint32 width, uint32 heigth);

    static void Clear();
    static void Present();

private:

    static void BindDefaultBuffers();

    static GraphicConfig m_config;

    static GraphicDevice m_dxDevice;
    static GraphicDeviceContext m_dxImmediateContext;
    static ComPtr<IDXGISwapChain> m_swapChain;
    static ComPtr<ID3D11RenderTargetView> m_backBufferRTV;
    static ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
    static ComPtr<ID3D11DepthStencilView> m_depthStencilView;

    static D3D11_VIEWPORT m_viewport;

    static HWND m_hwnd;
    static uint32 m_backBufferWidth;
    static uint32 m_backBufferHeigth;
};

OC_NS_END;