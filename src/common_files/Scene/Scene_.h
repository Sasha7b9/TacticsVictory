// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Tank;


class SceneT : public Scene
{
public:

    SceneT();
    virtual ~SceneT();

    virtual void Create();

    // Упаковать состояние сцены в buffer для передачи по сети
    void Comporess(VectorBuffer &buffer);

    // Распаковать состояние сцены из buffer-а, принятого по сети
    void Decompress(MemoryBuffer &buffer);
};
