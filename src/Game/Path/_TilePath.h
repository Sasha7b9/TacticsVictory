#pragma once


class lTilePath : public Object
{
    OBJECT(lTilePath);
public:
    lTilePath(bool create = true);
    ~lTilePath();

    void SetPosition(const Vector3 &pos);
    void SetVisible(bool visible);

    static void Add(Vector3 &pos);
    static void DisableAll();
    static void RemoveAll();

private:
    lTilePath& operator=(const lTilePath&)
    {};
    SharedPtr<Node> node;
};


class lThreadLoadPath : public Thread, public Object
{
    OBJECT(Object)

public:
    lThreadLoadPath(Vector3 pos, uint posInVector);

    virtual void ThreadFunction();

private:
    lThreadLoadPath& operator=(const lThreadLoadPath&)
    {};

    Vector3 pos;
    uint posInVector;
};
