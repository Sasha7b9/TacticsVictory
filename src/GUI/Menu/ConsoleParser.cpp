#include <stdafx.h>


void ConsoleParser::Execute(const String &string)
{
    Vector<String> words = string.Split(' ');

    uint size = words.Size();

    String word0 = size > 0 ? words[0] : "";
    String word1 = size > 1 ? words[1] : "";

    if(word0 == "exit")
    {
        gEngine->Exit();
    }
    else if(word0 == "vars")
    {
        if(size == 1)
        {
            gWindowVars->Toggle();
        }
        else if(size == 2)
        {
            if(word1 == "open")
            {
                gWindowVars->SetVisible(true);
            }
            else if(word1 == "close")
            {
                gWindowVars->SetVisible(false);
            }
        }
    }
}