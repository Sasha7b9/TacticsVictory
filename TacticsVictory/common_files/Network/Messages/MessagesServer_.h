// 2021/12/21 17:52:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Messages/MessagesTypes_.h"
#include "Objects/GameObjectTypes_.h"


namespace Pi
{
    class GameObject;
    class AirUnitObject;
    class GroundUnitObject;
    class WaterUnitObject;
    class UnitObject;


    class MessageCreateLandscape : public Message
    {
    public:
        MessageCreateLandscape(pchar name_file);
        MessageCreateLandscape() : Message(PiTypeMessage::CreateLandscape) {}
    private:
        String<> name_file;

        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *) const override;
    };


    class MessageCreateGameObject : public Message
    {
    public:
        MessageCreateGameObject(GameObject *object = nullptr) :
            Message(PiTypeMessage::CreateGameObject, PiFlagMessage::Unordered | PiFlagMessage::Unreliable)
        {
#ifdef PiSERVER
            if(object) AppendObject(object);
#endif
        };

        void AppendObject(GameObject *);

    private:

        struct StateObject
        {
            int      id;
            int      type[3];     // [0] - TypeGameObject
                                  // [1] - TypeUnit, TypeStructure, TypeWeapon, TypeAmmo
                                  // [2] - TypeAirUnit, TypeGroundUnit, TypeWaterUnit
            Point3D  position;
            Vector3D direction;
            Vector3D up;
        };

        int num_objects = 0;

        static const int MAX_NUM_OBJECTS = (kMaxMessageSize - sizeof(num_objects)) / sizeof(StateObject);

        StateObject states[MAX_NUM_OBJECTS];

        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *sender) const override;

        void FillUnit(UnitObject *);
    };


    class MessageGameObjectState : public Message
    {
    public:
        MessageGameObjectState() : //-V730
            Message(PiTypeMessage::SendGameObjectState, PiFlagMessage::Unordered | PiFlagMessage::Unreliable) {}

        void AddObject(GameObject *);
        bool Full() const  { return num_objects == MAX_NUM_OBJECTS; }
        void Clear()       { num_objects = 0; }
        bool Empty() const { return num_objects == 0; }

    private:

        struct StateObject
        {
            int      id;
            Point3D  position;
            Vector3D direction;
            Vector3D up;
        };

        int num_objects = 0;

        static const int MAX_NUM_OBJECTS = (kMaxMessageSize - sizeof(num_objects)) / sizeof(StateObject);

        StateObject states[MAX_NUM_OBJECTS];

        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *) const override;
    };
}
