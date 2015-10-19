#pragma once





class tvMenu : public UIElement
{
    OBJECT(tvMenu);

public:
    tvMenu(Context *context);

    static void RegisterObject(Context* context);

    void Log();

private:
    tvMenu& operator=(const tvMenu&) {};

    void HandleMenuEvent(StringHash eventType, VariantMap& eventData);

    Text *text = nullptr;
};