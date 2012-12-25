#ifndef SNIPER_TOOL_FACTORY_H
#define SNIPER_TOOL_FACTORY_H

#include <string>

class ToolBase;

class ToolFactory
{
    public :
	ToolFactory(const std::string& name, ToolBase* (*creator)(const std::string&));
};

#define DECLARE_TOOL(ToolClass) \
ToolBase* _tool_##ToolClass##_creator_(const std::string& objName) { return new ToolClass(objName); } \
ToolFactory  _reg_tool_##ToolClass##_creator(#ToolClass, &_tool_##ToolClass##_creator_)

#endif  //SNIPER_TOOL_FACTORY_H
