// 2021/03/03 21:08:52 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Object_.h"


class GameObject;


class GameObjectSpecificS : public GameObjectSpecific
{
public:

    GameObjectSpecificS(GameObject *object);

    virtual void Update(float timeStep) override;

    float timeNextTimeSend = 0.0f;        // Время следующей засылки состояния объекта
};
