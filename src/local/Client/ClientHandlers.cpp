// 2021/04/06 22:47:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Client.h"


void Client::HandleUpdate(StringHash, VariantMap &)
{
    if (TheMasterServer.IsConnected())
    {
        TheGUI->AppendInfo("Connection to master server established");
    }
    else
    {
        if (TheMasterServer.GetAddress()[0])
        {
            TheGUI->AppendWarning("Can't connect to master server");

            TheMasterServer.Connect();
        }
    }
}

void Client::HandlePostRenderUpdate(StringHash, VariantMap &)
{

}
