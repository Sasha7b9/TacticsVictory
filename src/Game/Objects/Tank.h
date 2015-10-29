#pragma once


#include "MovingObject.h"


class lTank : public lMovingObject
{
public:
    enum Type
    {
        Small,
        T_34_76
    };

    lTank(Type type);

    void Load();
    void Normalize();

private:
    lTank& operator=(const lTank&) {};

private:
    struct TankStruct
    {
        TankStruct(Type type_ = Small, char* fileName_ = 0) : type(type_), fileName(fileName_) {};
        Type type;
        char *fileName;
    };

public:
    struct Key
    {
        Key(Type type_ = Small) : type(type_) {};
        Type type;

        unsigned ToHash() const { return (uint)type; };

        bool operator==(const Key& rhs) const
        {
            return type == rhs.type;
        }
    };

    Type type;

    static HashMap<Key, TankStruct> parameters;
};
