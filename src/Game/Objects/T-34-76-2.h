#pragma once


#include "MovingObject.h"


class lT34_76_2 : public lMovingObject
{
public:
    lT34_76_2();

    void Load();
    void Normalize();

private:
    lT34_76_2& operator=(const lT34_76_2&) {};
};
