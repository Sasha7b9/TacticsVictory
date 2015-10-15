#include <stdafx.h>


tvDropDownListWithTextAndButton::tvDropDownListWithTextAndButton(char *text_, int widthText, int widthDDList) :
    UIElement(gContext)
{
    SharedPtr<Window> window(new Window(gContext));
    window->SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);

    window->SetLayout(Urho3D::LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<tvLabel> text(tvLabel::Create(text_, 15, widthText));
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

    SubscribeToEvent(ddList, E_ITEMSELECTED, HANDLER(tvDropDownListWithTextAndButton, HandleItemSelected));
    SubscribeToEvent(ddList, E_HOVERBEGIN, HANDLER(tvDropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(ddList, E_HOVEREND, HANDLER(tvDropDownListWithTextAndButton, HandleHoverEnd));

    buttonLeft = new Button(gContext);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, E_PRESSED, HANDLER(tvDropDownListWithTextAndButton, HandleButtonDown));
    SubscribeToEvent(buttonLeft, E_HOVERBEGIN, HANDLER(tvDropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, E_HOVEREND, HANDLER(tvDropDownListWithTextAndButton, HandleHoverEnd));

    buttonRight = new Button(gContext);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, E_PRESSED, HANDLER(tvDropDownListWithTextAndButton, HandleButtonDown));
    SubscribeToEvent(buttonRight, E_HOVERBEGIN, HANDLER(tvDropDownListWithTextAndButton, HandleHoverBegin));
    SubscribeToEvent(buttonRight, E_HOVEREND, HANDLER(tvDropDownListWithTextAndButton, HandleHoverEnd));

    SetMinSize(window->GetWidth(), window->GetHeight());
}

void tvDropDownListWithTextAndButton::SetSelection(uint index)
{
    ddList->SetSelection(index);
    VariantMap& eventData = GetEventDataMap();
    eventData[Urho3D::ItemSelected::P_ELEMENT] = this;
    eventData[Urho3D::ItemSelected::P_SELECTION] = ddList->GetSelection();
    SendEvent(E_ITEMSELECTED, eventData);
}

void tvDropDownListWithTextAndButton::AddItem(char *text)
{
    ddList->AddItem(tvLabel::Create(text, 16));
}

void tvDropDownListWithTextAndButton::HandleItemSelected(StringHash, VariantMap& eventData_)
{
    VariantMap &eventData = GetEventDataMap();
    eventData[Urho3D::ItemSelected::P_ELEMENT] = this;
    eventData[Urho3D::ItemSelected::P_SELECTION] = eventData_[Urho3D::ItemSelected::P_SELECTION];
    SendEvent(E_ITEMSELECTED, eventData);
}

void tvDropDownListWithTextAndButton::HandleButtonDown(StringHash, VariantMap& eventData)
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

SharedPtr<tvDropDownListWithTextAndButton> tvDropDownListWithTextAndButton::Create(Window *window, char *text, int widthText, int widthDDList, int numItems, char *items[])
{
    SharedPtr<tvDropDownListWithTextAndButton> ddl(new tvDropDownListWithTextAndButton(text, widthText, widthDDList));
    for(int i = 0; i < numItems; i++)
    {
        ddl->AddItem(items[i]);
    }
    window->AddChild(ddl);
    
    return ddl;
}

void tvDropDownListWithTextAndButton::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void tvDropDownListWithTextAndButton::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}