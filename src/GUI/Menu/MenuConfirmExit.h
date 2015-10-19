#pragma once


class tvMenuConfirmExit : public tvWindow
{
    OBJECT(tvMenuConfirmExit);

public:
    tvMenuConfirmExit(Context *context);

    static void RegisterObject(Context *context);

private:
    tvMenuConfirmExit& operator=(const tvMenuConfirmExit&)
    {};
};