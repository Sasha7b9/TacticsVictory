#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Label : public Text
{
    URHO3D_OBJECT(Label, Text);
    
public:
    Label(Context *context = gContext);
    static void RegisterObject(Context *context = gContext);
    static SharedPtr<Label> Create(char *text, int sizeFont = 20, int width = -1, int height = -1);
    void SetText(char *text);
    
private:
    char *text = 0;

    void HandleChangeLanguage(StringHash, VariantMap&);
};
