#pragma once


class vDropDownListWithTextAndButton : public UIElement
{
    OBJECT(vDropDownListWithTextAndButton);

public:
    vDropDownListWithTextAndButton(char *text, int widthText, int widthDDList);
    void AddItem(char *text);
    void SetSelection(uint index);

    static SharedPtr<vDropDownListWithTextAndButton> Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char * items[]);

private:
    vDropDownListWithTextAndButton& operator=(const vDropDownListWithTextAndButton&)
    {};

    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
    void HandleButtonDown(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    SharedPtr<DropDownList> ddList;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;
};