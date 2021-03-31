// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// C++

#include <cstdarg>
#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>


// Third party

#ifdef WIN32
    #pragma warning(push, 0)
#endif 

    #undef Bool
    #include <rapidjson/document.h>
    #include <sockpp/tcp_acceptor.h>
    #include <sockpp/tcp_connector.h>

#ifdef WIN32
    #pragma warning(pop)
#endif


// Tankist

#include "defines.h"

#include "Master.h"

#include "FileSystem/ConfigurationFile_.h"
#include "FileSystem/FileSystem_.h"

#include "Network/Other/SocketsTCP_.h"

#include "Utils/Log_.h"
#include "Utils/StringUtils_.h"
#include "Utils/SystemFunctions_.h"
#include "Utils/SystemUtils_.h"

#include "globals.h"
