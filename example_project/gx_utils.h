#ifndef __GX_UTILS_HEADER__
#define __GX_UTILS_HEADER__

#include <string>
#include <vector>
#include <ctime>
#include "cJSON.h"

struct GXDateTime
{
    GXDateTime();
    GXDateTime(const std::string& _str);
    void Set(const std::string& _str);

    std::string str;
    time_t value;
};

inline bool ReadFrom(cJSON* node, const char* name, bool& value)
{
    if (NULL == node)
    {
        return false;
    }

    if (strcmp(node->string, name) != 0)
    {
        return false;
    }

    if (cJSON_IsTrue(node)) {
        value = true;
    } else {
        value = false;
    }

    return true;
}

inline bool WriteTo(cJSON* node, const char* name, bool value)
{
	cJSON* item = value ? cJSON_CreateTrue() : cJSON_CreateFalse();
	if (item == NULL)
	{
		return false;
	}

	cJSON_AddItemToObject(node, name, item);
    return true;
}

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

inline bool WriteTo(cJSON* node, const char* name, int value)
{
	cJSON* item = cJSON_CreateNumber(value);
	if (item == NULL)
	{
		return false;
	}

	cJSON_AddItemToObject(node, name, item);
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

inline bool WriteTo(cJSON* node, const char* name, const std::string& value)
{
	cJSON* item = cJSON_CreateString(value.c_str());
	if (item == NULL)
	{
		return false;
	}

	cJSON_AddItemToObject(node, name, item);
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

inline bool ReadFrom(cJSON* node, const char* name, GXDateTime& value)
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

inline bool WriteTo(cJSON* node, const char* name, const GXDateTime& value)
{
	cJSON* item = cJSON_CreateString(value.str.c_str());
	if (item == NULL)
	{
		return false;
	}

	cJSON_AddItemToObject(node, name, item);
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

    value.LoadFrom(node);
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
        t.LoadFrom(c);
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

    for (typename std::vector<T>::const_iterator itr = value.begin();
        itr != value.end(); itr++)
    {
        cJSON* obj = itr->CreatecJSON();
        if (NULL != obj)
        {
            cJSON_AddItemToArray(item, obj);
        }
    }
    cJSON_AddItemToObject(node, name, item);
    return true;
}

#endif
