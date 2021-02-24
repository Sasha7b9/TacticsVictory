// 2021/02/22 15:41:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#pragma once
#include "Scene/Objects/TStatusBar.h"
#include "Scene/Objects/Units/TTank_.h"


class StatusBar;


class CTank : public Tank
{
    URHO3D_OBJECT(CTank, Tank);

public:

    CTank(Context *context);

    static void RegisterObject();

private:

    virtual void OnNodeSet(Node *node) override;

    virtual void Start() override;

    virtual void FixedUpdate(float time) override;

    static Vector<CTank *> storage;
};
