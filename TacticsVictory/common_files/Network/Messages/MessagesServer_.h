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
        virtual bool HandleMessage(Player *sender) const override;
    };


    class MessageCreateGameObject : public Message
    {
    public:
        MessageCreateGameObject(GameObject *);
        MessageCreateGameObject() : Message(PiTypeMessage::CreateGameObject) {}
    private:
        int id = 0;
        TypeGameObject::S typeGameObject = TypeGameObject::Empty;
        TypeUnit          typeUnit       = TypeUnit::None_;
        TypeAirUnit::S    typeAirUnit    = TypeAirUnit::Empty;
        TypeGroundUnit::S typeGroundUnit = TypeGroundUnit::Empty;
        TypeWaterUnit::S  typeWaterUnit  = TypeWaterUnit::Empty;
        Transform4D transform;

        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *sender) const override;

        void FillUnit(UnitObject *);
        void FillAirUnit(AirUnitObject *);
        void FillGroundUnit(GroundUnitObject *);
        void FillWaterUnit(WaterUnitObject *);
    };


    class MessageGameObjectNodeTransform : public Message
    {
    public:
        MessageGameObjectNodeTransform(GameObject *);
        MessageGameObjectNodeTransform() : Message(PiTypeMessage::SendGameObjectNodeTransform) {}
    private:
        int id = 0;
        Transform4D transform;

        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *) const override;
    };
}
