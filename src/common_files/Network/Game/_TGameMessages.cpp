// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


namespace Message
{
    void Message::Handle(VariantMap &map)
    {
        TConnection connection((Connection *)map[NetworkMessage::P_CONNECTION].GetPtr());

        MemoryBuffer msg(map[NetworkMessage::P_DATA].GetBuffer());

        if (id == MSG_TEXTSTRING)
        {
            ((TextString *)this)->Handle(msg);

        }

#ifdef CLIENT

        else if (id == MSG_BUILD_SCENE)
        {
            ((BuildScene *)this)->Handle(msg);
        }
        else if (id == MSG_SEND_OBJECT_STATE)
        {
            ((SendObjectState *)this)->Handle(msg);
        }

#elif defined SERVER

        else if (id == MSG_REQUEST_FOR_BUILD_SCENE)
        {
            ((RequestForBuildScene *)this)->Handle(connection);
        }
        else if (id == MSG_KEY_EVENT)
        {
            ((KeyEvent *)this)->Handle(msg);
        }

#endif
    }

}
