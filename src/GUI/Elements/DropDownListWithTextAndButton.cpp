#include <stdafx.h>


#include "GUI/Elements/DropDownListWithTextAndButton.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"


DropDownListWithTextAndButton::DropDownListWithTextAndButton(Context *context) :
    UIElement(context)
{

}


DropDownListWithTextAndButton::DropDownListWithTextAndButton(char *text_, int widthText, int widthDDList) :
    UIElement(gContext)
{
    SharedPtr<Window> window(new Window(gContext));
    window->SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);

    window->SetLayout(Urho3D::LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<Label> text(Label::Create(text_, 15, widthText));
    text->SetStyle("Window");
    text->SetFixedHeight(SET::MENU::TEXT::HEIGHT);
    window->AddChild(text);

    ddList = CreateChild<Urho3D::DropDownList>();

    XMLFile *style = gCache->GetResource<XMLFile>("UI/MainStyle.xml");
    ddList->SetDefaultStyle(style);

    ddList->SetStyleAuto();
    ddList->SetFixedSize(widthDDList, SET::MENU::DDLIST::HEIGHT);
    ddList->SetResizePopup(true);
    window->AddChild(ddList);

    SubscribeToEvent(ddList, Urho3D::E_ITEMSELECTED, HANDLER(DropDownListWithTextAndButton, HandleItemSelected));
    SubscribeToEvent(ddList, Urho3D::E_HOVERBEGIN, HANDLER(DropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(ddList, Urho3D::E_HOVEREND, HANDLER(DropDownListWithTextAndButton, HandleHoverEnd));

    buttonLeft = new Urho3D::Button(gContext);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, Urho3D::E_PRESSED, HANDLER(DropDownListWithTextAndButton, HandleButtonDown));
    SubscribeToEvent(buttonLeft, Urho3D::E_HOVERBEGIN, HANDLER(DropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, Urho3D::E_HOVEREND, HANDLER(DropDownListWithTextAndButton, HandleHoverEnd));

    buttonRight = new Urho3D::Button(gContext);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, Urho3D::E_PRESSED, HANDLER(DropDownListWithTextAndButton, HandleButtonDown));
    SubscribeToEvent(buttonRight, Urho3D::E_HOVERBEGIN, HANDLER(DropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(buttonRight, Urho3D::E_HOVEREND, HANDLER(DropDownListWithTextAndButton, HandleHoverEnd));

    SetMinSize(window->GetWidth(), window->GetHeight());
}

void DropDownListWithTextAndButton::SetSelection(uint index)
{
    ddList->SetSelection(index);
    VariantMap& eventData = GetEventDataMap();
    eventData[Urho3D::ItemSelected::P_ELEMENT] = this;
    eventData[Urho3D::ItemSelected::P_SELECTION] = ddList->GetSelection();
    SendEvent(Urho3D::E_ITEMSELECTED, eventData);
}

void DropDownListWithTextAndButton::RegisterObject(Context* context)
{
    context->RegisterFactory<DropDownListWithTextAndButton>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void DropDownListWithTextAndButton::AddItem(char *text)
{
    ddList->AddItem(Label::Create(text, 16));
}

void DropDownListWithTextAndButton::HandleItemSelected(StringHash, VariantMap& eventData_)
{
    VariantMap &eventData = GetEventDataMap();
    eventData[Urho3D::ItemSelected::P_ELEMENT] = this;
    eventData[Urho3D::ItemSelected::P_SELECTION] = eventData_[Urho3D::ItemSelected::P_SELECTION];
    SendEvent(Urho3D::E_ITEMSELECTED, eventData);
}

void DropDownListWithTextAndButton::HandleButtonDown(StringHash, VariantMap& eventData)
{
    Urho3D::Button *button = (Urho3D::Button*)eventData[Urho3D::Pressed::P_ELEMENT].GetPtr();

    uint currentItem = ddList->GetSelection();
    uint numItems = ddList->GetNumItems();
    uint newItem = 0;

    if(button == buttonLeft)
    {
        newItem = currentItem == 0 ? numItems - 1 : currentItem - 1;
    }
    else if(button == buttonRight)
    {
        newItem = currentItem == numItems - 1 ? 0 : currentItem + 1;
    }
    ddList->SetSelection(newItem);

    eventData = GetEventDataMap();
    eventData[Urho3D::ItemSelected::P_ELEMENT] = this;
    eventData[Urho3D::ItemSelected::P_SELECTION] = newItem;
    SendEvent(Urho3D::E_ITEMSELECTED, eventData);
}

SharedPtr<DropDownListWithTextAndButton> DropDownListWithTextAndButton::Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char *items[])
{
    SharedPtr<DropDownListWithTextAndButton> ddl(new DropDownListWithTextAndButton(text, widthText, widthDDList));
    for(int i = 0; i < numItems; i++)
    {
        ddl->AddItem(items[i]);
    }
    window->AddChild(ddl);
    
    return ddl;
}

void DropDownListWithTextAndButton::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void DropDownListWithTextAndButton::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}