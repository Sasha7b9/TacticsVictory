// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/_WindowRTS.h"


class Tab;


/*
    Основная игровая панель с вкладками
*/
class PanelMain : public WindowTV
{
    URHO3D_OBJECT(PanelMain, WindowTV);

public:
    PanelMain(Context *context = TheContext);

    static void RegisterObject(Context *context = TheContext);

    virtual void Update(float dT);
    void AddTab(SharedPtr<Tab> tab);

private:
    Vector<SharedPtr<Tab>> tabs;
    SharedPtr<Tab> currentTab;

    void HandleToggedTitle(StringHash eventType, VariantMap &eventData);
};
