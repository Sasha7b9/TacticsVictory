#pragma once


class lWindow : public Window
{
    OBJECT(lWindow)

public:
    lWindow(Context *context);

    static void RegisterObject(Context *context);

    void SetInCenterRect(const IntRect& rect);
    bool IsChildOfParent();
    void Toggle();

    SharedPtr<lButton> AddButton(char *text, int x, int y, int width = -1, int height = -1);
    SharedPtr<lButtonToggled> AddButtonToggled(char *text, int x, int y, int width, int height);

protected:
    lWindow& operator=(const lWindow&)
    {};

    HashMap<Button*, uint> mapButtonsActions;
};