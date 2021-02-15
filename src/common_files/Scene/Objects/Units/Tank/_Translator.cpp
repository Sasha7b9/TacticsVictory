/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#include "stdafx.h"
#include "Translator.h"
#include "Core/Math.h"
#include "Game/Objects/Units/Tank/Tank.h"



Translator::Translator(Context *context) : Object(context)
{
    // First number - delta row, second number - delta col
    angles["-1,-1"] = 315.0f;
    angles["-1,0"] = 0.0f;
    angles["-1,1"] = 45.0f;
    angles["0,1"] = 90.0f;
    angles["1,1"] = 135.0f;
    angles["1,0"] = 180.0f;
    angles["1,-1"] = 225.0f;
    angles["0,-1"] = 270.0f;
}


void Translator::RegisterInAS()
{
    asIScriptEngine *engine = TheScript->GetScriptEngine();
    engine->RegisterObjectType("Translator", 0, asOBJ_REF);
#pragma warning(push)
#pragma warning(disable:4191)
    engine->RegisterObjectMethod("Translator", "bool IsMoving()", asMETHOD(Translator, IsMoving), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Translator", asBEHAVE_ADDREF, "void AddRef()", asMETHOD(Translator, AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("Translator", asBEHAVE_RELEASE, "void ReleaseRef()", asMETHOD(Translator, ReleaseRef), asCALL_THISCALL);
#pragma warning(pop)
}


void Translator::Init(Tank* tank_)
{
    tank = tank_;
}


void Translator::SetPath(const PODVector<Coord> &path_, float speed_)
{
    path = path_;

    absSpeed = speed_;

    if(this->path.Size() > 1)
    {
        SetStep(path[0], path[1]);
        this->path.Erase(0, 1);
    }
    else if(path.Size() == 1)
    {
        this->speed = Vector3::ZERO;
        currentPos = path[0].ToVector3();
        tank->SetPosition(currentPos);
    }
}


Vector3 Translator::Update(float dT)
{
    if(state == Stop)
    {
        return currentPos;
    }

    if(state == Rotate)
    {
        float delta = speedRotate * dT;
        absAngle -= fabs(delta);
        currentAngle += delta;
        if(currentAngle < 0.0f)
        {
            currentAngle += 360.0f;
        }
        else if(currentAngle >= 360.0f)
        {
            currentAngle -= 360.0f;
        }
        if(absAngle <= 0.0f)
        {
            currentAngle = endAngle;
            state = Move;
        }
        tank->SetRotation(currentAngle);
    }
    else if(state == Move)
    {
        currentPos += dT * speed;
        distance -= dT * absSpeed;

        if(distance < 0.0f)
        {
            currentPos = end;

            if(path.Size() > 1)
            {
                SetStep(path[0], path[1]);
                path.Erase(0, 1);
            }
            else
            {
                state = Stop;
            }
        }
    }

    return currentPos;
}


void Translator::SetStep(const Coord &start, const Coord &end_)
{
    end = end_.ToVector3();

    currentPos = start.ToVector3();

    distance = (this->end - currentPos).Length();

    speed = (this->end - currentPos) / distance * absSpeed;

    String hash = String((int)end_.row - (int)start.row) + String(",") + String((int)end_.col - (int)start.col);


    float angleNeed = angles[hash].GetFloat();
    float angle = tank->GetRotation();

    if(fabs(angleNeed - angle) > M_EPSILON)
    {
        StartRotation(angleNeed);
    }
    else
    {
        state = Move;
    }
}


void Translator::StartRotation(float angleNeed)
{
    float curAngle = tank->GetRotation();

    endAngle = angleNeed;

    if(angleNeed > curAngle)
    {
        float delta = angleNeed - curAngle;
        if(delta < 180.0f)
        {
            speedRotate = fabs(speedRotate);
            absAngle = delta;
        }
        else
        {
            speedRotate = -fabs(speedRotate);
            absAngle = 360.0f - delta;
        }
    }
    else
    {
        float delta = curAngle - angleNeed;
        if(delta > 180.0f)
        {
            speedRotate = fabs(speedRotate);
            absAngle = 360.0f - delta;
        }
        else
        {
            speedRotate = -fabs(speedRotate);
            absAngle = delta;
        }
    }

    state = Rotate;
}


bool Translator::IsMoving()
{
    return state != Stop;
}
