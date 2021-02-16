/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once


struct ObjectState
{
    virtual ~ObjectState() {};
    void Send() const;

    virtual void Compress(VectorBuffer &buffer) const = 0;
    virtual void Decompress(MemoryBuffer &buffer) = 0;
};
