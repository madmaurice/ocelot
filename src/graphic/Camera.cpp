
#include "Camera.h"

OC_NS_BG;

// Rotation reference : https://goocreate.com/learn/everything-you-always-wanted-to-know-about-rotation/
// View matrix reference : https://www.3dgep.com/understanding-the-view-matrix/
// and http://www.codinglabs.net/article_world_view_projection_matrix.aspx

BaseCamera::BaseCamera(float nearZ, float farZ)
    : m_nearZ(nearZ)
    , m_farZ(farZ)
{
    OC_ASSERT(m_nearZ >= 0.0f);
    OC_ASSERT(m_farZ >= 0.0f);
    OC_ASSERT(m_nearZ < m_farZ);
}

Vector3 BaseCamera::Left() const
{
    return m_world.Left();
}

Vector3 BaseCamera::Right() const
{
    return m_world.Right();
}

Vector3 BaseCamera::Down() const
{
    return m_world.Down();
}

Vector3 BaseCamera::Up() const
{
    return m_world.Up();
}

Vector3 BaseCamera::Back() const
{
    return m_world.Back();
}

Vector3 BaseCamera::Forward() const
{
    return m_world.Forward();
}

void BaseCamera::SetProjection(const Matrix4& projection)
{
    m_projection = projection;
    m_viewProjection = m_view * m_projection;
}

void BaseCamera::SetFarClip(float farClip)
{
    m_farZ = farClip;
    CreateProjection();
}

void BaseCamera::SetNearClip(float nearClip)
{
    m_nearZ = nearClip;
    CreateProjection();
}

void BaseCamera::SetOrientation(const Quaternion& orientation)
{
    m_orientation = orientation;
    m_world = m_orientation.ToMatrix4();
    m_world.SetTranslation(m_position);
    UpdateView();
}

void BaseCamera::SetPosition(const Vector3& pos)
{
    m_position = pos;
    m_world.SetTranslation(m_position);
    UpdateView();
}

void BaseCamera::SetWorld(const Matrix4& world)
{
    m_world = world;
    m_position = m_world.GetTranslation();
    UpdateView();
}

void BaseCamera::SetLookAt(const Vector3& eye, const Vector3& lookAt, const Vector3& up)
{
    m_view = Matrix4::LookAtMatrixLH(eye, lookAt, up);
    m_world = Matrix4::Inverse(m_view);
    m_position = eye;

    m_viewProjection = m_view * m_projection;
}

void BaseCamera::UpdateView()
{
    m_view = Matrix4::Inverse(m_world);
    m_viewProjection = m_view * m_projection;
}

FirstPersonCamera::FirstPersonCamera(float aspectRatio, float fieldOfView, float nearClip, float farClip)
    : BaseCamera(nearClip, farClip)
    , m_aspectRatio(aspectRatio)
    , m_fov(fieldOfView)
{
    OC_ASSERT(m_aspectRatio > 0);
    OC_ASSERT(m_fov > 0 && m_fov < OC_PI);
    CreateProjection();
}

void FirstPersonCamera::CreateProjection()
{
    m_projection = Matrix4::PerspectiveFovMatrixLH(m_aspectRatio, m_fov, m_nearZ, m_farZ);
    m_viewProjection = m_view * m_projection;
}

void FirstPersonCamera::SetXRotation(float xRotation)
{
    m_xRot = Clamp(xRotation, -OC_PIDIV2, OC_PIDIV2);
    SetOrientation(Quaternion(m_xRot, m_yRot, 0));
}

void FirstPersonCamera::SetYRotation(float yRotation)
{
    m_yRot = DirectX::XMScalarModAngle(yRotation);
    SetOrientation(Quaternion(m_xRot, m_yRot, 0));
}

void FirstPersonCamera::SetAspectRatio(float aspect)
{
    m_aspectRatio = aspect;
    CreateProjection();
}

void FirstPersonCamera::SetFov(float fov)
{
    m_fov = fov;
    CreateProjection();
}

OC_NS_END;