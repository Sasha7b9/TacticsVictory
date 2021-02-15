#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class VectorBufferRTS : public VectorBuffer
{
public:
    VectorBufferRTS();
    VectorBufferRTS(int);
    VectorBufferRTS(float);
    void WriteTank(Tank *tank);
    void ReadTank(uint *id, Vector3 *position, Quaternion *rotation);

private:
};

