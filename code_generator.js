'use strict';

/*
 * tools
 */
//gx_editor -> GxEditor
function toPascal(underscore) {
    underscore = "_" + underscore;
    return underscore.replace(/_([a-z])/g, (x, y) => {
        return y.toUpperCase();
    });
}

function isInt(str) {
    return str.match(/^[-+]?\d+$/);
}

function isDouble(str) {
    return str.match(/^[-+]?\d+\.\d+$/);
}

function isBool(str) {
    return str === "true" || str === "false";
}

function isDatetime(str) {
    return str.match(/^\d\d\d\d-(0?[1-9]|1[0-2])-(0?[1-9]|[12][0-9]|3[01]) (00|[0-9]|1[0-9]|2[0-3]):([0-9]|[0-5][0-9]):([0-9]|[0-5][0-9])$/) !== null;
}

//返回v的基本类型
function getRawType(v) {
    const s = Object.prototype.toString.call(v);
    return s.match(/\[object (.*?)\]/)[1].toLowerCase();
}

function getVectorVariableType(variableType, depth) {
    if (depth <= 0) {
        return `${variableType}`;
    } else if (depth == 1) {
        return `std::vector<${variableType}>`;
    }
    return `std::vector<${getVectorVariableType(variableType, depth - 1)} >`;
}

/*
 * code
 */
function CodeGenerator(cppTmpl) {
    this.cppTmpl = cppTmpl;
    this.tempTypeAutoId = 0;
}

CodeGenerator.prototype.genFromJSONObj = function (jsonObj) {
    const fileBaseName = "file_base_name";

    this.preprocessJSON(jsonObj);

    const headerContent = this.genHeaderContent(jsonObj);
    const header = this.cppTmpl.genHeaderFile(fileBaseName,
        headerContent);

    const sourceContent = this.genSourceContent(jsonObj);
    const source = this.cppTmpl.genSourceFile(fileBaseName,
        sourceContent);

    return header + "\n//cpp\n" + source;
};

CodeGenerator.prototype.preprocessJSON = function (jsonObj) {
    if (!jsonObj.__type__) {
        jsonObj.__type__ = this.getTempKey();
    }

    for (const key in jsonObj) {
        if (jsonObj.hasOwnProperty(key)) {
            const value = jsonObj[key];
            const rawType = getRawType(value);
            if (rawType === "object") {
                if (!value.__type__) {
                    value.__type__ = key;
                }
            } else if (rawType === "array") {
                const childObj = this.getArrayChildObject(value);
                if (childObj) {
                    if (!childObj.__type__) {
                        childObj.__type__ = this.getTempKey();
                    }
                }
            }
        }
    }
};

CodeGenerator.prototype.getArrayChildObject = function (arrayObj) {
    let childObj = arrayObj;

    let rawType = getRawType(childObj);
    while(rawType === "array") {
        if (childObj.length <= 0) {
            return null;
        }

        childObj = childObj[0];
        rawType = getRawType(childObj)
    }
    if (rawType !== "object") {
        return null;
    }

    return childObj;
}

CodeGenerator.prototype.genHeaderContent = function (jsonObj, jsonKey) {
    let content = "";
    let varContent = "";
    for (const key in jsonObj) {
        if (jsonObj.hasOwnProperty(key) && key !== "__type__") {
            const value = jsonObj[key];
            const typeInfo = this.getTypeInfo(key, value);
            if (typeInfo.subStruct) {
                content += this.genHeaderContent(typeInfo.subStruct.jsonObj,
                    typeInfo.subStruct.key);
            }

            varContent += this.cppTmpl.genHeaderFileStructVar(typeInfo.variableType,
                typeInfo.variableName);
        }
    }

    if (!jsonKey) {
        content += this.cppTmpl.genHeaderFileStructRoot(varContent);
    } else {
        content += this.cppTmpl.genHeaderFileStruct(toPascal(jsonObj.__type__), varContent);
    }

    return content;
};

CodeGenerator.prototype.genSourceContent = function (jsonObj, jsonKey) {
    let content = "";
    let constructorContent = "";
    let loadContent = "";
    let createcJSONContent = "";
    let isFirst = true;
    for (const key in jsonObj) {
        if (jsonObj.hasOwnProperty(key) && key !== "__type__") {
            const value = jsonObj[key];
            const typeInfo = this.getTypeInfo(key, value);
            if (typeInfo.subStruct) {
                content += this.genSourceContent(typeInfo.subStruct.jsonObj,
                    typeInfo.subStruct.key);
            }

            if (typeInfo.rawType !== "object" && typeInfo.rawType !== "array") {
                constructorContent += this.cppTmpl.genSourceFileCtorVar(typeInfo.variableName,
                    typeInfo.variableValue, isFirst);
                isFirst = false;
            }
            loadContent += this.cppTmpl.genSourceFileLoadVar(typeInfo.variableName);
            createcJSONContent += this.cppTmpl.genSourceFileCreatecJSONVar(typeInfo.variableName);
        }
    }

    if (!jsonKey) {
        content += this.cppTmpl.genSourceFileCtor("Config", constructorContent);
        content += this.cppTmpl.genSourceFileLoad("Config", loadContent);
        content += this.cppTmpl.genSourceFileCreatecJSON("Config", createcJSONContent);
        content += this.cppTmpl.genSourceFileParse();
        content += this.cppTmpl.genSourceFilePrint();
    } else {
        content += this.cppTmpl.genSourceFileCtor(toPascal(jsonObj.__type__), constructorContent);
        content += this.cppTmpl.genSourceFileLoad(toPascal(jsonObj.__type__), loadContent);
        content += this.cppTmpl.genSourceFileCreatecJSON(toPascal(jsonObj.__type__), createcJSONContent);
    }

    return content;
};

CodeGenerator.prototype.getTempKey = function () {
    (this.tempTypeAutoId)++;
    return `temp_key${this.tempTypeAutoId}`;
}

CodeGenerator.prototype.getArrayTypeInfo = function (v, depth) {
    if (v.length <= 0) {
        return "EmptyArray";
    }
    if (!depth) {
        depth = 1;
    }

    const item = v[0];
    const rawType = getRawType(item);
    if (rawType === "object") {
        const tempKey = item.__type__;
        const typeInfo = this.getTypeInfo(tempKey, item);

        const arrayTypeInfo = {
            variableType: getVectorVariableType(typeInfo.variableType, depth),
            subStruct: {
                jsonObj: item,
                key: tempKey
            }
        };
        return arrayTypeInfo;
    } else if (rawType === "array") {
        return this.getArrayTypeInfo(item, depth + 1);
    } else {
        const typeInfo = this.getTypeInfo("dummy", item);

        const arrayTypeInfo = {
            variableType: getVectorVariableType(typeInfo.variableType, depth),
            subStruct: null
        };
        return arrayTypeInfo;
    }
}

CodeGenerator.prototype.getTypeInfo = function (key, value) {
    const rawType = getRawType(value);
    let typeInfo = {
        rawType: rawType,
        variableType: rawType,
        variableName: key,
        variableValue: value,
        subStruct: null
    };
    if (typeInfo.rawType === "object") {
        typeInfo.variableType = toPascal(value.__type__);
        typeInfo.subStruct = {
            jsonObj: value,
            key: key
        };
    } else if (typeInfo.rawType === "array") {
        const arrayTypeInfo = this.getArrayTypeInfo(value);
        if (arrayTypeInfo === "EmptyArray") {
            typeInfo.variableType = "EmptyArray";
        } else {
            typeInfo.variableType = arrayTypeInfo.variableType;
            typeInfo.subStruct = arrayTypeInfo.subStruct;
        }
    } else if (typeInfo.rawType === "number") {
        if (value % 1 === 0) {
            typeInfo.variableType = "int";
        } else {
            typeInfo.variableType = "double";
        }
    } else if (typeInfo.rawType === "boolean") {
        typeInfo.variableType = "bool";
    } else if (typeInfo.rawType === "string") {
        if (isInt(value)) {
            typeInfo.variableType = "int";
            typeInfo.variableValue = parseInt(value);
        } else if (isDouble(value)) {
            typeInfo.variableType = "double";
            typeInfo.variableValue = parseFloat(value);
        } else if (isBool(value)) {
            typeInfo.variableType = "bool";
            typeInfo.variableValue = (value === "true");
        } else if (isDatetime(value)) {
            typeInfo.variableType = "GXDateTime";
        } else {
            typeInfo.variableType = "std::string";
        }
    }
    return typeInfo;
}