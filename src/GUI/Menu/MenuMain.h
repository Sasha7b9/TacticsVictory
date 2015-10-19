#pragma once


class tvMenuMain : public tvWindow
{
    OBJECT(tvMenuMain);

public:
    tvMenuMain(Context *context);

    static void RegisterObject(Context *context);

    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

private:
    tvMenuMain& operator=(const tvMenuMain&)
    {};

    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    SharedPtr<tvButton> buttonNewGame;
    SharedPtr<tvButton> buttonEditor;
    SharedPtr<tvButton> buttonExit;
    SharedPtr<tvButton> buttonOptions;
};