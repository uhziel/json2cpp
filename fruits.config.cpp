#include "fruits.config.h"

namespace GXFruits {

Energy::Energy()
    : carbohydrates(0)
    , fat(0)
    , protein(0)
{}

void Energy::Load(cJSON* node)
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
	::WirteTo(object, "protein", protein);

	return object;
}

Fruit::Fruit()
    : name("")
    , price(1)
    , per_sale_time("")
{}

void Fruit::Load(cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
		if (::ReadFrom(c, "energy", energy)) continue;
		if (::ReadFrom(c, "name", name)) continue;
		if (::ReadFrom(c, "price", price)) continue;
		if (::ReadFrom(c, "per_sale_time", per_sale_time)) continue;
	}
}

cJSON* Fruit::CreatecJSON() const
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

	::WriteTo(object, "energy", energy);
	::WriteTo(object, "name", name);
	::WriteTo(object, "price", price);
	::WriteTo(object, "per_sale_time", per_sale_time);

	return object;
}

Config::Config()
{}

void Config::Load(cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
		if (::ReadFrom(c, "fruit", fruit)) continue;
	}
}

cJSON* Config::CreatecJSON() const
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

	::WriteTo(object, "fruit", fruit);

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
	Load(root);
	cJSON_Delete(root);
}

void Config::Print(std::string& out) const
{
	cJSON* root = CreatecJSON();
	if (NULL == root)
	{
		return;
	}

	const char* text = cJSON_PrintUnformattedForGBK(root);
	if (NULL == text)
	{
		return;
	}
	out = text;
	free(text);
}

}
