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


    //----------------------------------------------------------------------------------------------------------------------------
    class GameObject : public Node
    {
    public:

        static void Construct();

        static void Destruct();

        GameObjectProperty &GetGameObjectProperty() { return *(GameObjectProperty *)GetProperty(PiTypeProperty::GameObject); }

        // ���������� ���������� ������� �� �����. �� ������� ��� ���������� �� 0.5f
        void SetMapPosition(float mapX, float mapY);

        void SetMapPosition(float mapX, float mapY, float mapZ);

        // ���������� ��������� �� ������, ������ ��������� � �������� ����������� coord
        static GameObject &GetFromScreen(const Point2D &coord);

        // ����������� � ��������� �� UnitObject, ���� ��������, � ���������� nullptr � ���� ������
        UnitObject *CastToUnitObject() { return IsUnit() ? (UnitObject *)this : nullptr; }

        bool IsUnit() const { return typeObject == TTypeGameObject::Unit; }

        static GameObject *empty;

        int GetID() const { return id; }

    protected:

        GameObject(TTypeGameObject::S);

        virtual ~GameObject() {}

    private:
        void SetNodePosition(const Point3D &position) { Node::SetNodePosition(position); }

        TTypeGameObject::S typeObject;

        static int createdObjects;              // ������� �������� ��� �������
        int id = 0;
    };


    //----------------------------------------------------------------------------------------------------------------------------
    class GameObjectController : public Controller, public LinkTarget<GameObjectController>
    {
    public:
    
        virtual ~GameObjectController() {};
    
        virtual void Preprocess() override;

        virtual void Move() override;
    
    protected:
    
        GameObjectController(TTypeGameObject::S typeObject, PiTypeController::S contrType);
        GameObjectController(const GameObjectController &gameObjectController);
    
    private:
    
        TTypeGameObject::S typeObject;
        float scaleDefault = 1.0F;
        Vector3D rotateDefault {Vector3D::ZERO};
        Point3D coordGame;
        GameObjectProperty *property = nullptr;
    };


    //----------------------------------------------------------------------------------------------------------------------------
    class GameObjectProperty : public Property, public EventTarget
    {
        friend class GameObjectController;

    public:

        GameObjectProperty(GameObject &);

        virtual ~GameObjectProperty();

        bool Selectable() const { return gameObject.IsUnit(); }

        // ���������� ���������
        void SetSelection();

        // ����� ���������
        void RemoveSelection();

        // ���� ���������� ������� ���� : 0 - ����� ������, 1 - ������� ������, 2 - ������ ������
        void MouseEvent(uint state);

        void SetMapPosition(float x, float y) { positionMap = {x, y}; }

        bool Selected() const { return selected; }

        // ���������� GameObjectProperty � ������� �� ������, ����������� ������������ coord
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
