// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include <Resource/PiPacking.h>


namespace Pi
{

    enum
    {
        kMutatorMovement = 'move'
    };
    
    class MovementMutator final : public Mutator
    {
    
        friend class MutatorReg < MovementMutator > ;
    
    public:
        MovementMutator(Point2D posShow, Point2D posHide, Vector2D speed);
        ~MovementMutator();
    
        void SetParameters(Point2D posShow, Point2D posHide, Vector2D speed);
        void Toggle();
        void Preprocess() override;
    
        void Pack(Packer &data, PackFlag::E packFlags) const override;
        void Unpack(Unpacker &data, uint unpackFlags) override;
        bool UnpackChunk(const ChunkHeader *chunkHeader, Unpacker& data, uint unpackFlags);
    
        int GetSettingCount() const override;
        Setting *GetSetting(int index) const override;
        void SetSetting(const Setting *setting) override;
    
        void Move() override;
        void Reset() override;
    
    private:
        MovementMutator();
        MovementMutator(const MovementMutator& movementMutator);
    
        MovementMutator& operator=(const MovementMutator&) = delete;
    
        void SetCurrenPosition();
        void CalculateNewPosition(float k);
    
        Mutator *Replicate() const override;
    
        uint state = 0;
        Point2D positionShow = { 0.0F, 0.0F };
        Point2D positionHide = { 0.0F, 0.0F };
        Point2D positionCurrent = { 0.0F, 0.0F };
        Vector2D speed = { 0.0F, 0.0F };
    };

}
