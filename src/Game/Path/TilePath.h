#pragma once


class lTilePath : public Object
{
    OBJECT(lTilePath);
public:
    lTilePath();
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


class lThreadLoadPath : public Thread
{
public:
    virtual void ThreadFunction();
private:
};
