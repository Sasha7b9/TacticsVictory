#pragma once

#define LOG(format, ...) Urho3D::Log::Write(Urho3D::LOG_INFO, Urho3D::ToString(format, ##__VA_ARGS__));

class Log
{
public:
private:
};
