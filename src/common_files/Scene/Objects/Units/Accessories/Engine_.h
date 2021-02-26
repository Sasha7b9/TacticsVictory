// 2021/02/26 21:54:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EngineT : public Component
{
public:

    EngineT(Context *context) : Component(context) {}

    virtual void Update(float timeStep) { UNUSED(timeStep); };

private:
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EngineAir : public EngineT
{
public:

    EngineAir(Context *context) : EngineT(context) {}

    virtual void Update(float timeStep) override;

private:
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EngineGround : public EngineT
{
public:

    EngineGround(Context *context) : EngineT(context) {}


    virtual void Update(float timeStep) override;
    
private:
};
