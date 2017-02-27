
#pragma once

#include "core/util/ComPtr.h"
#include "graphic/util/DxUtil.h"

OC_NS_BG;

struct ShaderCompiler;

class Shader
{
public:

    bool IsNull() const { return m_blob.Get() == nullptr; }
    ID3DBlob* GetBlob() { return m_blob.Get();  }

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

    void BindVS();

private:
    ComPtr<ID3D11VertexShader> m_vs;

    friend ShaderCompiler;
};


struct PixelShader : public Shader
{
public:
    PixelShader();
    PixelShader(const String& filePath, const String& functionName);

    void BindPS();

private:
    ComPtr<ID3D11PixelShader> m_ps;

    friend ShaderCompiler;
};

struct ShaderCompiler
{
    static VertexShader CompileVS(const char* path, const char* functionName = "VS", const char* profile = "vs_5_0");
    static PixelShader CompilePS(const char* path, const char* functionName = "PS", const char* profile = "ps_5_0");
};

OC_NS_END;