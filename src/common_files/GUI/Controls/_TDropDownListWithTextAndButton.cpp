/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "GUI/TCursor.h"
#include "GUI/TGUIEvents.h"
#include "GUI/Controls/_TDropDownListWithTextAndButton.h"
#include "GUI/Controls/_TLabel.h"
#include "Utils/TSettings.h"


DropDownListWithTextAndButton::DropDownListWithTextAndButton(Context *context) :
    UIElement(context)
{

}


DropDownListWithTextAndButton::DropDownListWithTextAndButton(char *text_, int widthText, int widthDDList) :
    UIElement(TheContext)
{
    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);

    window->SetLayout(LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<Label> text(Label::Create(text_, true, 15, widthText));
    text->SetStyle("Window");
    text->SetFixedHeight(SET::MENU::TEXT::HEIGHT);
    window->AddChild(text);

    ddList = CreateChild<DropDownList>();

    XMLFile *style = TheCache->GetResource<XMLFile>("UI/MainStyle.xml");
    ddList->SetDefaultStyle(style);

    ddList->SetStyleAuto();
    ddList->SetFixedSize(widthDDList, SET::MENU::DDLIST::HEIGHT);
    ddList->SetResizePopup(true);
    window->AddChild(ddList);

    SubscribeToEvent(ddList, E_ITEMSELECTED, URHO3D_HANDLER(DropDownListWithTextAndButton, HandleItemSelected));
    SubscribeToEvent(ddList, E_HOVERBEGIN, URHO3D_HANDLER(DropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(ddList, E_HOVEREND, URHO3D_HANDLER(DropDownListWithTextAndButton, HandleHoverEnd));

    buttonLeft = new Button(TheContext);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, E_PRESSED, URHO3D_HANDLER(DropDownListWithTextAndButton, HandleButtonDown));
    SubscribeToEvent(buttonLeft, E_HOVERBEGIN, URHO3D_HANDLER(DropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, E_HOVEREND, URHO3D_HANDLER(DropDownListWithTextAndButton, HandleHoverEnd));

    buttonRight = new Button(TheContext);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, E_PRESSED, URHO3D_HANDLER(DropDownListWithTextAndButton, HandleButtonDown));
    SubscribeToEvent(buttonRight, E_HOVERBEGIN, URHO3D_HANDLER(DropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(buttonRight, E_HOVEREND, URHO3D_HANDLER(DropDownListWithTextAndButton, HandleHoverEnd));

    SetMinSize(window->GetWidth(), window->GetHeight());
}


void DropDownListWithTextAndButton::SetSelection(uint index)
{
    ddList->SetSelection(index);
    VariantMap& eventData = GetEventDataMap();
    eventData[ItemSelected::P_ELEMENT] = this;
    eventData[ItemSelected::P_SELECTION] = ddList->GetSelection();
    SendEvent(E_ITEMSELECTED, eventData);
}


void DropDownListWithTextAndButton::RegisterObject(Context* context)
{
    context->RegisterFactory<DropDownListWithTextAndButton>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);
}


void DropDownListWithTextAndButton::AddItem(char *text)
{
    ddList->AddItem(Label::Create(text, true, 16));
}


void DropDownListWithTextAndButton::HandleItemSelected(StringHash, VariantMap& eventData_)
{
    VariantMap &eventData = GetEventDataMap();
    eventData[ItemSelected::P_ELEMENT] = this;
    eventData[ItemSelected::P_SELECTION] = eventData_[ItemSelected::P_SELECTION];
    SendEvent(E_ITEMSELECTED, eventData);
}


void DropDownListWithTextAndButton::HandleButtonDown(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Pressed::P_ELEMENT].GetPtr();

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
    eventData[ItemSelected::P_ELEMENT] = this;
    eventData[ItemSelected::P_SELECTION] = newItem;
    SendEvent(E_ITEMSELECTED, eventData);
}


SharedPtr<DropDownListWithTextAndButton> DropDownListWithTextAndButton::Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char *items[])
{
    SharedPtr<DropDownListWithTextAndButton> ddl(new DropDownListWithTextAndButton(text, widthText, widthDDList));
    for(uint64 i = 0; i < (uint64)numItems; i++)
    {
        ddl->AddItem(items[i]);
    }
    window->AddChild(ddl);
    
    return ddl;
}


void DropDownListWithTextAndButton::HandleHoverBegin(StringHash, VariantMap&)
{
    VariantMap &eventData = GetEventDataMap();
    eventData[HoverBeginElementGUI::P_ELEMENT] = this;
    SendEvent(E_HOVER_BEGIN_ELEMENT_GUI, eventData);
}


void DropDownListWithTextAndButton::HandleHoverEnd(StringHash, VariantMap&)
{
    VariantMap &eventData = GetEventDataMap();
    eventData[HoverEndElementGUI::P_ELEMENT] = this;
    SendEvent(E_HOVER_END_ELEMENT_GUI, eventData);
}
