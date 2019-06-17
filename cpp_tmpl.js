'use strict';

let cppTmpl = {};

//////////////////////////////////////////////////
// HeaderFile
cppTmpl.genHeaderFile = (fileBaseName, tmplNamespace, content) =>
`#ifndef __${fileBaseName}__GXHEADER__
#define __${fileBaseName}__GXHEADER__

#include "gx_utils.h"
#include "cJSON.h"

namespace ${tmplNamespace} {
${content}
}

#endif
`;

cppTmpl.genHeaderFileStruct = (elemStructName, content) => `
struct ${elemStructName}
{
    ${elemStructName}();

${content}
    void LoadFrom(cJSON* node);
    cJSON* CreatecJSON() const;
};
`;

cppTmpl.genHeaderFileStructRoot = (content) => `
struct Config
{
    Config();

${content}
    void Load(cJSON* node);
    cJSON* CreatecJSON() const;
    void Parse(const char* content);
    void Print(std::string& out) const;
};
`;

cppTmpl.genHeaderFileStructVar = (type, variable) =>
`    ${type} ${variable};
`;

//////////////////////////////////////////////////
// SourceFile
cppTmpl.genSourceFile = (fileBaseName, tmplNamespace, content) =>
`#include "${fileBaseName}.config.h"

namespace ${tmplNamespace} {
${content}
}
`;

cppTmpl.genSourceFileCtor = (elemStructName, content) => `
${elemStructName}::${elemStructName}()
${content}{}
`;

cppTmpl.genSourceFileCtorVar = (variable, defaultValue, isFirst) => {
	return `    ${isFirst ? ':' : ','} ${variable}(${typeof defaultValue==='string' ? '\"'+defaultValue+'\"':defaultValue})
`;
};

cppTmpl.genSourceFileLoad = (elemStructName, content) => `
void ${elemStructName}::LoadFrom(cJSON* node)
{
	for (cJSON* c = node->child; c != NULL; c = c->next)
	{
${content}	}
}
`;

cppTmpl.genSourceFileLoadVar = (variable) =>
`		if (::ReadFrom(c, "${variable}", ${variable})) continue;
`;

cppTmpl.genSourceFileCreatecJSON = (elemStructName, content) => `
cJSON* ${elemStructName}::CreatecJSON() const
{
	cJSON* object = cJSON_CreateObject();
	if (object == NULL)
	{
		return NULL;
	}

${content}
	return object;
}
`;

cppTmpl.genSourceFileCreatecJSONVar = (variable) =>
`	::WriteTo(object, "${variable}", ${variable});
`;

cppTmpl.genSourceFileParse = () => `
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
`;

cppTmpl.genSourceFilePrint = () => `
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
	free(static_cast<void*>(text));
}
`;
