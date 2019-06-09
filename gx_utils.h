#ifndef __GX_UTILS_HEADER__
#define __GX_UTILS_HEADER__

#include "tinyxml/tinyxml.h"
#include <string>
#include <vector>
#include <ctime>

struct GXDateTime
{
    GXDateTime();
    GXDateTime(const std::string& _str);
    void Set(const std::string& _str);

    std::string str;
    time_t value;
};

inline bool ReadFrom(cJSON* node, const char* name, int& value)
{
    if (NULL == node)
    {
        return false;
    }

    if (strcmp(node->string, name) != 0)
    {
        return false;
    }

    value = static_cast<int>(node->valueint);
    return true;
}

inline bool ReadFrom(cJSON* node, const char* name, std::string& value)
{
    if (NULL == node)
    {
        return false;
    }

    if (strcmp(node->string, name) != 0)
    {
        return false;
    }

    value = node->valuestring;
    return true;
}

inline bool ReadFrom(cJSON* node, const char* name, double& value)
{
    if (NULL == node)
    {
        return false;
    }

    if (strcmp(node->string, name) != 0)
    {
        return false;
    }

    value = node->valuedouble;
    return true;
}

inline bool WriteTo(cJSON* node, const char* name, double value)
{
	cJSON* item = cJSON_CreateNumber(value);
	if (item == NULL)
	{
		return false;
	}

	cJSON_AddItemToObject(node, name, item);
    return true;
}

inline bool ReadFrom(cJSON* node, const char* name, const GXDateTime& value)
{
    if (NULL == node)
    {
        return false;
    }

    if (strcmp(node->string, name) != 0)
    {
        return false;
    }

    if (node->type != cJSON_String)
    {
        return false;
    }

    value.Set(node->valuestring);
    return true;
}

template <typename T>
inline bool ReadFrom(cJSON* node, const char* name, T& value)
{
    if (NULL == node)
    {
        return false;
    }

    if (strcmp(node->string, name) != 0)
    {
        return false;
    }

    value.Load(node);
    return true;
}

template <typename T>
inline bool WriteTo(cJSON* node, const char* name, const T& value)
{
    cJSON* item = value.CreatecJSON();
	if (item == NULL)
	{
		return false;
	}

	cJSON_AddItemToObject(node, name, item);
    return true;
}

template <typename T>
inline bool ReadFrom(cJSON* node, const char* name, std::vector<T>& value)
{
    if (NULL == node)
    {
        return false;
    }

    if (strcmp(node->string, name) != 0)
    {
        return false;
    }

    for (cJSON* c = node->child; c != NULL; c = c->next)
    {
        T t;
        t.Load(c);
        value.push_back(t);
    }
    return false;
}

template <typename T>
inline bool WriteTo(cJSON* node, const char* name, const std::vector<T>& value)
{
    if (NULL == node)
    {
        return false;
    }

    cJSON* item = cJSON_CreateArray();
    if (NULL == item)
    {
        return false;
    }

    for (std::vector<T>::const_iteator itr = value.begin();
        itr != value.end(); itr++)
    {
        cJSON* obj = itr->CreatecJSON();
        if (NULL != obj)
        {
            cJSON_AddItemToArray(item, obj);
        }
    }
    return true;
}

#endif
