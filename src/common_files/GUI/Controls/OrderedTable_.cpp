// 2021/03/28 21:56:56 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_v.h"
#include "GUI/Controls/OrderedTable_.h"
#include "GUI/Controls/Buttons/Button_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Utils/StringUtils_.h"


struct HeaderRowStruct
{
    static const int NUM = 7;

    pchar name;
    int width;
    HorizontalAlignment h_align;
};


static HeaderRowStruct header_rows[HeaderRowStruct::NUM] =
{
    { "Name",    360, HA_LEFT},
    { "Address", 125, HA_CENTER},
    { "Ping",    40,  HA_CENTER},
    { "CPU%",    40,  HA_CENTER},
    { "L",       40,  HA_CENTER},
    { "N",       40,  HA_CENTER},
    { "P",       40,  HA_CENTER}
};


HeaderTable::HeaderTable() : Control(TheContext)
{
    for (int i = 0; i < HeaderRowStruct::NUM; i++)
    {
        columns.Push({ header_rows[i].name, header_rows[i].width });
    }

    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/OrderedTableStyle.xml"));
    window->SetStyle(TheSettings.GetString("menu", "elem", "window", "style"));
    AddChild(window);

    window->SetLayout(LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    for (uint i = 0; i < columns.Size(); i++)
    {
        Column &column = columns[i];
        SharedPtr<ButtonT> header_row(new ButtonT(window, column.name));
        header_row->SetName(column.name);
        header_row->SetFixedWidth(column.width);
        window->AddChild(header_row);
    }

    SetMinSize(window->GetWidth(), window->GetHeight());
}


LineTable::LineTable(HeaderTable *header) : Control(TheContext)
{
    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(TheSettings.GetString("menu", "elem", "window", "style"));
    AddChild(window);

    window->SetLayout(LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    for (int i = 0; i < HeaderRowStruct::NUM; i++)
    {
        SharedPtr<Label> label = Label::Create("", 20, -1, -1, false);

        if (i == 0)      { name = label; }
        else if (i == 1) { address = label; }
        else if (i == 2) { ping = label; }
        else if (i == 3) { cpu = label; }
        else if (i == 4) { lang = label; }
        else if (i == 5) { network = label; }
        else if (i == 6) { players = label; }

        label->SetAlignment(HA_CENTER, VA_CENTER);
        label->SetTextAlignment(header_rows[i].h_align);
        UIElement *h = header->GetChild(header_rows[i].name, true);

        label->SetFixedWidth(h->GetWidth());
        window->AddChild(label);
    }

    SetMinSize(window->GetWidth(), window->GetHeight());
}


void LineTable::SetServerInfo(std::string info)
{
    std::vector<std::string> words;

    SU::SplitToWords(info.c_str(), words, ",|");

    name->SetText(words.size() > 0 ? words[0].c_str() : "");

    address->SetText(words.size() > 1 ? words[1].c_str() : "");

    ping->SetText(words.size() > 2 ? words[2].c_str() : "");

    cpu->SetText(words.size() > 3 ? words[3].c_str() : "");
}


OrderedTable::OrderedTable(UIElement *ui_element, char *title) : Control(TheContext)
{
    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(TheSettings.GetString("menu", "elem", "window", "style"));
    AddChild(window);

    window->SetLayout(LM_VERTICAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<Label> label_title(Label::Create(title, 15, 700, 20));
    label_title->SetAlignment(HA_CENTER, VA_CENTER);
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


void OrderedTable::SetServersInfo(std::string &data)
{
    for (uint i = 0; i < NUM_LINES; i++)
    {
        size_t pos = data.find('|');

        if (pos != std::string::npos)
        {
            std::string text = data.substr(0, pos);
            lines[i]->SetServerInfo(text);
            data.erase(0, pos + 1);
        }
        else
        {
            lines[i]->SetServerInfo("");
        }
    }
}
