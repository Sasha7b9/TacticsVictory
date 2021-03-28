// 2021/03/28 21:56:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/OrderedTable_.h"
#include "Utils/Settings.h"


HeaderTable::HeaderTable() : WindowT(TheContext)
{

}


LineTable::LineTable(HeaderTable *header) : WindowT(TheContext)
{

}


OrderedTable::OrderedTable(UIElement *ui_element, char *title) : WindowT(TheContext)
{
    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);

    window->SetLayout(LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<Label> label_title(Label::Create(title, true, 15, 700, 20));
    label_title->SetTextAlignment(HA_CENTER);
    window->AddChild(label_title);

    SetMinSize(window->GetWidth(), window->GetHeight());

    ui_element->AddChild(this);
}