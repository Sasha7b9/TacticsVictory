#pragma once


class lTilePath : public Object
{
    OBJECT(lTilePath);
public:
    lTilePath();
    lTilePath(const lTilePath &tile);
    ~lTilePath();
    void SetPosition(const Vector3 &pos);
    void SetVisible(bool visible);

    static void Add(Vector3 &pos);
    static void DisableAll();
    static void RemoveAll();

private:
    lTilePath& operator=(const lTilePath&)
    {};
    SharedPtr<Node> node;

    static uint numTilesAll;
    static uint numTilesEnabled;
    static Vector<SharedPtr<lTilePath>> tiles;
};