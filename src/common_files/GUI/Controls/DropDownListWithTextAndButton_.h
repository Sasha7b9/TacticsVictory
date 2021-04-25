// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class DropDownListWithTextAndButton : public UIElement
{
    URHO3D_OBJECT(DropDownListWithTextAndButton, UIElement);

public:
    DropDownListWithTextAndButton(Context *);
    DropDownListWithTextAndButton(pchar text, int widthText, int widthDDList);
    static void RegisterObject();

    void AddItem(char *text);
    void SetSelection(uint index);

    static SharedPtr<DropDownListWithTextAndButton> Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char * items[]);

private:
    SharedPtr<DropDownList> ddList;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;

    void HandlerItemSelected(StringHash eventType, VariantMap& eventData);
    void HandlerButtonDown(StringHash eventType, VariantMap& eventData);
    void HandlerHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandlerHoverEnd(StringHash eventType, VariantMap& eventData);
};
