#pragma once


class tvDropDownListWithTextAndButton : public UIElement
{
    OBJECT(tvDropDownListWithTextAndButton);

public:
    tvDropDownListWithTextAndButton(char *text, int widthText, int widthDDList);
    void AddItem(char *text);
    void SetSelection(uint index);

    static SharedPtr<tvDropDownListWithTextAndButton> Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char * items[]);

private:
    tvDropDownListWithTextAndButton& operator=(const tvDropDownListWithTextAndButton&)
    {};

    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
    void HandleButtonDown(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    SharedPtr<DropDownList> ddList;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;
};