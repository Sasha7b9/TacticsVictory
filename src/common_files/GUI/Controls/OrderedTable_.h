// 2021/03/28 21:56:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Label_.h"


struct ServerInfo;


class HeaderTable : public WindowT
{
    URHO3D_OBJECT(HeaderTable, WindowT);

public:

    HeaderTable();

    struct Column
    {
        Column(pchar n, int w) : name(n), width(w) {}
        pchar name;
        int   width;
    };

    Vector<Column> columns;
};


class LineTable : public WindowT
{
    URHO3D_OBJECT(LineTable, WindowT);

public:

    LineTable(HeaderTable *header);

    void SetServerInfo(ServerInfo *info);

    SharedPtr<Label> name;
    SharedPtr<Label> address;
    SharedPtr<Label> ping;
    SharedPtr<Label> cpu;
};


class OrderedTable : public WindowT
{
    URHO3D_OBJECT(OrderedTable, WindowT);

    void SetServersInfo(const std::string &data);

public:

    OrderedTable(UIElement *ui_element, char *title);

    SharedPtr<HeaderTable> header;
    Vector<LineTable *> lines;

    static const int NUM_LINES = 10;
};
