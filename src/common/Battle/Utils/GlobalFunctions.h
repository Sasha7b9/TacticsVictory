// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace GF
{
    String IntToString(int value, uint length);
    bool GetAddressPort(const Vector<String> &words, String &address, uint16 &port);  // Возвращает в address aдрес, если в векторе есть строка вида
                                                               // "-address:xxxx", в port - адрес порта, если в векторе есть строка вида "-port:xx"
}
