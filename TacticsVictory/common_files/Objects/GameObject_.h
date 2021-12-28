// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "System/Events.h"
#include "Objects/GameObjectTypes_.h"


namespace Pi
{
    class GameObjectController;
    class GameObjectProperty;
    class InfoWindow;
    class UnitObject;


    class GameObject : public Node, public MapElement<GameObject>
    {
    public:

        typedef int KeyType;

        KeyType GetKey() const { return id; }

        static void Construct();

        static void Destruct();

        GameObjectProperty &GetGameObjectProperty() { return *(GameObjectProperty *)GetProperty(PiTypeProperty::GameObject); }

        // Добавить объект в игру
        bool AppendInGame(int x, int y);

        template<typename T> T *GetController() { return (T *)Node::GetController(); }

        // Возвращает указатель на объект, кторый находится в экранных координатах coord
        static GameObject &GetFromScreen(const Point2D &coord);

        // Преобразует к указателю на UnitObject, если возможно, и возвращает nullptr в ином случае
        UnitObject *GetUnitObject() { return IsUnit() ? (UnitObject *)this : nullptr; }

        bool IsUnit() const { return typeGameObject == TypeGameObject::Unit; }

        static GameObject *empty;

        void SetDirection(const Vector3D &direction, const Vector3D &up = Vector3D::UP);

        Node *GetNodeGeometry() { return nodeGeometry; }

        Node *GetMainNode() { return this; }

        // Создаёт узел с именем name и подвешивает к нему узел с геометрией
        Node *CreateNodeForGeometry(pchar name, Node *nodeGeometry);

        const TypeGameObject typeGameObject;

        static Map<GameObject> objects;

        GameObjectController * const controller = nullptr;

        const int id = 0;

        const int numberThread = 0;            // Номер потока, который будет обрабатывать этот объект

    protected:

        GameObject(TypeGameObject, int, GameObjectController *);

        virtual ~GameObject();

    private:

        Node *nodeGeometry = nullptr;           // На этом узле хранится геометрия

        static int createdObjects;              // Столько объектов уже создано
    };


    class GameObjectController : public Controller
    {
        friend class GameObject;

    public:
    
        virtual ~GameObjectController() {};
    
        virtual void Preprocess() override;

        virtual void Move(float dT);
        virtual void Move() override {};
    
    protected:
    
        GameObjectController(GameObject *);

        GameObject * const gameObject = nullptr;
    
    private:

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
