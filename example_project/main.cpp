#include "fruits.h"
#include <string>

int main()
{
    Config cfg;
    cfg.Parse("{\"fruits\":[{\"__type__\":\"fruit\",\"name\":\"香蕉\",\"price\":10,\"per_sale_time\":\"2018-12-27 00:11:01\",\"energy\":{\"__type__\":\"energy\",\"carbohydrates\":22.84,\"fat\":0.33,\"protein\":1.09}}],\"demo\":{\"__type__\":\"demo\",\"demo_bool\":true,\"demo_int\":1,\"demo_double\":0.1,\"demo_str\":\"\",\"demo_time\":\"2018-12-27 00:11:01\",\"demo_array\":[[1,2,3]]}}");
    std::string result;
    cfg.Print(result);
    return 0;
}
