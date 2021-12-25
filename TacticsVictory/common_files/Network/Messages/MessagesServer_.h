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

        static const int MAX_NUM_OBJECTS = 3;
        void AppendObject(GameObject *);
        int NumObjects() const { return num_objects; }
        void Clear() { num_objects = 0; }

    private:

        int num_objects = 0;
        int id[MAX_NUM_OBJECTS];
        int type[MAX_NUM_OBJECTS][3];   // [0] - TypeGameObject
                                        // [1] - TypeUnit, TypeStructure, TypeWeapon, TypeAmmo
                                        // [2] - TypeAirUnit, TypeGroundUnit, TypeWaterUnit
        Transform4D transform[MAX_NUM_OBJECTS];

        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *sender) const override;

        void FillUnit(UnitObject *);
    };


    class MessageGameObjectState : public Message
    {
    public:
        MessageGameObjectState() :
            Message(PiTypeMessage::SendGameObjectState, PiFlagMessage::Unordered | PiFlagMessage::Unreliable) {}

        void AddObject(GameObject *);
        int  NumObjects() const { return num_objects; }
        int  MaxNumObjects() const { return MAX_OBJECTS; }
        void ResetCounter() { num_objects = 0; }

    private:

        static const int MAX_OBJECTS = 10;

        int      num_objects = 0;
        int      id[MAX_OBJECTS];
        Point3D  position[MAX_OBJECTS];
        Vector3D direction[MAX_OBJECTS];
        Vector3D up[MAX_OBJECTS];

        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *) const override;
    };
}
