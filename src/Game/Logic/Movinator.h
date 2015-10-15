#pragma once


class tvMovinator : public LogicComponent
{
    OBJECT(tvMovinator);
    
public:
    tvMovinator(Context *context);

    void SetMoveSpeed(float speed);
    void SetCenter(const Vector3 &vec);
    virtual void Update(float time);

private:
    tvMovinator& operator=(const tvMovinator&) {};
    float speed = 0.0f;
    float angle = 0.0f;
    Vector3 center;
};