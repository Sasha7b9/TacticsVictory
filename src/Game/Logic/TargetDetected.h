#pragma once


class TargetDetected : public Component
{
    OBJECT(TargetDetected);

public:
    TargetDetected(Context* context = gContext);

protected:
    virtual void OnNodeSet(Node *node);

private:
    void HandleNodeCollision(StringHash, VariantMap&);

    TargetDetected& operator=(const TargetDetected&)
    {};
};