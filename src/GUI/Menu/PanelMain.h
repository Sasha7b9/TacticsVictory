#pragma once


class tvPanelMain : public tvWindow
{
    OBJECT(tvPanelMain);

public:
    tvPanelMain(Context *context = gContext);

    virtual void Update(float dT);

    static void RegisterObject(Context *context);

    void Toggle();

    void AddTab(SharedPtr<tvTab> tab);

private:
    tvPanelMain& operator=(const tvPanelMain&)
    {};

    SharedPtr<tvLineTranslator2D> translator;
    Vector<SharedPtr<tvTab>> tabs;

    void HandleToggedTitle(StringHash eventType, VariantMap &eventData);
};