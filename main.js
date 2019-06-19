"use strict";

const testJsonString = `{
    "fruits": [
        {
            "__type__": "fruit",
            "name": "香蕉",
            "price": "10",
            "per_sale_time": "2018-12-27 00:11:01",
            "energy": {
                "__type__": "energy",
                "carbohydrates": "22.84",
                "fat": "0.33",
                "protein": "1.09"
            }
        }
    ],
    //演示支持的数据类型
    "demo": {
        "__type__": "demo",
        "demo_bool": "true",  //支持行注释
        "demo_int": "0",
        "demo_double": "0.1",
        "demo_str": "",
        "demo_time": "2018-12-27 00:11:01",
        "demo_array": [
            [
                1, 2, 3
            ]
        ]
    }
}`;

window.onload = function () {
    const jsonInput = document.getElementById("jsonInput");
    jsonInput.value = testJsonString;
}

function uncomment(jsonString) {
    return jsonString.replace(/\/\/.*$/gm, "");
}

function exec(jsonString) {
    console.log(jsonString);
    jsonString = uncomment(jsonString);
    console.log(" uncomment:", jsonString);
    let jsonObj = null;
    try {
        jsonObj = JSON.parse(jsonString);
    } catch (error) {
        const cppOutput = document.getElementById("cppOutput");
        cppOutput.value = error.message + "\n" + jsonString;
        return;
    }

    const codeGenerator = new CodeGenerator(cppTmpl);
    
    const cppOutput = document.getElementById("cppOutput");
    cppOutput.value = codeGenerator.genFromJSONObj(jsonObj);
}
