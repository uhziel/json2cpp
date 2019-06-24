#ifndef __file_base_name__GXHEADER__
#define __file_base_name__GXHEADER__

#include "json2cpp_utils.h"
#include "cJSON.h"

struct Energy
{
    Energy();

    double carbohydrates;
    double fat;
    double protein;
};

bool LoadFrom(Energy& value, cJSON* node);
cJSON* CreatecJSON(const Energy& value);

struct Fruit
{
    Fruit();

    std::string name;
    int price;
    GXDateTime per_sale_time;
    Energy energy;
};

bool LoadFrom(Fruit& value, cJSON* node);
cJSON* CreatecJSON(const Fruit& value);

struct Demo
{
    Demo();

    bool demo_bool;
    int demo_int;
    double demo_double;
    std::string demo_str;
    GXDateTime demo_time;
    std::vector<std::vector<int> > demo_array;
};

bool LoadFrom(Demo& value, cJSON* node);
cJSON* CreatecJSON(const Demo& value);

struct Config
{
    Config();

    std::vector<Fruit> fruits;
    Demo demo;

    void Parse(const char* content);
    void Print(std::string& out) const;
};

bool LoadFrom(Config& value, cJSON* node);
cJSON* CreatecJSON(const Config& value);

#endif