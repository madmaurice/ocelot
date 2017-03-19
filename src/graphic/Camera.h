
#pragma once

#include "math/Math.h"

OC_NS_BG;

class BaseCamera
{
public:

    BaseCamera(float nearZ, float farZ);
    virtual ~BaseCamera() = default;

    const Matrix4& GetView() const { return m_view; };
    const Matrix4& GetProjection() const { return m_projection; };
    const Matrix4& GetViewProjection() const { return m_viewProjection; };
    const Matrix4& GetWorld() const { return m_world; };
    const Vector3& GetPosition() const { return m_position; };
    const Quaternion& GetOrientation() const { return m_orientation; };
    float GetNearClip() const { return m_nearZ; };
    float GetFarClip() const { return m_farZ; };

    Vector3 Forward() const;
    Vector3 Back() const;
    Vector3 Up() const;
    Vector3 Down() const;
    Vector3 Right() const;
    Vector3 Left() const;

    void SetLookAt(const Vector3& eye, const Vector3& lookAt, const Vector3& up);
    void SetWorld(const Matrix4& world);
    void SetPosition(const Vector3& pos);
    void SetOrientation(const Quaternion& orientation);
    void SetNearClip(float nearClip);
    void SetFarClip(float farClip);
    void SetProjection(const Matrix4& projection);

protected:

    Matrix4 m_view;
    Matrix4 m_projection;
    Matrix4 m_viewProjection;

    Matrix4 m_world;
    Vector3 m_position;
    Quaternion m_orientation;

    float m_nearZ;
    float m_farZ;

    virtual void CreateProjection() = 0;
    void UpdateView();
};


class FirstPersonCamera : public BaseCamera
{
public:

    FirstPersonCamera(float aspectRatio, float fieldOfView, float nearClip, float farClip);
    virtual ~FirstPersonCamera() = default;

    float GetXRotation() const { return m_xRot; };
    float GetYRotation() const { return m_yRot; };

    void SetXRotation(float xRotation);
    void SetYRotation(float yRotation);

private:
    virtual void CreateProjection() override;

    float m_aspectRatio = 0;
    float m_fov = 0;
    float m_xRot = 0;
    float m_yRot = 0;
};

OC_NS_END;