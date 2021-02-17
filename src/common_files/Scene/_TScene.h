/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


class Tank;


class TScene : public Object
{
    URHO3D_OBJECT(TScene, Object);

public:

    TScene(Context *context = TheContext);
    virtual ~TScene();

    virtual void Update(float timeStep);
    virtual void Create();

    void SetSelected(Tank *node, bool selected);
    Tank* GetSelected();

    Vector<Vector<float>> level;

    Scene *scene = nullptr;

    virtual void Existor() = 0;     // Эта функция нужна для того, чтобы было нельзя создать объект этого типа

protected:

    virtual SharedPtr<Tank> CreateTank() = 0;

private:

    void RegisterObjects();
};
