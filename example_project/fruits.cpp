#include "fruits.h"

Energy::Energy()
    : carbohydrates(22.84)
    , fat(0.33)
    , protein(1.09)
{}

bool LoadFrom(Energy& value, cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
		if (::ReadFrom(c, "carbohydrates", value.carbohydrates)) continue;
		if (::ReadFrom(c, "fat", value.fat)) continue;
		if (::ReadFrom(c, "protein", value.protein)) continue;
	}
	return true;
}

cJSON* CreatecJSON(const Energy& value)
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

	::WriteTo(object, "carbohydrates", value.carbohydrates);
	::WriteTo(object, "fat", value.fat);
	::WriteTo(object, "protein", value.protein);

	return object;
}

Fruit::Fruit()
    : name("香蕉")
    , price(10)
    , per_sale_time("2018-12-27 00:11:01")
{}

bool LoadFrom(Fruit& value, cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
		if (::ReadFrom(c, "name", value.name)) continue;
		if (::ReadFrom(c, "price", value.price)) continue;
		if (::ReadFrom(c, "per_sale_time", value.per_sale_time)) continue;
		if (::ReadFrom(c, "energy", value.energy)) continue;
	}
	return true;
}

cJSON* CreatecJSON(const Fruit& value)
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

	::WriteTo(object, "name", value.name);
	::WriteTo(object, "price", value.price);
	::WriteTo(object, "per_sale_time", value.per_sale_time);
	::WriteTo(object, "energy", value.energy);

	return object;
}

Demo::Demo()
    : demo_bool(true)
    , demo_int(0)
    , demo_double(0.1)
    , demo_str("")
    , demo_time("2018-12-27 00:11:01")
{}

bool LoadFrom(Demo& value, cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
		if (::ReadFrom(c, "demo_bool", value.demo_bool)) continue;
		if (::ReadFrom(c, "demo_int", value.demo_int)) continue;
		if (::ReadFrom(c, "demo_double", value.demo_double)) continue;
		if (::ReadFrom(c, "demo_str", value.demo_str)) continue;
		if (::ReadFrom(c, "demo_time", value.demo_time)) continue;
		if (::ReadFrom(c, "demo_array", value.demo_array)) continue;
	}
	return true;
}

cJSON* CreatecJSON(const Demo& value)
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

	::WriteTo(object, "demo_bool", value.demo_bool);
	::WriteTo(object, "demo_int", value.demo_int);
	::WriteTo(object, "demo_double", value.demo_double);
	::WriteTo(object, "demo_str", value.demo_str);
	::WriteTo(object, "demo_time", value.demo_time);
	::WriteTo(object, "demo_array", value.demo_array);

	return object;
}

Config::Config()
{}

bool LoadFrom(Config& value, cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
		if (::ReadFrom(c, "fruits", value.fruits)) continue;
		if (::ReadFrom(c, "demo", value.demo)) continue;
	}
	return true;
}

cJSON* CreatecJSON(const Config& value)
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

	::WriteTo(object, "fruits", value.fruits);
	::WriteTo(object, "demo", value.demo);

	return object;
}

void Config::Parse(const char* content)
{
	if (NULL == content)
	{
		return;
	}

	cJSON* root = cJSON_Parse(content);
	if (NULL == root)
	{
		return;
	}

	*this = Config();
	LoadFrom(*this, root);
	cJSON_Delete(root);
}

void Config::Print(std::string& out) const
{
	cJSON* root = CreatecJSON(*this);
	if (NULL == root)
	{
		return;
	}

	const char* text = cJSON_PrintUnformatted(root);
	if (NULL == text)
	{
		return;
	}
	out = text;
	free((void*)(text));
}
