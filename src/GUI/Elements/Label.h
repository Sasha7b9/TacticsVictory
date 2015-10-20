#pragma once


class vLabel : public Text
{
    OBJECT(vLabel);
public:
    vLabel(Context *context);

    static void RegisterObject(Context *context);
    static SharedPtr<vLabel> Create(char *text, int sizeFont, int width = -1, int height = -1);
    static void ReloadLanguage();
    
    void SetNewText(const char *text);

private:
    vLabel& operator=(const vLabel&)
    {};
};