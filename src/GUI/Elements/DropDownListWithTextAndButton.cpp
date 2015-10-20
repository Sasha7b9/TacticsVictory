#include <stdafx.h>


#include "GUI/Elements/DropDownListWithTextAndButton.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"


vDropDownListWithTextAndButton::vDropDownListWithTextAndButton(char *text_, int widthText, int widthDDList) :
    UIElement(gContext)
{
    SharedPtr<Window> window(new Window(gContext));
    window->SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);

    window->SetLayout(Urho3D::LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<vLabel> text(vLabel::Create(text_, 15, widthText));
    text->SetStyle("Window");
    text->SetFixedHeight(SET::MENU::TEXT::HEIGHT);
    window->AddChild(text);

    ddList = CreateChild<DropDownList>();

    XMLFile *style = gCache->GetResource<XMLFile>("UI/MainStyle.xml");
    ddList->SetDefaultStyle(style);

    ddList->SetStyleAuto();
    ddList->SetFixedSize(widthDDList, SET::MENU::DDLIST::HEIGHT);
    ddList->SetResizePopup(true);
    window->AddChild(ddList);

    SubscribeToEvent(ddList, E_ITEMSELECTED, HANDLER(vDropDownListWithTextAndButton, HandleItemSelected));
    SubscribeToEvent(ddList, E_HOVERBEGIN, HANDLER(vDropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(ddList, E_HOVEREND, HANDLER(vDropDownListWithTextAndButton, HandleHoverEnd));

    buttonLeft = new Button(gContext);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, E_PRESSED, HANDLER(vDropDownListWithTextAndButton, HandleButtonDown));
    SubscribeToEvent(buttonLeft, E_HOVERBEGIN, HANDLER(vDropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, E_HOVEREND, HANDLER(vDropDownListWithTextAndButton, HandleHoverEnd));

    buttonRight = new Button(gContext);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, E_PRESSED, HANDLER(vDropDownListWithTextAndButton, HandleButtonDown));
    SubscribeToEvent(buttonRight, E_HOVERBEGIN, HANDLER(vDropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(buttonRight, E_HOVEREND, HANDLER(vDropDownListWithTextAndButton, HandleHoverEnd));

    SetMinSize(window->GetWidth(), window->GetHeight());
}

void vDropDownListWithTextAndButton::SetSelection(uint index)
{
    ddList->SetSelection(index);
    VariantMap& eventData = GetEventDataMap();
    eventData[Urho3D::ItemSelected::P_ELEMENT] = this;
    eventData[Urho3D::ItemSelected::P_SELECTION] = ddList->GetSelection();
    SendEvent(E_ITEMSELECTED, eventData);
}

void vDropDownListWithTextAndButton::AddItem(char *text)
{
    ddList->AddItem(vLabel::Create(text, 16));
}

void vDropDownListWithTextAndButton::HandleItemSelected(StringHash, VariantMap& eventData_)
{
    VariantMap &eventData = GetEventDataMap();
    eventData[Urho3D::ItemSelected::P_ELEMENT] = this;
    eventData[Urho3D::ItemSelected::P_SELECTION] = eventData_[Urho3D::ItemSelected::P_SELECTION];
    SendEvent(E_ITEMSELECTED, eventData);
}

void vDropDownListWithTextAndButton::HandleButtonDown(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Urho3D::Pressed::P_ELEMENT].GetPtr();

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
    SendEvent(E_ITEMSELECTED, eventData);
}

SharedPtr<vDropDownListWithTextAndButton> vDropDownListWithTextAndButton::Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char *items[])
{
    SharedPtr<vDropDownListWithTextAndButton> ddl(new vDropDownListWithTextAndButton(text, widthText, widthDDList));
    for(int i = 0; i < numItems; i++)
    {
        ddl->AddItem(items[i]);
    }
    window->AddChild(ddl);
    
    return ddl;
}

void vDropDownListWithTextAndButton::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void vDropDownListWithTextAndButton::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}