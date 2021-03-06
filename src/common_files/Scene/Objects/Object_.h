// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/PhysicsParameters_.h"


class ObjectT;


//----------------------------------------------------------------------------------------------------------------------
// Здесь хранятся смещения для параметров модели, которые нужно применить к ней для правильной ориентации.
// Масштаб является параметром у node_
class ShiftParameters : public Object
{
    URHO3D_OBJECT(ShiftParameters, Object);

public:

    ShiftParameters() : Object(TheContext) {}

    float rotate = 0.0f;               // Поворот модели относительно направления ноды
    Vector3 position = Vector3::ZERO;  // Если модель не выровнена относительно начала координат, здесь смещение
};


//----------------------------------------------------------------------------------------------------------------------
// Специфичные для клент/серверных объектов параметры
class ObjectSpecific : public Object
{
    URHO3D_OBJECT(ObjectSpecific, Object);

public:

    static ObjectSpecific *Create(ObjectT *object);

    virtual void Update(float /*timeStep*/) {};

    virtual void OnPostRenderUpdate() {};

protected:

    ObjectSpecific(ObjectT *_object);

    ObjectT *object       = nullptr;
};


//----------------------------------------------------------------------------------------------------------------------
class ObjectT : public LogicComponent
{
    URHO3D_OBJECT(ObjectT, LogicComponent);

public:

    // Упаковать состояние объекта для передачи по сети
    virtual void Compress(VectorBuffer &buffer);

    // Распаковать состояние объекта, принятого по сети
    virtual void Decompress(MemoryBuffer &buffer);

    virtual void OnPostRenderUpdate();

    Node *GetObjectNode() const { return Component::GetNode(); }

    SharedPtr<ShiftParameters>   shift;     // Используется для приведения параметров модели к текущей сцене
    static Vector<ObjectT *>     storage;   // Здесь хранятся все объекты типа ObjectT (и их подклассы)
    SharedPtr<PhysicsParameters> physics;   // Параметры в физическом мире. Такие как координаты
    static ObjectT              *empty;     // Этот объект используется в качестве null-объекта

protected:

    ObjectT(Context *context);

    void LoadFromJSON();

    void Normalize(float k = 1.0f);

    virtual void OnNodeSet(Node *node) override;

    virtual void Start() override;

    virtual void DelayedStart() override;

    virtual void CreateSpecific() = 0;

    virtual void Update(float time) override;

    // Возвращает глубину вложенности node_ (относительно корневой ноды сцены)
    int NestingDepth() const;

    SharedPtr<ObjectSpecific> specific;         // Клиент/сервер специфичные параметры

private:

    // Непосредственный доступ к ноде запрещён в большинстве случаев. Там, где это необходимо, нужно использовать
    // GetObjectNode.
    Node *GetNode() const { return Component::GetNode(); }

    SharedPtr<StaticModel> staticModel;
};
