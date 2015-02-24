
#include "shape.h"
#include "math/math.h"

OC_NS_BG;

Cube::Cube()
    : m_width(0)
    , m_height(0)
    , m_depth(0)
{}

Cube::Cube(float width, float height, float depth)
    : m_width(width)
    , m_height(height)
    , m_depth(depth)
{
}

void Cube::buildMesh(ID3D11Device* device)
{
    // Create the vertices.
    MeshVertex v[24];

    float w2 = 0.5f*m_width;
    float h2 = 0.5f*m_height;
    float d2 = 0.5f*m_depth;

    // Fill in the front face vertex data.
    v[0] = MeshVertex(-w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
    v[1] = MeshVertex(-w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
    v[2] = MeshVertex(+w2, +h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
    v[3] = MeshVertex(+w2, -h2, -d2, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

    // Fill in the back face vertex data.
    v[4] = MeshVertex(-w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    v[5] = MeshVertex(+w2, -h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    v[6] = MeshVertex(+w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    v[7] = MeshVertex(-w2, +h2, +d2, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    // Fill in the top face vertex data.
    v[8] = MeshVertex(-w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    v[9] = MeshVertex(-w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    v[10] = MeshVertex(+w2, +h2, +d2, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    v[11] = MeshVertex(+w2, +h2, -d2, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

    // Fill in the bottom face vertex data.
    v[12] = MeshVertex(-w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
    v[13] = MeshVertex(+w2, -h2, -d2, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
    v[14] = MeshVertex(+w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
    v[15] = MeshVertex(-w2, -h2, +d2, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

    // Fill in the left face vertex data.
    v[16] = MeshVertex(-w2, -h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    v[17] = MeshVertex(-w2, +h2, +d2, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    v[18] = MeshVertex(-w2, +h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    v[19] = MeshVertex(-w2, -h2, -d2, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    // Fill in the right face vertex data.
    v[20] = MeshVertex(+w2, -h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    v[21] = MeshVertex(+w2, +h2, -d2, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    v[22] = MeshVertex(+w2, +h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    v[23] = MeshVertex(+w2, -h2, +d2, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    m_vertices.assign(&v[0], &v[24]);

    // Create the indices.
    uint32 i[36];

    // Fill in the front face index data
    i[0] = 0; i[1] = 1; i[2] = 2;
    i[3] = 0; i[4] = 2; i[5] = 3;

    // Fill in the back face index data
    i[6] = 4; i[7] = 5; i[8] = 6;
    i[9] = 4; i[10] = 6; i[11] = 7;

    // Fill in the top face index data
    i[12] = 8; i[13] = 9; i[14] = 10;
    i[15] = 8; i[16] = 10; i[17] = 11;

    // Fill in the bottom face index data
    i[18] = 12; i[19] = 13; i[20] = 14;
    i[21] = 12; i[22] = 14; i[23] = 15;

    // Fill in the left face index data
    i[24] = 16; i[25] = 17; i[26] = 18;
    i[27] = 16; i[28] = 18; i[29] = 19;

    // Fill in the right face index data
    i[30] = 20; i[31] = 21; i[32] = 22;
    i[33] = 20; i[34] = 22; i[35] = 23;

    m_indices.assign(&i[0], &i[36]);

    buildBuffers(device);
}


Sphere::Sphere()
    : m_radius(0)
    , m_sliceCount(0)
    , m_stackCount(0)
{
}

Sphere::Sphere(float radius, uint32 sliceCount, uint32 stackCount)
    : m_radius(radius)
    , m_sliceCount(sliceCount)
    , m_stackCount(stackCount)
{
}

void Sphere::buildMesh(ID3D11Device* device)
{
    m_vertices.clear();
    m_indices.clear();

    // Compute the vertices stating at the top pole and moving down the stacks.

    // Poles: note that there will be texture coordinate distortion as there is
    // not a unique point on the texture map to assign to the pole when mapping
    // a rectangular texture onto a sphere.
    MeshVertex topVertex(0.0f, +m_radius, 0.0f, 0.0f, +1.0f, 0.0f, 0.0f, 0.0f);
    MeshVertex bottomVertex(0.0f, -m_radius, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);

    m_vertices.push_back(topVertex);

    float phiStep = OC_PI / m_stackCount;
    float thetaStep = 2.0f*OC_PI / m_sliceCount;

    // Compute vertices for each stack ring (do not count the poles as rings).
    for (uint32 i = 1; i <= m_stackCount - 1; ++i)
    {
        float phi = i*phiStep;

        // Vertices of ring.
        for (uint32 j = 0; j <= m_sliceCount; ++j)
        {
            float theta = j*thetaStep;

            MeshVertex v;

            // spherical to cartesian
            v.m_position.x = m_radius*sinf(phi)*cosf(theta);
            v.m_position.y = m_radius*cosf(phi);
            v.m_position.z = m_radius*sinf(phi)*sinf(theta);

            v.m_normal = Vector3::normalize(v.m_position);

            v.m_texCoord.x = theta / OC_2PI;
            v.m_texCoord.y = phi / OC_PI;

            m_vertices.push_back(v);
        }
    }

    m_vertices.push_back(bottomVertex);

    // Compute indices for top stack.  The top stack was written first to the vertex buffer
    // and connects the top pole to the first ring.
    for (uint32 i = 1; i <= m_sliceCount; ++i)
    {
        m_indices.push_back(0);
        m_indices.push_back(i + 1);
        m_indices.push_back(i);
    }

    // Compute indices for inner stacks (not connected to poles).

    // Offset the indices to the index of the first vertex in the first ring.
    // This is just skipping the top pole vertex.
    uint32 baseIndex = 1;
    uint32 ringVertexCount = m_sliceCount + 1;
    for (uint32 i = 0; i < m_stackCount - 2; ++i)
    {
        for (uint32 j = 0; j < m_sliceCount; ++j)
        {
            m_indices.push_back(baseIndex + i*ringVertexCount + j);
            m_indices.push_back(baseIndex + i*ringVertexCount + j + 1);
            m_indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);

            m_indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
            m_indices.push_back(baseIndex + i*ringVertexCount + j + 1);
            m_indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
        }
    }

    // Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
    // and connects the bottom pole to the bottom ring.

    // South pole vertex was added last.
    uint32 southPoleIndex = (uint32)m_vertices.size() - 1;

    // Offset the indices to the index of the first vertex in the last ring.
    baseIndex = southPoleIndex - ringVertexCount;

    for (uint32 i = 0; i < m_sliceCount; ++i)
    {
        m_indices.push_back(southPoleIndex);
        m_indices.push_back(baseIndex + i);
        m_indices.push_back(baseIndex + i + 1);
    }

    buildBuffers(device);
}


Cylinder::Cylinder()
    : m_bottomRadius(0)
    , m_topRadius(0)
    , m_sliceCount(0)
    , m_stackCount(0)
{
}

Cylinder::Cylinder(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount)
    : m_bottomRadius(bottomRadius)
    , m_topRadius(topRadius)
    , m_height(height)
    , m_sliceCount(sliceCount)
    , m_stackCount(stackCount)
{
}

void Cylinder::buildMesh(ID3D11Device* device)
{
    // TODO
    OC_UNUSED(device);
}

Grid::Grid()
    : m_width(0)
    , m_depth(0)
    , m_rows(0)
    , m_columns(0)
{
}

Grid::Grid(float width, float depth, uint32 rows, uint32 columns)
    : m_width(width)
    , m_depth(depth)
    , m_rows(rows)
    , m_columns(columns)
{
}

void Grid::buildMesh(ID3D11Device* device)
{
    uint32 m = m_rows;
    uint32 n = m_columns;

    uint32 vertexCount = m*n;
    uint32 faceCount = (m - 1)*(n - 1) * 2;

    // Create the vertices.
    float halfWidth = 0.5f*m_width;
    float halfDepth = 0.5f*m_depth;

    float dx = m_width / (n - 1);
    float dz = m_depth / (m - 1);

    float du = 1.0f / (n - 1);
    float dv = 1.0f / (m - 1);

    m_vertices.resize(vertexCount);
    for (uint32 i = 0; i < m; ++i)
    {
        float z = halfDepth - i*dz;
        for (uint32 j = 0; j < n; ++j)
        {
            float x = -halfWidth + j*dx;

            m_vertices[i*n + j].m_position = Vector3(x, 0.0f, z);
            m_vertices[i*n + j].m_normal = Vector3(0.0f, 1.0f, 0.0f);

            // Stretch texture over grid.
            m_vertices[i*n + j].m_texCoord.x = j*du;
            m_vertices[i*n + j].m_texCoord.y = i*dv;
        }
    }

    // Create the indices.
    m_indices.resize(faceCount * 3); // 3 indices per face

    // Iterate over each quad and compute indices.
    uint32 k = 0;
    for (uint32 i = 0; i < m - 1; ++i)
    {
        for (uint32 j = 0; j < n - 1; ++j)
        {
            m_indices[k] = i*n + j;
            m_indices[k + 1] = i*n + j + 1;
            m_indices[k + 2] = (i + 1)*n + j;

            m_indices[k + 3] = (i + 1)*n + j;
            m_indices[k + 4] = i*n + j + 1;
            m_indices[k + 5] = (i + 1)*n + j + 1;

            k += 6; // next quad
        }
    }

    buildBuffers(device);
}

OC_NS_END;