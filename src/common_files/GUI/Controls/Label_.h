// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Label : public Text
{
    URHO3D_OBJECT(Label, Text);
    
public:
    Label(Context *);
    static void RegisterObject();

    static SharedPtr<Label> Create(const String &text, bool center = true, int sizeFont = 20,
        int width = -1, int height = -1);

    void SetText(pchar text);
    
private:
    pchar text = nullptr;

    void HandleChangeLanguage(StringHash, VariantMap&);
};
