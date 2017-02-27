

#include "Shader.h"
#include "graphic/Graphic.h"

#include <d3dcompiler.h>

OC_NS_BG;

namespace
{
    // TODO read config?
    static const char* s_hlslFileDir = "../../src/graphic/shader/hlsl/";

    String FindHlslFile(const char* path)
    {
        // Check current dir
        DWORD attribute = GetFileAttributes(path);
        if (attribute != INVALID_FILE_ATTRIBUTES)
        {
            return path;
        }

        // Check hlsl dir 
        String hlslDirPath(s_hlslFileDir);
        hlslDirPath += path;

        attribute = GetFileAttributes(hlslDirPath.c_str());
        if (attribute != INVALID_FILE_ATTRIBUTES)
        {
            return hlslDirPath;
        }

        // Not found
        return "";
    }

    bool CompileShaderFromFile(const char* fileName, const char* entryPoint, const char* shaderModel, ID3DBlob** blobOut)
    {
        HRESULT hr = S_OK;
        bool retVal = true;

        DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_WARNINGS_ARE_ERRORS;
#if defined( DEBUG ) || defined( _DEBUG )
        // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
        // Setting this flag improves the shader debugging experience
        flags |= D3DCOMPILE_DEBUG;
#endif

        ID3DBlob* pErrorBlob;
        hr = D3DX11CompileFromFile(fileName, NULL, NULL, entryPoint, shaderModel,
            flags, 0, NULL, blobOut, &pErrorBlob, NULL);

        if (FAILED(hr))
        {
            retVal = false;
            if (pErrorBlob != NULL)
            {
                OC_LOG_ERROR("Failed to compile shader " << fileName << ", error :" << (char*)pErrorBlob->GetBufferPointer());
            }
        }

        if (pErrorBlob)
        {
            pErrorBlob->Release();
        }

        return retVal;
    }
}


// Shader compiler
// -------------------------
VertexShader ShaderCompiler::CompileVS(const char* path, const char* functionName, const char* profile)
{
    // Find and compile the vertex shader
    String hlslFilePath = FindHlslFile(path);
    OC_ASSERT_MSG(hlslFilePath.length() > 0, "Hlsl file not found!");

    VertexShader retVS(hlslFilePath, functionName);
    OC_LOG_INFO("Compiling vertex shader : file=" << hlslFilePath << ", func=" << functionName);

    ComPtr<ID3DBlob> vsBlob = nullptr;
    if (!CompileShaderFromFile(hlslFilePath.c_str(), functionName, profile, vsBlob.GetAddressOf()))
    {
        return retVS;
    }

    // Save blob and create VS
    retVS.m_blob = vsBlob;
    DXCall(Graphic::GetDevice()->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, retVS.m_vs.GetAddressOf()));

    return retVS;
}

PixelShader ShaderCompiler::CompilePS(const char* path, const char* functionName, const char* profile)
{
    // Find and compile the pixel shader
    String hlslFilePath = FindHlslFile(path);
    OC_ASSERT_MSG(hlslFilePath.length() > 0, "Hlsl file not found!");

    PixelShader retPS(hlslFilePath, functionName);
    OC_LOG_INFO("Compiling pixel shader : file=" << hlslFilePath << ", func=" << functionName);

    ComPtr<ID3DBlob> psBlob = nullptr;
    if (!CompileShaderFromFile(hlslFilePath.c_str(), functionName, profile, psBlob.GetAddressOf()))
    {
        return retPS;
    }

    // Save blob and create PS
    retPS.m_blob = psBlob;
    DXCall(Graphic::GetDevice()->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, retPS.m_ps.GetAddressOf()));

    return retPS;
}

Shader::Shader()
    : m_blob(nullptr)
{}

Shader::Shader(const String& filePath, const String& functionName)
    : m_blob(nullptr)
    , m_filePath(filePath)
    , m_functionName(functionName)
{}

// Vertex Shader 
// -------------------------
VertexShader::VertexShader()
{ }

VertexShader::VertexShader(const String& filePath, const String& functionName)
    : Shader(filePath, functionName)
    , m_vs(nullptr)
{ }

void VertexShader::BindVS()
{
    Graphic::GetDeviceContext()->VSSetShader(m_vs.Get(), nullptr, 0);
}


// Pixel Shader 
// -------------------------
PixelShader::PixelShader()
{ }

PixelShader::PixelShader(const String& filePath, const String& functionName)
    : Shader(filePath, functionName)
    , m_ps(nullptr)
{ }

void PixelShader::BindPS()
{
    Graphic::GetDeviceContext()->PSSetShader(m_ps.Get(), nullptr, 0);
}


OC_NS_END;