// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "System/Events.h"
#include "Objects/InfoWindow.h"
#include "Objects/GameObjectTypes.h"


namespace Pi
{
    class GameObjectProperty;
    class InfoWindow;
    class UnitObject;


    class GameObject : public Node
    {
    public:

        static void Construct();

        static void Destruct();

        GameObjectProperty &GetGameObjectProperty() { return *(GameObjectProperty *)GetProperty(PiTypeProperty::GameObject); }

        // Добавить объект в игру
        bool AppendInGame(int x, int y);

        template<typename T>
        T *GetController()
        {
            return (T *)Node::GetController();
        }

        // Возвращает указатель на объект, кторый находится в экранных координатах coord
        static GameObject &GetFromScreen(const Point2D &coord);

        // Преобразует к указателю на UnitObject, если возможно, и возвращает nullptr в ином случае
        UnitObject *CastToUnitObject() { return IsUnit() ? (UnitObject *)this : nullptr; }

        bool IsUnit() const { return typeObject == TypeGameObject::Unit; }

        static GameObject *empty;

        int GetID() const { return id; }

        void SetNodeDirection(const Vector3D &direction, const Vector3D &up = Vector3D::UP);

    protected:

        GameObject(TypeGameObject::S);

        virtual ~GameObject() {}

    private:

        TypeGameObject::S typeObject;

        static int createdObjects;              // Столько объектов уже создано
        int id = 0;
    };


    class GameObjectController : public Controller, public LinkTarget<GameObjectController>
    {
    public:
    
        virtual ~GameObjectController() {};
    
        virtual void Preprocess() override;

        virtual void Move() override;
    
    protected:
    
        GameObjectController(TypeGameObject::S typeObject, PiTypeController::S contrType);
        GameObjectController(const GameObjectController &gameObjectController);
    
    private:
    
        TypeGameObject::S typeObject;
        float scaleDefault = 1.0F;
        Vector3D rotateDefault {Vector3D::ZERO};
        Point3D coordGame;
        GameObjectProperty *property = nullptr;
    };


    class GameObjectProperty : public Property, public EventTarget
    {
        friend class GameObjectController;

    public:

        GameObjectProperty(GameObject &);

        virtual ~GameObjectProperty();

        bool Selectable() const { return gameObject.IsUnit(); }

        // Установить выделение
        void SetSelection();

        // Снять выделение
        void RemoveSelection();

        // Сюда посылается событие мыши : 0 - левая кнопка, 1 - средняя кнопка, 2 - правая кнопка
        void MouseEvent(uint state);

        bool Selected() const { return selected; }

        // Возвращает GameObjectProperty в позиции на экране, указываемой координатами coord
        static GameObjectProperty *GetFromScreen(const Point2D &coord);

        GameObject &gameObject;

    private:

        bool        selected = false;
        InfoWindow *infoWindow = nullptr;
    };
}
