#pragma once


#include "GUI/Elements/Window.h"


class PanelMain : public lWindow
{
    OBJECT(PanelMain);

public:
    PanelMain(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    virtual void Update(float dT);
    void AddTab(SharedPtr<Tab> tab);

private:
    PanelMain& operator=(const PanelMain&)
    {};

    Vector<SharedPtr<Tab>> tabs;

    SharedPtr<Tab> currentTab;

    void HandleToggedTitle(StringHash eventType, VariantMap &eventData);
};