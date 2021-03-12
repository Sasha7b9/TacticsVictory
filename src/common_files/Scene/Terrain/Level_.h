// 2021/03/12 12:00:05 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


URHO3D_EVENT(E_MAP_CHANGED, MapChanged)
{

}


class Level : public Object
{
    URHO3D_OBJECT(Level, Object);

public:

    Level() : Object(TheContext) {}

    struct LogicCell
    {
        float height;                   // Высота ячейки
    };

    void Clear() { level.Clear(); };

    void CreateFromVector(const Vector<Vector<float>> &lev);

    float GetHeight(uint rowX, uint colZ) const;

    void SetHeight(uint rowX, uint colZ, float height);

    void Load(const char *fileName);

    void Load(MemoryBuffer &msg);

    bool Save(const String &fileName);

    Vector<Vector<float>> CreateRandom(uint numRows, uint numCols);

    Vector<Vector<float>> map;

    Vector<Vector<LogicCell>> level;

};
