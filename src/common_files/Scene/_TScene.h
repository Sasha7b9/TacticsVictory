/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


class Tank;


class TScene : public Scene
{
    URHO3D_OBJECT(TScene, Scene);

public:

    TScene(Context *context = TheContext);
    virtual ~TScene();

    static void RegisterObject(Context *context = TheContext);

    virtual void Create();

    Vector<Vector<float>> level;
};
