// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/Units/Ground/GroundUnit_.h"
#include "Objects/Staff/Commander_.h"


namespace Pi
{
    class TankController;


    class Tank : public GroundUnitObject, public MapElement<Tank>
    {
    public:

        static Tank *Create(int id = -1);

        static Map<Tank> objects;

    private:

        Tank(int id = -1);
        virtual ~Tank() {};

        static const GameObjectParameters parameters;

        Node *CreateBody();
        Node *CreateTrack(bool left);
        Node *CreateTower();
        Node *CreateBarrel();
    };


    class CommanderTank : public Commander
    {
        friend class Commander;

    public:

        virtual ~CommanderTank() {}

    protected:

        CommanderTank(GameObject *);
    };
}
