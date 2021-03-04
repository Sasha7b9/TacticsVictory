// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Tank;


class SceneT : public Scene
{
public:

    SceneT(Context *context = TheContext);
    virtual ~SceneT();

    virtual void Create();
};
