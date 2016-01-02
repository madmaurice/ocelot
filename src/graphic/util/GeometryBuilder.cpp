
#include "geometryBuilder.h"

OC_NS_BG;


GeometryBuilder::GeometryBuilder(const ComPtr<ID3D11Device>& dxDevice)
    : m_dxDevice(dxDevice)
{
}

Cube GeometryBuilder::CreateCube(float width, float height, float depth)
{
    Cube cube(width, height, depth);
    cube.BuildMesh(m_dxDevice.Get());
    return cube;
}

OC_NS_END;