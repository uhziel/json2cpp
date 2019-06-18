#include "fruits.h"
#include <string>

int main()
{
    Config cfg;
    cfg.Parse("{\"fruits\":[{\"__type__\":\"fruit\",\"name\":\"香蕉\",\"price\":10,\"per_sale_time\":\"2020-11-11 11:11:11\",\"energy\":{\"__type__\":\"energy\",\"carbohydrates\":22.84,\"fat\":0.33,\"protein\":1.09}},{\"name\":\"苹果\",\"price\":9,\"energy\":{\"carbohydrates\":0,\"fat\":0,\"protein\":0}}]}");
    std::string result;
    cfg.Print(result);
    return 0;
}
