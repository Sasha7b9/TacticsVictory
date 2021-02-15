/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


class DropDownListWithTextAndButton : public UIElement
{
    URHO3D_OBJECT(DropDownListWithTextAndButton, UIElement);

public:
    DropDownListWithTextAndButton(Context *context = TheContext);

    DropDownListWithTextAndButton(char *text, int widthText, int widthDDList);

    static void RegisterObject(Context* context = TheContext);

    void AddItem(char *text);
    void SetSelection(uint index);

    static SharedPtr<DropDownListWithTextAndButton> Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char * items[]);

private:
    SharedPtr<DropDownList> ddList;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;

    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
    void HandleButtonDown(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    DEFAULT_MEMBERS(DropDownListWithTextAndButton);
};
