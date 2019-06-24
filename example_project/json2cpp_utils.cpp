#include "json2cpp_utils.h"
#include <cstdio>
#include <cstring>

GXDateTime::GXDateTime()
    : value(0)
{}

time_t str2time(const std::string& str)
{
    if (str.empty())
        return 0;

    tm timeinfo;
	memset(&timeinfo, 0, sizeof(timeinfo));
    sscanf(str.c_str(), "%d-%d-%d %d:%d:%d",
        &timeinfo.tm_year,
        &timeinfo.tm_mon,
        &timeinfo.tm_mday,
        &timeinfo.tm_hour,
        &timeinfo.tm_min,
        &timeinfo.tm_sec);
    timeinfo.tm_year -= 1900;
    timeinfo.tm_mon -= 1;
    return mktime(&timeinfo);
}

GXDateTime::GXDateTime(const std::string& _str)
{
    str = _str;
    value = str2time(str);
}

void GXDateTime::Set(const std::string& _str)
{
    str = _str;
    value = str2time(str);    
}

bool LoadFrom(bool& value, cJSON* node)
{
    if (cJSON_IsTrue(node)) {
        value = true;
    } else {
        value = false;
    }
    return true;
}

cJSON* CreatecJSON(bool value)
{
    return value ? cJSON_CreateTrue() : cJSON_CreateFalse();    
}

bool LoadFrom(int& value, cJSON* node)
{
    value = static_cast<int>(node->valueint);
    return true;
}

cJSON* CreatecJSON(int value)
{
    return cJSON_CreateNumber(value);
}

bool LoadFrom(std::string& value, cJSON* node)
{
    value = node->valuestring;
    return true;
}

cJSON* CreatecJSON(const std::string& value)
{
    return cJSON_CreateString(value.c_str());
}

bool LoadFrom(double& value, cJSON* node)
{
    value = node->valuedouble;
    return true;
}

cJSON* CreatecJSON(double value)
{
    return cJSON_CreateNumber(value);
}

bool LoadFrom(GXDateTime& value, cJSON* node)
{
    if (node->type != cJSON_String)
    {
        return false;
    }
    value.Set(node->valuestring);
    return true;
}

cJSON* CreatecJSON(const GXDateTime& value)
{
    return cJSON_CreateString(value.str.c_str());
}
