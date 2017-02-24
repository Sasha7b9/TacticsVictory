#pragma once


class Settings
{
public:
    bool Load();
    int GetInt(char *elem, char *name);
    int GetInt(char *name);
    float GetFloat(char *elem, char *name);
    void SetInt(char *elem, char *name, int value);
    void SetInt(char *name, int value);
    void SetFloat(char *elem, char *name, float value);

    void Save();

private:
    bool GetIntFromChild(char *child, char *name, int *value);
    bool GetFloatFromChild(char *child, char *name, float *value);
    bool GetIntFromChild(char *name, int *value);

    String nameFile;
    SharedPtr<XMLFile> file;
    XMLElement root;
    
public:
    struct IntKey
    {
        IntKey()
        {};
        IntKey(char *child, char *elem = "val")
        {
            str = String(child) + String(elem);
        };
        String str;
        uint ToHash() const
        {
            return str.ToHash();
        }
    };

    struct FloatKey
    {
        FloatKey()
        {
        };
        FloatKey(char *child, char *elem)
        {
            str = String(child) + String(elem);
        }
        String str;
        uint ToHash() const
        {
            return str.ToHash();
        }
    };

private:
    HashMap<IntKey, int> mapIntChild;
    HashMap<FloatKey, float> mapFloatChild;
};


struct SET
{
    struct WINDOW
    {
        static const int WIDTH = 1600;
        static const int HEIGHT = 1000;
        static const IntVector2 SIZE;
    };

    struct PANEL
    {
        static const float SPEED;
        struct BOTTOM
        {
            static const int WIDTH = SET::WINDOW::WIDTH;
            static const int HEIGHT = 20;
            static const IntVector2 SIZE;

            struct BUTTON
            {
                static const int WIDTH = 80;
                static const int HEIGHT = 15;
            };
        };

        struct MAP
        {
            static const int WIDTH = 200;
            static const int HEIGHT = WIDTH;
            static const IntVector2 SIZE;
        };

        struct MAIN
        {
            static const int HEIGHT = MAP::HEIGHT;
            static const int WIDTH = BOTTOM::WIDTH - MAP::WIDTH + 1;
            static const IntVector2 SIZE;
        };
    };

    struct MENU
    {
        struct ELEM
        {
            struct WINDOW
            {
                static const char *STYLE;
            };
        };

        struct SLIDER
        {
            static const int WIDTH = 200;
            static const int HEIGHT = 16;
            static const IntVector2 SIZE;
        };

        struct DDLIST
        {
            static const int WIDTH = 200;
            static const int HEIGHT = 18;
            static const IntVector2 SIZE;
        };

        struct TEXT
        {
            static const int WIDTH = 180;
            static const int HEIGHT = 10;
            static const IntVector2 SIZE;
        };

        struct GOVERNOR
        {
            struct CELL
            {
                static const int WIDTH = 10;
                static const int HEIGHT = 13;
                static const IntVector2 SIZE;
            };
        };

        struct FONT
        {
            static const char* NAME;

            struct SIZE
            {
                static const int TITLE = 20;
                static const int ITEM = 16;
            };
        };
    };
};
