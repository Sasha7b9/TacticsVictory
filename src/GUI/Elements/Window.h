#pragma once


class vWindow : public Window
{
    OBJECT(vWindow)

public:
    vWindow(Context *context);

    static void RegisterObject(Context *context);

    void SetInCenterRect(const IntRect& rect);
    bool IsChildOfParent();
    void Toggle();

    SharedPtr<vButton> AddButton(char *text, int x, int y, int width = -1, int height = -1);
    SharedPtr<vButtonToggled> AddButtonToggled(char *text, int x, int y, int width, int height);

protected:
    vWindow& operator=(const vWindow&)
    {};

    HashMap<Button*, uint> mapButtonsActions;
};