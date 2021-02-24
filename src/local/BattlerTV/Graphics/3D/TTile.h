// 2021/02/24 16:50:25 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Tile : public LogicComponent
{
    URHO3D_OBJECT(Tile, LogicComponent);

public:

    Tile(Node *node, pchar name);
    ~Tile();
};
