

#include "shader.h"
#include "graphic/dxUtil.h"
#include <d3dcompiler.h>
#include <windows.h>

OC_NS_BG;

namespace
{
    static const char* s_hlslFileDir = "../../src/graphic/shader/hlsl/";

    String findHlslFile(const char* path)
    {
        // Check current dir
        DWORD attribute = GetFileAttributes(path);
        if (attribute != INVALID_FILE_ATTRIBUTES)
            return path;

        // Check hlsl dir 
        String hlslDirPath(s_hlslFileDir);
        hlslDirPath += path;

        attribute = GetFileAttributes(hlslDirPath.c_str());
        if (attribute != INVALID_FILE_ATTRIBUTES)
            return hlslDirPath;

        // Not found
        return "";
    }

    bool compileShaderFromFile(const char* fileName, const char* entryPoint, const char* shaderModel, ID3DBlob** blobOut)
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
                OC_LOG_ERROR("Failed to compile shader " << fileName << ", error :" << (char*)pErrorBlob->GetBufferPointer());
        }

        if (pErrorBlob)
            pErrorBlob->Release();

        return retVal;
    }
}

Shader::Shader()
    : m_blob(nullptr)
{}

Shader::Shader(const String& filePath, const String& functionName)
    : m_blob(nullptr)
    , m_filePath(filePath)
    , m_functionName(functionName)
{}

bool Shader::isNull() const
{
    return m_blob.Get() == nullptr;
}

ID3DBlob* Shader::getBlob()
{
    return m_blob.Get();
}

// Vertex Shader 
// -------------------------
VertexShader::VertexShader()
{ }

VertexShader::VertexShader(const String& filePath, const String& functionName)
    : Shader(filePath, functionName)
    , m_vs(nullptr)
{ }

void VertexShader::bindVS(ID3D11DeviceContext* context)
{
    context->VSSetShader(m_vs.Get(), nullptr, 0);
}


// Pixel Shader 
// -------------------------
PixelShader::PixelShader()
{ }

PixelShader::PixelShader(const String& filePath, const String& functionName)
    : Shader(filePath, functionName)
    , m_ps(nullptr)
{ }

void PixelShader::bindPS(ID3D11DeviceContext* context)
{
    context->PSSetShader(m_ps.Get(), nullptr, 0);
}


// Shader compiler
// -------------------------
VertexShader ShaderCompiler::compileVS(ID3D11Device* device, const char* path, const char* functionName, const char* profile)
{
    String hlslFilePath = findHlslFile(path);
    OC_ASSERT_MSG(hlslFilePath.length() > 0, "Hlsl file not found!");

    VertexShader retVS(hlslFilePath, functionName);
    OC_LOG_INFO("Compiling vertex shader : file=" << hlslFilePath << ", func=" << functionName);

    // Compile the vertex shader
    ComPtr<ID3DBlob> vsBlob = nullptr;
    if (!compileShaderFromFile(hlslFilePath.c_str(), functionName, profile, vsBlob.GetAddressOf()))
    {
        return retVS;
    }

    // Save blob and create VS
    retVS.m_blob = vsBlob;
    DXCall(device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, retVS.m_vs.GetAddressOf()));

    return retVS;
}

PixelShader ShaderCompiler::compilePS(ID3D11Device* device, const char* path, const char* functionName, const char* profile)
{
    String hlslFilePath = findHlslFile(path);
    OC_ASSERT_MSG(hlslFilePath.length() > 0, "Hlsl file not found!");

    PixelShader retPS(hlslFilePath, functionName);
    OC_LOG_INFO("Compiling pixel shader : file=" << hlslFilePath << ", func=" << functionName);

    // Compile the pixel shader
    ComPtr<ID3DBlob> psBlob = nullptr;
    if (compileShaderFromFile(hlslFilePath.c_str(), functionName, profile, psBlob.GetAddressOf()))
    {
        retPS.m_blob = psBlob;
    }

    // Save blob and create PS
    retPS.m_blob = psBlob;
    DXCall(device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, retPS.m_ps.GetAddressOf()));

    return retPS;
}

OC_NS_END;