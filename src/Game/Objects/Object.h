#pragma once


class lObject : public Object
{
    OBJECT(lObject);

public:
    lObject();

    void SetPosition(const Vector3& pos);

protected:
    SharedPtr<Node> modelNode;
    SharedPtr<StaticModel> modelObject;
    Vector3 deltaPos;

private:
    lObject& operator=(const lObject&) {};

};
