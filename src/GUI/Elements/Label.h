#pragma once


class Label : public Urho3D::Text
{
    OBJECT(Label);
public:
    Label(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);
    static SharedPtr<Label> Create(char *text, int sizeFont = 20, int width = -1, int height = -1, Urho3D::HorizontalAlignment ha = Urho3D::HA_LEFT, Urho3D::VerticalAlignment va = Urho3D::VA_TOP);
    void SetText(char *text);
    
private:
    Label& operator=(const Label&)
    {};

    void HandleChangeLanguage(StringHash, VariantMap&);
    char *text = 0;
};