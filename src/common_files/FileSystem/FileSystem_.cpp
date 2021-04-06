// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/FileSystem_.h"
#include "Utils/Log_.h"
#include "Utils/StringUtils_.h"
#include "Utils/SystemUtils_.h"

#ifdef WIN32
#pragma warning(push, 0)
#include <shlobj_core.h>
#pragma warning(pop)
#endif


#ifdef WIN32

char FS::delimiter = '\\';

#else

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char FS::delimiter = '/';

#endif


uint FS::File::CalculateCheckSum(size_t size)
{
    uint checksum = 0;

    static const int sizeBuffer = 512 * 1024;

    char buffer[sizeBuffer] = { 0 };

    while (size > 0)
    {
        size_t readBytes = (size >= sizeBuffer) ? sizeBuffer : size;
        size -= readBytes;

        Read(buffer, readBytes);

        for (size_t i = 0; i < readBytes; i++)
        {
            checksum = (uint8)buffer[i] + (checksum << 6U) + (checksum << 16U) - checksum;
        }
    }

    return checksum;
}


void FS::RemoveFile(const std::string &nameFile)
{
#ifdef WIN32

    if (DeleteFileA(nameFile.c_str()) == 0)
    {
        DWORD error = GetLastError();
        if (error != 2 &&               // Не удаётся найти указанный файл
            error != 3)                 // Системе не удается найти указанный путь
        {
            LOGERRORF("Can't remove file %s", nameFile.c_str());

            DISPLAY_LAST_ERROR();
        }
    };

#else

    if (remove(nameFile.c_str()) != 0)
    {
        if (errno != 2)                 // Файл не существует
        {
            LOGERROR("Can't remove file %s", nameFile.c_str());

            DISPLAY_LAST_ERROR();
        }
    }

#endif
}


bool FS::File::Open(pchar _name, pchar file, int line, ModeAccess::E mode)
{
    name = _name;

#ifdef WIN32

    DWORD access = 0;

    if (mode & ModeAccess::Read) //-V2006
    {
        access |= GENERIC_READ; //-V2523
    }
    if (mode & ModeAccess::Write) //-V2006
    {
        access |= GENERIC_WRITE;
    }

    handle = CreateFileA(_name, access, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (handle == INVALID_HANDLE_VALUE)
    {
        LOGERRORF("Can't open file \"%s\" from %s : %d", name.c_str(), file, line);

        DISPLAY_LAST_ERROR();

        handle = nullptr;

        return false;
    }

    return true;

#else

    uint access = 0;

    if (mode == ModeAccess::Read)       { access = O_RDONLY; } 
    else if (mode == ModeAccess::Write) { access = O_RDWR; }
    else                                { access = O_RDWR;   }

    fileDesc = open(_name, access, 0);

    if (fileDesc == -1)
    {
        LOGERROR("Can't open file \"%s\"", name.c_str());

        DISPLAY_LAST_ERROR();

        fileDesc = -1;

        return false;
    }

    return true;

#endif
}


bool FS::File::Create(pchar _name, ModeAccess::E mode)
{
    name = _name;

    FS::RemoveFile(_name);

#ifdef WIN32

    DWORD access = 0;

    if (mode & ModeAccess::Read) //-V2006
    {
        access |= GENERIC_READ; //-V2523
    }
    if (mode & ModeAccess::Write) //-V2006
    {
        access |= GENERIC_WRITE;
    }

    handle = CreateFileA(_name, access, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (GetLastError() == 3)            // Системе не удаётся найти указанный путь
    {
        std::string fullName(_name);

        size_t pos = fullName.rfind(FS::delimiter);

        if (pos != std::string::npos)
        {
            std::string path = fullName.substr(0, pos);

            FS::CreateDirectory(path);

            handle = CreateFileA(_name, access, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        }
    }

    if (handle == INVALID_HANDLE_VALUE)
    {
        LOGERRORF("Can't create file \"%s\"", name.c_str());

        DISPLAY_LAST_ERROR();

        handle = nullptr;

        return false;
    }

    return true;

#else

    uint access = 0;

    if (mode == ModeAccess::Read) { access = O_RDONLY; }
    else if (mode == ModeAccess::Write) { access = O_WRONLY; }
    else { access = O_RDWR; }

    fileDesc = open(_name, access | O_CREAT, S_IWRITE | S_IREAD);

    if (fileDesc < 0)
    {
        LOGERROR("Can't open file \"%s\"", name);

        DISPLAY_LAST_ERROR();

        fileDesc = -1;

        return false;
    }

    return true;

#endif
}


void FS::File::Write(const void *buffer, int numBytes)
{
#ifdef WIN32

    DWORD counter = 0;

    if (WriteFile(handle, buffer, (DWORD)numBytes, &counter, NULL) == 0)
    {
        LOGERRORF("Can't write to file %s", name.c_str());

        DISPLAY_LAST_ERROR();
    }

#else

    if (write(fileDesc, buffer, numBytes) != numBytes)
    {
        LOGERROR("Can't write to file %s", name.c_str());

        DISPLAY_LAST_ERROR();
    }

#endif
}


void FS::File::Read(std::string &string, size_t size)
{
    string.resize(size);

    Read(&string[0], size);
}



void FS::File::Read(void *buffer, size_t numBytes)
{
#ifdef WIN32

    DWORD counter = 0;

    if (ReadFile(handle, buffer, (DWORD)numBytes, &counter, NULL) == 0)
    {
        LOGERRORF("Can't read from file %s %llu bytes", name.c_str(), numBytes);

        DISPLAY_LAST_ERROR();
    }

#else

    if (read(fileDesc, buffer, numBytes) != (ssize_t)numBytes)
    {
        LOGERROR("Can't read from file %s %d bytes", name.c_str(), numBytes);

        DISPLAY_LAST_ERROR();
    }

#endif
}


bool FS::File::ReadString(std::string &string)
{
    string.clear();

#ifdef WIN32

    DWORD counter = 0;

    bool Ox0D = false;
    bool Ox0A = false;

    do 
    {
        char symbol = 0;
        ReadFile(handle, &symbol, 1, &counter, NULL);

        if (counter != 0)
        {
            string.append(&symbol, 1);
        }

        if (symbol == 0x0D) { Ox0D = true; }
        if (symbol == 0x0A) { Ox0A = true; }

    } while (counter == 1 && (!Ox0D || !Ox0A));

    return Ox0D && Ox0A;

#else

    return false;

#endif
}


void FS::CreateDirectory(std::string &path)
{
#ifdef WIN32

#define CP_UTF8                   65001       // UTF-8 translation

    char buffer[1024];

    GetCurrentDirectoryA(1024, buffer);

    std::string full(buffer);

    full.append("\\");
    full += path;

    int size = MultiByteToWideChar(CP_UTF8, 0, &full[0], (int)full.size(), NULL, 0);
    std::wstring wpath((uint64)size, 0);
    MultiByteToWideChar(CP_UTF8, 0, &full[0], (int)full.size(), &wpath[0], size);

    if (SHCreateDirectory(NULL, wpath.c_str()) != 0)
    {
        LOGERRORF("Can't create directory %s", full.c_str());

        DISPLAY_LAST_ERROR();
    }

#else

    

#endif
}


namespace FS
{
    File &operator<< (File &out, const char *buffer)
    {
        out.Write(buffer, SU::Length(buffer));

        return out;
    }

    File &operator<< (File &out, uint64 value)
    {
        char buffer[30];
        sprintf_s(buffer, 30, "%llu", value);
        out.Write(buffer, SU::Length(buffer));
        return out;
    }
}


size_t FS::File::Size()
{
#ifdef WIN32

#define INVALID_FILE_SIZE ((DWORD)0xFFFFFFFF)

    DWORD hiSize = 0;

    DWORD result = GetFileSize(handle, &hiSize); //-V2001

    if (result == INVALID_FILE_SIZE) //-V2523
    {
        DISPLAY_LAST_ERROR();

        return 0;
    }

    return (size_t)result;

#else

    long pos = lseek(fileDesc, 0L, SEEK_SET);

    long size = lseek(fileDesc, 0L, SEEK_END);

    lseek(fileDesc, pos, SEEK_SET);

    return size;

#endif
}


void FS::File::Close()
{
#ifdef WIN32

    if (handle != nullptr)
    {
        CloseHandle(handle);
        handle = nullptr;
    }

#else

    if (fileDesc != -1)
    {
        close(fileDesc);
        fileDesc = -1;
    }

#endif
}


bool FS::File::IsOpened()
{
#ifdef WIN32

    return (handle != nullptr);

#else

    return (fileDesc != -1);

#endif
}

