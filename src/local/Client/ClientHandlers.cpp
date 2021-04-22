// 2021/04/06 22:47:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Client.h"
#include "Network/Other/ConnectorTCP_v.h"


void Client::HandlerUpdate(StringHash, VariantMap &)
{
    TheMaster.Update();
}

void Client::HandlerPostRenderUpdate(StringHash, VariantMap &)
{

}
