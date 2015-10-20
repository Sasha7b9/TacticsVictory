#pragma once


class vMovinator : public LogicComponent
{
    OBJECT(vMovinator);
    
public:
    vMovinator(Context *context);

    void SetMoveSpeed(float speed);
    void SetCenter(const Vector3 &vec);
    virtual void Update(float time);

private:
    vMovinator& operator=(const vMovinator&) {};
    float speed = 0.0f;
    float angle = 0.0f;
    Vector3 center;
};