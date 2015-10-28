#pragma once


#include "Object.h"


class lMovingObject : public lObject
{
public:
    lMovingObject();
private:
    lMovingObject& operator=(const lMovingObject&) {};
};