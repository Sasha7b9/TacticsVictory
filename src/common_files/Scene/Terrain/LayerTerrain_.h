// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

class CubeTerrain;

class LayerTerrain : public Object
{
    URHO3D_OBJECT(LayerTerrain, Object);

public:
    LayerTerrain(Context *context = TheContext);
    ~LayerTerrain();
    void AddCube(const SharedPtr<CubeTerrain> &cube);
    void Create();
    void Build();
    CubeTerrain* GetCube(uint row, uint col);

    Vector<SharedPtr<CubeTerrain>> cubes;

private:
    SharedPtr<Geometry> geometry;
    SharedPtr<Model> model;
    SharedPtr<StaticModel> object;

    Node *CreateChild();
};
