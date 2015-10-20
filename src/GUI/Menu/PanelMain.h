#pragma once


#include "GUI/Elements/Window.h"


class lPanelMain : public lWindow
{
    OBJECT(lPanelMain);

public:
    lPanelMain(Context *context = gContext);

    virtual void Update(float dT);

    static void RegisterObject(Context *context);

    void Toggle();

    void AddTab(SharedPtr<lTab> tab);

private:
    lPanelMain& operator=(const lPanelMain&)
    {};

    SharedPtr<lLineTranslator2D> translator;
    Vector<SharedPtr<lTab>> tabs;

    void HandleToggedTitle(StringHash eventType, VariantMap &eventData);
};