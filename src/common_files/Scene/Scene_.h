// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Tank;


class SceneT : public Scene
{
    URHO3D_OBJECT(SceneT, Scene);

public:

    SceneT(Context *context = TheContext);
    virtual ~SceneT();

    static void RegisterComponent(Context *context = TheContext);

    virtual void Create();
};
