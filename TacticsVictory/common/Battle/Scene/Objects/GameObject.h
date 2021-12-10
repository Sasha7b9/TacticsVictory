// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "System/Events.h"
#include "Scene/Objects/InfoWindow.h"


namespace Pi
{
    class GameObjectProperty;
    class InfoWindow;
    class UnitObject;

    namespace PiTypeProperty
    {
        const S GameObject = "GameObject";
    }

    namespace PiTypeGameObject
    {
        typedef StringHash S;

        const S Empty = "Empty";
        const S Unit  = "Unit";
    }

    //----------------------------------------------------------------------------------------------------------------------------
    class GameObject : public Node
    {
    public:

        GameObjectProperty &GetGameObjectProperty() { return *(GameObjectProperty *)GetProperty(PiTypeProperty::GameObject); }

        // Установить координаты объекта на карте. От мировых они отличаются на 0.5f
        void SetMapPosition(float mapX, float mapY);

        // Возвращает указатель на объект, кторый находится в экранных координатах coord
        static GameObject &GetFromScreen(const Point2D &coord);

        // Преобразует к указателю на UnitObject, если возможно, и возвращает nullptr в ином случае
        UnitObject *CastToUnitObject() { return IsUnit() ? (UnitObject *)this : nullptr; }

        bool IsUnit() const { return type == PiTypeGameObject::Unit; }

        static GameObject &Empty();

    protected:

        GameObject(PiTypeGameObject::S);

        virtual ~GameObject() {}

    private:
        void SetNodePosition(const Point3D &position) { Node::SetNodePosition(position); }

        PiTypeGameObject::S type;
    };


    //----------------------------------------------------------------------------------------------------------------------------
    class GameObjectController : public Controller, public LinkTarget<GameObjectController>
    {
    
    public:

        enum class Type
        {
            Unit
        };
    
        virtual ~GameObjectController() {};
    
        virtual void Preprocess() override { Controller::Preprocess(); }

        virtual void Move() override;
    
    protected:
    
        GameObjectController(Type gameObjType, PiTypeController::S contrType);
        GameObjectController(const GameObjectController &gameObjectController);
    
    private:
    
        Type gameObjectType;
    
        float scaleDefault = 1.0F;
        Vector3D rotateDefault {Vector3D::ZERO};
    
    
        Point3D coordGame;
    };


    //----------------------------------------------------------------------------------------------------------------------------
    class GameObjectProperty : public Property, public EventTarget
    {
        friend class GameObjectController;

    public:

        GameObjectProperty(GameObject &);

        virtual ~GameObjectProperty() { delete infoWindow; };

        bool Selectable() const { return gameObject.IsUnit(); }

        // Установить выделение
        void SetSelection();

        // Снять выделение
        void RemoveSelection();

        // Сюда посылается событие мыши : 0 - левая кнопка, 1 - средняя кнопка, 2 - правая кнопка
        void MouseEvent(uint state);

        void SetMapPosition(float x, float y) { positionMap = {x, y}; }

        bool Selected() const { return selected; }

        // Возвращает GameObjectProperty в позиции на экране, указываемой координатами coord
        static GameObjectProperty *GetFromScreen(const Point2D &coord);

        GameObject &gameObject;

    private:

        bool        selected = false;
        InfoWindow *infoWindow = nullptr;
        Vector3D    rotate = Vector3D::ZERO;
        float       scale = 1.0F;
        Vector2D    positionMap{0.0f, 0.0f};
    };
}
