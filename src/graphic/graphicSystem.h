
#pragma once

#include "core\util\nonCopyable.h"
#include "core\util\pointer.h"
#include <d3d11.h>

OC_NS_BG;

struct GraphicSystemConfig
{
    bool m_fullScreen;
    bool m_selectBestQuality;
    uint32 m_MSAASample;
    uint32 m_MSAAQuality;
    D3D_DRIVER_TYPE m_dxDriverType;
};

class GraphicSystem : public NonCopyable
{
public:
    GraphicSystem(HWND hwnd, uint32 windowWidth = 1024, uint32 windowHeight = 768);
    ~GraphicSystem();

    bool initialize();
    bool initialize(const GraphicSystemConfig& config);
    void shutdown();

    uint32 getBackBufferWidth() const;
    uint32 getBackBufferHeigth() const;

    void resize(uint32 width, uint32 heigth);

    void present();
    // NOTE: Update might be needed later (with scene...)
    //void update(float elapsed);

private:

    void bindDefaultBuffers();

    GraphicSystemConfig m_config;

    ComPtr<ID3D11Device> m_dxDevice;
    ComPtr<ID3D11DeviceContext> m_dxImmediateContext;
    ComPtr<IDXGISwapChain> m_swapChain;
    ComPtr<ID3D11RenderTargetView> m_backBufferRTV;
    ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
    ComPtr<ID3D11DepthStencilView> m_depthStencilView;

    D3D11_VIEWPORT m_viewport;

    HWND m_hwnd;
    uint32 m_backBufferWidth;
    uint32 m_backBufferHeigth;
};

OC_NS_END;