
#pragma once

#include "core/util/nonCopyable.h"
#include "core/util/ComPtr.h"
#include <d3d11.h>

OC_NS_BG;

class GeometryBuilder;

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

    bool Initialize();
    bool Initialize(const GraphicSystemConfig& config);
    void Shutdown();

    uint32 GetBackBufferWidth() const;
    uint32 GetBackBufferHeigth() const;

    void Resize(uint32 width, uint32 heigth);

    void Clear();
    void Present();

    ComPtr<ID3D11Device> GetDevice() { return m_dxDevice; }
    ComPtr<ID3D11DeviceContext> GetDeviceContext() { return m_dxImmediateContext; }

    std::shared_ptr<GeometryBuilder> GetGeometryBuilder() { return m_geoBuilder; }

private:

    void BindDefaultBuffers();

    GraphicSystemConfig m_config;

    ComPtr<ID3D11Device> m_dxDevice;
    ComPtr<ID3D11DeviceContext> m_dxImmediateContext;
    ComPtr<IDXGISwapChain> m_swapChain;
    ComPtr<ID3D11RenderTargetView> m_backBufferRTV;
    ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
    ComPtr<ID3D11DepthStencilView> m_depthStencilView;

    // Utils
    std::shared_ptr<GeometryBuilder> m_geoBuilder;

    D3D11_VIEWPORT m_viewport;

    HWND m_hwnd;
    uint32 m_backBufferWidth;
    uint32 m_backBufferHeigth;
};

OC_NS_END;