#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CALL_MEMBER_IF_EXIST(object, function) if(object) (object)->function()


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetWindowInCenterScreen(Window *window);
void OpenFileSelector(char *title, char *textOk, char *textCancel, const Vector<String> &filters);
unsigned GetLastModifiedTime(char* name);                                   // Return the file's last modified time. File path relative from TVData
String GetNameFile(const char *name);
String IntToString(int value, uint length);
bool GetAddressPort(const Vector<String> &words, String &address, uint16 &port);  // Возвращает в address aдрес, если в векторе есть строка вида
                                                               // "-address:xxxx", в port - адрес порта, если в векторе есть строка вида "-port:xx"

