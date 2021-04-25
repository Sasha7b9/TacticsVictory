// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "GUI/Cursor_.h"
#include "GUI/GUIEvents_.h"
#include "GUI/Controls/DropDownListWithTextAndButton_.h"
#include "GUI/Controls/Label_.h"


DropDownListWithTextAndButton::DropDownListWithTextAndButton(Context *context) :
    UIElement(context)
{

}


DropDownListWithTextAndButton::DropDownListWithTextAndButton(pchar text_, int widthText, int widthDDList) :
    UIElement(TheContext)
{
    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(TheSettings.GetString("menu", "elem", "window", "style"));
    AddChild(window);

    window->SetLayout(LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<Label> text(Label::Create(text_, 15, widthText));
    text->SetAlignment(HA_CENTER, VA_CENTER);
    text->SetStyle("Window");
    text->SetFixedHeight(TheSettings.GetInt("menu", "text", "height"));
    window->AddChild(text);

    ddList = CreateChild<DropDownList>();

    XMLFile *style = TheCache->GetResource<XMLFile>("UI/MainStyle.xml");
    ddList->SetDefaultStyle(style);

    ddList->SetStyleAuto();
    ddList->SetFixedSize(widthDDList, TheSettings.GetInt("menu", "ddlist", "height"));
    ddList->SetResizePopup(true);
    window->AddChild(ddList);

    SubscribeToEvent(ddList, E_ITEMSELECTED, URHO3D_HANDLER(DropDownListWithTextAndButton, HandlerItemSelected));
    SubscribeToEvent(ddList, E_HOVERBEGIN, URHO3D_HANDLER(DropDownListWithTextAndButton, HandlerHoverBegin));
    SubscribeToEvent(ddList, E_HOVEREND, URHO3D_HANDLER(DropDownListWithTextAndButton, HandlerHoverEnd));

    buttonLeft = new Button(TheContext);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, E_PRESSED, URHO3D_HANDLER(DropDownListWithTextAndButton, HandlerButtonDown));
    SubscribeToEvent(buttonLeft, E_HOVERBEGIN, URHO3D_HANDLER(DropDownListWithTextAndButton, HandlerHoverBegin));
    SubscribeToEvent(buttonLeft, E_HOVEREND, URHO3D_HANDLER(DropDownListWithTextAndButton, HandlerHoverEnd));

    buttonRight = new Button(TheContext);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, E_PRESSED, URHO3D_HANDLER(DropDownListWithTextAndButton, HandlerButtonDown));
    SubscribeToEvent(buttonRight, E_HOVERBEGIN, URHO3D_HANDLER(DropDownListWithTextAndButton, HandlerHoverBegin));
    SubscribeToEvent(buttonRight, E_HOVEREND, URHO3D_HANDLER(DropDownListWithTextAndButton, HandlerHoverEnd));

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


void DropDownListWithTextAndButton::RegisterObject()
{
    TheContext->RegisterFactory<DropDownListWithTextAndButton>("UI");

    Context *context = TheContext;

    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);
}


void DropDownListWithTextAndButton::AddItem(char *text)
{
    SharedPtr<Label> label(Label::Create(text, 16));
    label->SetAlignment(HA_CENTER, VA_CENTER);
    ddList->AddItem(label);
}


void DropDownListWithTextAndButton::HandlerItemSelected(StringHash, VariantMap& eventData_)
{
    VariantMap &eventData = GetEventDataMap();
    eventData[ItemSelected::P_ELEMENT] = this;
    eventData[ItemSelected::P_SELECTION] = eventData_[ItemSelected::P_SELECTION];
    SendEvent(E_ITEMSELECTED, eventData);
}


void DropDownListWithTextAndButton::HandlerButtonDown(StringHash, VariantMap& eventData)
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


SharedPtr<DropDownListWithTextAndButton> DropDownListWithTextAndButton::Create(Window *window, pchar text,
    int widthText, int widthDDList, int numItems, pchar items[])
{
    SharedPtr<DropDownListWithTextAndButton> ddl(new DropDownListWithTextAndButton(text, widthText, widthDDList));
    for(uint64 i = 0; i < (uint64)numItems; i++)
    {
        ddl->AddItem(items[i]);
    }
    window->AddChild(ddl);
    
    return ddl;
}


void DropDownListWithTextAndButton::HandlerHoverBegin(StringHash, VariantMap&)
{
    SendEvent(E_HOVER_BEGIN_ELEMENT_GUI, GetEventDataMap());
}


void DropDownListWithTextAndButton::HandlerHoverEnd(StringHash, VariantMap&)
{
    SendEvent(E_HOVER_END_ELEMENT_GUI, GetEventDataMap());
}
