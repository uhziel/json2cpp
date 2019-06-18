#include "fruits.h"

Energy::Energy()
    : carbohydrates(22.84)
    , fat(0.33)
    , protein(1.09)
{}

void Energy::LoadFrom(cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
		if (::ReadFrom(c, "carbohydrates", carbohydrates)) continue;
		if (::ReadFrom(c, "fat", fat)) continue;
		if (::ReadFrom(c, "protein", protein)) continue;
	}
}

cJSON* Energy::CreatecJSON() const
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

	::WriteTo(object, "carbohydrates", carbohydrates);
	::WriteTo(object, "fat", fat);
	::WriteTo(object, "protein", protein);

	return object;
}

Fruit::Fruit()
    : name("香蕉")
    , price(10)
    , per_sale_time("2018-12-27 00:11:01")
{}

void Fruit::LoadFrom(cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
		if (::ReadFrom(c, "name", name)) continue;
		if (::ReadFrom(c, "price", price)) continue;
		if (::ReadFrom(c, "per_sale_time", per_sale_time)) continue;
		if (::ReadFrom(c, "energy", energy)) continue;
	}
}

cJSON* Fruit::CreatecJSON() const
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

	::WriteTo(object, "name", name);
	::WriteTo(object, "price", price);
	::WriteTo(object, "per_sale_time", per_sale_time);
	::WriteTo(object, "energy", energy);

	return object;
}

Config::Config()
{}

void Config::LoadFrom(cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
		if (::ReadFrom(c, "fruits", fruits)) continue;
	}
}

cJSON* Config::CreatecJSON() const
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

	::WriteTo(object, "fruits", fruits);

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
	LoadFrom(root);
	cJSON_Delete(root);
}

void Config::Print(std::string& out) const
{
	cJSON* root = CreatecJSON();
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