// 2021/03/28 21:56:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class LineTable : public WindowT
{
    URHO3D_OBJECT(LineTable, WindowT);

public:

    LineTable();
};


class OrderedTable : public WindowT
{
    URHO3D_OBJECT(OrderedTable, WindowT);

public:

    OrderedTable(char *table);
};
