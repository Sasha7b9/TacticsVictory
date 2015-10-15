#pragma once


class tvScene : public Object
{
    OBJECT(tvScene)

public:
    tvScene();

    void Create();

private:
    tvScene& operator=(const tvScene&)
    {};
};