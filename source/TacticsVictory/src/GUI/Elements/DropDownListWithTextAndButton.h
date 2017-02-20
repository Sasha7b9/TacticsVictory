#pragma once


class DropDownListWithTextAndButton : public UIElement
{
    URHO3D_OBJECT(DropDownListWithTextAndButton, UIElement);

public:
    DropDownListWithTextAndButton(Context *context = gContext);

    DropDownListWithTextAndButton(char *text, int widthText, int widthDDList);

    static void RegisterObject(Context* context = gContext);

    void AddItem(char *text);
    void SetSelection(uint index);

    static SharedPtr<DropDownListWithTextAndButton> Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char * items[]);

private:
    DropDownListWithTextAndButton& operator=(const DropDownListWithTextAndButton&)
    {};

    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
    void HandleButtonDown(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    SharedPtr<Urho3D::DropDownList> ddList;
    SharedPtr<Urho3D::Button> buttonLeft;
    SharedPtr<Urho3D::Button> buttonRight;
};