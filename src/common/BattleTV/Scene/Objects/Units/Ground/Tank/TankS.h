// 2021/02/26 16:38:06 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class TankSpecificS : public TankSpecific
{
    URHO3D_OBJECT(TankSpecificS, TankSpecific);

public:

    TankSpecificS(Context *context) : TankSpecific(context) {}

    float timeNextTimeSend = 0.0f;        // Время следующей засылки состояния объекта

    virtual void Update(float timeStep) override;
};
