#pragma once


class tvPanelBottom : public tvWindow
{
    OBJECT(tvPanelBottom);

public:
    tvPanelBottom(Context *context);

    static void RegisterObject(Context *context);

private:
    tvPanelBottom& operator=(const tvPanelBottom&)
    {};
};