
#pragma once

#include "graphic/buffer/constantBuffer.h"
#include "graphic/shader/effect.h"

struct ID3D11DeviceContext;

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

class BasicEffect : public Effect
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

    bool initialize(ID3D11Device* device);

    void applyChanges(ID3D11DeviceContext* deviceContext);

    FrameParam& getFrameParam();
    ObjParam& getObjParam();

private:
    virtual void bindResources(ID3D11DeviceContext* context);

    ConstantBuffer<FrameParam> m_cbFrame;
    ConstantBuffer<ObjParam> m_cbObj;
};

OC_NS_END;