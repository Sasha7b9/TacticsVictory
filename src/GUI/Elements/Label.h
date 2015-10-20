#pragma once


class lLabel : public Text
{
    OBJECT(lLabel);
public:
    lLabel(Context *context);

    static void RegisterObject(Context *context);
    static SharedPtr<lLabel> Create(char *text, int sizeFont, int width = -1, int height = -1);
    static void ReloadLanguage();
    
    void SetNewText(const char *text);

private:
    lLabel& operator=(const lLabel&)
    {};
};