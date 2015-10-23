#pragma once


class lLabel : public Text
{
    OBJECT(lLabel);
public:
    lLabel(Context *context = gContext);

    static void RegisterObject(Context *context);
    static SharedPtr<lLabel> Create(char *text, int sizeFont = 20, int width = -1, int height = -1);
    void SetText(char *text);
    
private:
    lLabel& operator=(const lLabel&)
    {};

    void HandleChangeLanguage(StringHash, VariantMap&);
    char *text = 0;
};