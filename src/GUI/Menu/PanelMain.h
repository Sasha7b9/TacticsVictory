#pragma once


#include "GUI/Elements/Window.h"


class lPanelMain : public lWindow
{
    OBJECT(lPanelMain);

public:
    lPanelMain(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    virtual void Update(float dT);
    void AddTab(SharedPtr<lTab> tab);

private:
    lPanelMain& operator=(const lPanelMain&)
    {};

    Vector<SharedPtr<lTab>> tabs;

    SharedPtr<lTab> currentTab;

    void HandleToggedTitle(StringHash eventType, VariantMap &eventData);
};