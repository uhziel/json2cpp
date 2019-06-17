"use strict";

const testJsonString = `{
    "fruits": [
        {
            "name": "香蕉",
            "price": 10,
            "per_sale_time": "2018-12-27 00:11:01",
            "energy": {
                "__type__": "fruit_energy",
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
