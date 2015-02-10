
#pragma once

#include "graphic/model/shape.h"

OC_NS_BG;

class GeometryBuilder
{
public:
    GeometryBuilder(const ComPtr<ID3D11Device>& dxDevice);

    Cube createCube(float width, float height, float depth);

private:

    ComPtr<ID3D11Device> m_dxDevice;
};

OC_NS_END;

// TODO : others stuff from geometry builder