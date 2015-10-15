#pragma once


class tvConsole : public tvWindow
{
    OBJECT(tvConsole);

public:
    tvConsole(Context *context);

    void Toggle();
    void HandleFinishedText(StringHash eventType, VariantMap& eventData);

private:
    SharedPtr<LineEdit> lineEdit;
    SharedPtr<Text> text;
    SharedPtr<ScrollBar> scrollBar;


};