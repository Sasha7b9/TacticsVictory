#pragma once


class tvPlane : public Object
{
    OBJECT(tvPlane)
public:
    tvPlane(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3 &p3);

private:
    tvPlane& operator=(const tvPlane&) {};
    void Create(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3 &p3);
};