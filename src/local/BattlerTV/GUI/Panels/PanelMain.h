// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


class Tab;


/*
    Основная игровая панель с вкладками
*/
class PanelMain : public WindowT
{
    URHO3D_OBJECT(PanelMain, WindowT);

public:
    PanelMain(Context *context);
    static void RegisterObject();

    virtual void Update(float dT);
    void AddTab(SharedPtr<Tab> tab);

private:
    Vector<SharedPtr<Tab>> tabs;
    SharedPtr<Tab> currentTab;

    void HandleToggedTitle(StringHash eventType, VariantMap &eventData);
};
