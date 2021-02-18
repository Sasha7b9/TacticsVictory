/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


class Tank;


class TScene : public Object
{
    URHO3D_OBJECT(TScene, Object);

public:

    TScene(Context *context = TheContext);
    virtual ~TScene();

    static void RegisterObject(Context *context = TheContext);

    virtual void Update(float timeStep);
    virtual void Create();

    Vector<Vector<float>> level;

    Scene *scene = nullptr;
};
