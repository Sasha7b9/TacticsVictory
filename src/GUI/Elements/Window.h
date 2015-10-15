#pragma once


class tvWindow : public Window
{
    OBJECT(tvWindow)

public:
    tvWindow(Context *context);

    static void RegisterObject(Context *context);

    void SetInCenterRect(const IntRect& rect);
    bool IsChildOfParent();
    void Toggle();

    SharedPtr<tvButton> AddButton(char *text, int x, int y, int width = -1, int height = -1);
    SharedPtr<tvButtonToggled> AddButtonToggled(char *text, int x, int y, int width, int height);

protected:
    tvWindow& operator=(const tvWindow&)
    {};

    HashMap<Button*, uint> mapButtonsActions;
};