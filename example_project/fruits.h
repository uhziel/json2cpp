#ifndef __file_base_name__GXHEADER__
#define __file_base_name__GXHEADER__

#include "gx_utils.h"
#include "cJSON.h"

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

    std::string name;
    int price;
    GXDateTime per_sale_time;
    Energy energy;

    void LoadFrom(cJSON* node);
    cJSON* CreatecJSON() const;
};

struct Demo
{
    Demo();

    bool demo_bool;
    int demo_int;
    double demo_double;
    std::string demo_str;
    GXDateTime demo_time;
    //std::vector<std::vector<int> > demo_array;

    void LoadFrom(cJSON* node);
    cJSON* CreatecJSON() const;
};

struct Config
{
    Config();

    std::vector<Fruit> fruits;
    Demo demo;

    void LoadFrom(cJSON* node);
    cJSON* CreatecJSON() const;
    void Parse(const char* content);
    void Print(std::string& out) const;
};

#endif