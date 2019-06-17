#ifndef __fruits__GXHEADER__
#define __fruits__GXHEADER__

#include "gx_utils.h"
#include "cJSON.h"

namespace GXFruits {

struct Energy
{
    Energy();

    double carbohydrates;
    double fat;
    double protein;

    void LoadFrom(cJSON* node);
    cJSON* CreatecJSON() const;
};

struct Fruit
{
    Fruit();

    Energy energy;
    std::string name;
    int price;
    GXDateTime per_sale_time;

    void Load(cJSON* node);
    cJSON* CreatecJSON() const;
};

struct Config
{
    Config();

    std::vector<GXShare::Fruit> fruit;

    void Load(cJSON* node);
    cJSON* CreatecJSON() const;
    void Parse(const char* content);
    void Print(std::string& out) const;
};

}

#endif
