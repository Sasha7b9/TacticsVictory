#pragma once


namespace FS
{
    extern char delimiter;

    void RemoveFile(const std::string &nameFile);

    void CreateDirectory(std::string &path);

    class File
    {
    public:

        struct ModeAccess
        {
            enum E
            {
                Read    = 1 << 0,
                Write   = 1 << 1
            };
        };

        ~File() { Close(); };

        // Открывает существующий файл
        bool Open(pchar name, pchar file, int line, ModeAccess::E mode = (ModeAccess::E)(ModeAccess::Read | ModeAccess::Write));

        // Создаёт новый файл. Если файл с таким именем уже существует, стирает его содержимое
        bool Create(pchar name, ModeAccess::E mode = (ModeAccess::E)(ModeAccess::Read | ModeAccess::Write));

        uint CalculateCheckSum(size_t size);

        void Write(const void *buffer, int size);

        void Read(void *buffer, size_t size);

        void Read(std::string &string, size_t size);

        bool ReadString(std::string &string);

        size_t Size();

        void Close();

        bool IsOpened();

        friend File &operator<< (File &out, const char *);
        friend File &operator<< (File &out, uint64);

    private:

        std::string name;

#ifdef WIN32
        HANDLE handle = nullptr; //-V122
#else
        int fileDesc = -1;
#endif
    };
}
