// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Mutator;


class Label : public Text
{
    URHO3D_OBJECT(Label, Text);
    
public:
    Label(Context *context = TheContext, Mutator *mutator = nullptr);
    static void RegisterObject();

    static SharedPtr<Label> Create(pchar text, bool center = true, int sizeFont = 20, int width = -1, int height = -1,
        bool auto_translate = true);

    void SetText(pchar text);

    virtual void Update(float dT) override;
    
private:
    String text;

    void HandleChangeLanguage(StringHash, VariantMap&);

    SharedPtr<Mutator> mutator;
};
