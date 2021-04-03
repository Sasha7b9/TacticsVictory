// 2021/04/02 17:15:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#pragma warning(push, 0)

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

#define _WINSOCKAPI_
#include <windows.h>

#include <cstdarg>
#include <iostream>
#include <locale>
#include <mutex>
#include <vector>

#pragma warning(pop)

#include "defines.h"

#include "FileSystem/ConfigurationFile_.h"
#include "Utils/Log_.h"
