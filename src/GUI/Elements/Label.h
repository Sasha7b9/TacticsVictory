#pragma once


class tvLabel : public Text
{
    OBJECT(tvLabel);
public:
    tvLabel(Context *context);

    static void RegisterObject(Context *context);
    static SharedPtr<tvLabel> Create(char *text, int sizeFont, int width = -1, int height = -1);
    static void ReloadLanguage();
    
    void SetNewText(const char *text);

private:
    tvLabel& operator=(const tvLabel&)
    {};
};