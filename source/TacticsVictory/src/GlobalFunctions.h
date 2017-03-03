#pragma once


#define CALL_IF_EXIST(object, function) if(object) (object)->function()


void SetWindowInCenterScreen(Window *window);
void OpenFileSelector(char *title, char *textOk, char *textCancel, Vector<String> &filters);
/// Return the file's last modified time. File path relative from TVData/
unsigned GetLastModifiedTime(char* name);
String GetNameFile(const char *name);

