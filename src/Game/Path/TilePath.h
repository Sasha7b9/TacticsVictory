#pragma once


class TilePath : public UObject
{
    OBJECT(TilePath);
public:
    TilePath();
    ~TilePath();
    void SetPosition(const Vector3 &pos);
    void SetVisible(bool visible);

    static void Add(Vector3 &pos);
    static void DisableAll();
    static void RemoveAll();

private:
    TilePath& operator=(const TilePath&)
    {};
    SharedPtr<Node> node;

    static uint numTilesAll;
    static uint numTilesEnabled;
    static Vector<SharedPtr<TilePath>> tiles;
};