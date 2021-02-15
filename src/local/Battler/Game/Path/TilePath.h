#pragma once



class TilePath : public Object
{
    URHO3D_OBJECT(TilePath, Object);
public:
    TilePath();
    ~TilePath();
    void SetPosition(const Vector3 &pos);
    void SetVisible(bool visible);

    static void Add(const Vector3 &pos);
    static void DisableAll();
    static void RemoveAll();

private:
    SharedPtr<Node> node;
    static uint numTilesAll;
    static uint numTilesEnabled;
    static Vector<SharedPtr<TilePath>> tiles;

    DEFAULT_MEMBERS(TilePath);
};
