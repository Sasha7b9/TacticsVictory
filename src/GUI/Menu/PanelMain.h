#pragma once


#include "GUI/Elements/Window.h"


class vPanelMain : public vWindow
{
    OBJECT(vPanelMain);

public:
    vPanelMain(Context *context = gContext);

    virtual void Update(float dT);

    static void RegisterObject(Context *context);

    void Toggle();

    void AddTab(SharedPtr<vTab> tab);

private:
    vPanelMain& operator=(const vPanelMain&)
    {};

    SharedPtr<vLineTranslator2D> translator;
    Vector<SharedPtr<vTab>> tabs;

    void HandleToggedTitle(StringHash eventType, VariantMap &eventData);
};