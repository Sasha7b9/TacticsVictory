// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EngineT : public Component
{
    URHO3D_OBJECT(EngineT, Component);

public:

    EngineT(Context *context) : Component(context) {}

    virtual void Update(float timeStep) { UNUSED(timeStep); };

private:
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EngineAir : public EngineT
{
    URHO3D_OBJECT(EngineAir, EngineT);

public:

    EngineAir(Context *context) : EngineT(context) {}

    virtual void Update(float timeStep) override;

private:
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EngineGround : public EngineT
{
    URHO3D_OBJECT(EngineGround, EngineT);

public:

    EngineGround(Context *context) : EngineT(context) {}

    virtual void Update(float timeStep) override;

    void OnNodeSet(Node *node) override;

    static void CreateEngine(Node *node);
    
private:
};
