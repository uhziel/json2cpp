"use strict";

const testJsonString = `
{
    "fruits": [
        {
            "name": "香蕉",
            "price": 10,
            "per_sale_time": "2018-12-27 00:11:01",
            "energy": {
                "carbohydrates": 22.84,
                "fat": 0.33,
                "protein": 1.09
            }
        },
        {
            "name": "苹果",
            "price": 9,
            "energy": {
                "carbohydrates": 0,
                "fat": 0,
                "protein": 0  
            }
        }
    ]
}`

function json2cpp(jsonObj) {
    return "被生成的代码";
}

function genCpp(jsonString) {
    jsonString = testJsonString;
    console.log(jsonString);
    const jsonObj = JSON.parse(jsonString);
    const cppOutput = document.getElementById("cppOutput");
    cppOutput.value = json2cpp(jsonObj);
}