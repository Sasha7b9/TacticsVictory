// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Logic/Mutator_.h"


class Label : public Text
{
    URHO3D_OBJECT(Label, Text);
    
public:
    Label(Context *context = TheContext);
    static void RegisterObject();

    static SharedPtr<Label> Create(pchar text, int sizeFont = 20, int width = -1, int height = -1,
        bool auto_translate = true);

    void SetText(pchar text);

    void SetMutator(Mutator *_mutator) { mutator = _mutator; }

    virtual void Update(float dT) override;

    Mutator *GetMutator() { return mutator; }
    
private:
    String text;

    void HandlerChangeLanguage(StringHash, VariantMap&);

    SharedPtr<Mutator> mutator;
};
