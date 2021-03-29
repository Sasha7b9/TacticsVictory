// 2021/03/28 21:56:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/OrderedTable_.h"
#include "GUI/Controls/Buttons/Button_.h"
#include "Utils/Settings.h"


struct HeaderRowStruct
{
    pchar name;
    int width;
    static const int NUM = 4;
};


static const HeaderRowStruct header_rows[HeaderRowStruct::NUM] =
{
    { "Name", 450 },
    { "Address", 150 },
    { "Ping", 60 },
    { "CPU%", 60 }
};


HeaderTable::HeaderTable() : WindowT(TheContext)
{
    for (int i = 0; i < HeaderRowStruct::NUM; i++)
    {
        rows.Push({ header_rows[i].name, header_rows[i].width });
    }

    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/OrderedTableStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);

    window->SetLayout(LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    for (uint i = 0; i < rows.Size(); i++)
    {
        Row &row = rows[i];
        SharedPtr<ButtonT> header_row(new ButtonT(window, row.name));
        header_row->SetName(row.name);
        header_row->SetMinWidth(row.width);
        window->AddChild(header_row);
    }

    SetMinSize(window->GetWidth(), window->GetHeight());
}


LineTable::LineTable(HeaderTable *header) : WindowT(TheContext)
{
    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);

    window->SetLayout(LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    for (int i = 0; i < HeaderRowStruct::NUM; i++)
    {
        String name = String("test") + header_rows[i].name;

        SharedPtr<Label> label = Label::Create(name.CString());
        UIElement *h = header->GetChild(header_rows[i].name, true);
        label->SetMinWidth(h->GetWidth());
        window->AddChild(label);
    }

    SetMinSize(window->GetWidth(), window->GetHeight());
}


OrderedTable::OrderedTable(UIElement *ui_element, char *title) : WindowT(TheContext)
{
    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);

    window->SetLayout(LM_VERTICAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<Label> label_title(Label::Create(title, true, 15, 700, 20));
    label_title->SetTextAlignment(HA_CENTER);
    window->AddChild(label_title);

    header = new HeaderTable();
    window->AddChild(header);

    for (int i = 0; i < NUM_LINES; i++)
    {
        SharedPtr<LineTable> line(new LineTable(header));
        window->AddChild(line);
        lines.Push(line);
    }

    SetMinSize(window->GetWidth(), window->GetHeight());

    ui_element->AddChild(this);
}