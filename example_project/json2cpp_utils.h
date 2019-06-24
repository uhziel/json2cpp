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

bool LoadFrom(bool& value, cJSON* node);
cJSON* CreatecJSON(bool value);

bool LoadFrom(int& value, cJSON* node);
cJSON* CreatecJSON(int value);

bool LoadFrom(std::string& value, cJSON* node);
cJSON* CreatecJSON(const std::string& value);

bool LoadFrom(double& value, cJSON* node);
cJSON* CreatecJSON(double value);

bool LoadFrom(GXDateTime& value, cJSON* node);
cJSON* CreatecJSON(const GXDateTime& value);

template <typename T>
inline bool LoadFrom(std::vector<T>& value, cJSON* node)
{
    for (cJSON* c = node->child; c != NULL; c = c->next)
    {
        T t;
        if (LoadFrom(t, c))
        {
            value.push_back(t);
        }
    }
    return true;
}
template <typename T>
inline cJSON* CreatecJSON(const std::vector<T>& value)
{
    cJSON* array = cJSON_CreateArray();
    if (NULL == array)
    {
        return NULL;
    }

    for (typename std::vector<T>::const_iterator itr = value.begin();
        itr != value.end(); itr++)
    {
        cJSON* item = CreatecJSON(*itr);
        if (NULL != item)
        {
            cJSON_AddItemToArray(array, item);
        }
    }
    return array;
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

    return LoadFrom(value, node);
}

template <typename T>
inline bool WriteTo(cJSON* node, const char* name, const T& value)
{
    cJSON* item = CreatecJSON(value);
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
        if (LoadFrom(t, c))
        {
            value.push_back(t);
        }
    }
    return true;
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
        cJSON* obj = CreatecJSON(*itr);
        if (NULL != obj)
        {
            cJSON_AddItemToArray(item, obj);
        }
    }
    cJSON_AddItemToObject(node, name, item);
    return true;
}

#endif
