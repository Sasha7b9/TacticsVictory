#pragma once


enum
{
    Hit_Missile
};


EVENT(E_HIT, AmmunitionEvent)
{
    PARAM(P_TYPE, AmmunitionEventType);
    PARAM(P_OBJECT, GameObject);
}
