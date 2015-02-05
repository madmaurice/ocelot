
#pragma once

#include "core/util/pointer.h"
#include "graphic/dxUtil.h"


OC_NS_BG;

struct ShaderCompiler;

class Shader
{
public:

    bool isNull() const;
    ID3DBlob* getBlob();

    String m_filePath;
    String m_functionName;

protected:
    Shader();
    Shader(const String& filePath, const String& functionName);
    ComPtr<ID3DBlob> m_blob;
};


class VertexShader : public Shader
{
public:

    VertexShader();
    VertexShader(const String& filePath, const String& functionName);

    void bindVS(ID3D11DeviceContext* context);

private:
    ComPtr<ID3D11VertexShader> m_vs;

    friend ShaderCompiler;
};


struct PixelShader : public Shader
{
public:
    PixelShader();
    PixelShader(const String& filePath, const String& functionName);

    void bindPS(ID3D11DeviceContext* context);

private:
    ComPtr<ID3D11PixelShader> m_ps;

    friend ShaderCompiler;
};


struct ShaderCompiler
{
    static VertexShader compileVS(ID3D11Device* device, const char* path, 
        const char* functionName = "VS", const char* profile = "vs_5_0");

    static PixelShader compilePS(ID3D11Device* device, const char* path, 
        const char* functionName = "PS", const char* profile = "ps_5_0");
};

OC_NS_END;