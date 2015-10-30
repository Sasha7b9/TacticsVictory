#pragma once


class lDropDownListWithTextAndButton : public UIElement
{
    OBJECT(lDropDownListWithTextAndButton);

public:
    lDropDownListWithTextAndButton(Context *context = gContext);

    lDropDownListWithTextAndButton(char *text, int widthText, int widthDDList);

    static void RegisterObject(Context* context = gContext);

    void AddItem(char *text);
    void SetSelection(uint index);

    static SharedPtr<lDropDownListWithTextAndButton> Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char * items[]);

private:
    lDropDownListWithTextAndButton& operator=(const lDropDownListWithTextAndButton&)
    {};

    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
    void HandleButtonDown(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    SharedPtr<DropDownList> ddList;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;
};