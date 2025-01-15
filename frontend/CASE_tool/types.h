#pragma once
#include <string>
//TODO clean it
using AgentId_t = int; // type for agent ID

const AgentId_t MANAGER_ID = 1;

//node attributes
const std::string NODE_ID = "ID";
const std::string NODE_AGENT_ID = "AgentId";
const std::string NODE_NAME = "Name";
const std::string NODE_OUTSIDE_ID = "OutsideId";
const std::string NODE_COLOR = "Color";
const std::string NODE_TYPE = "Type";
const std::string NODE_SIZE = "Size";
const std::string NODE_DELETED = "Deleted";
const std::string NODE_STATE = "State";
const std::string NODE_SAVED_STATE = "SavedState";
const std::string NODE_INPUTS = "Inputs";
const std::string NODE_OUTPUTS = "Outputs";
const std::string NODE_INSIDE_IDS = "InsideIds";
const std::string NODE_ASSOCIATED_IDS = "AssociatedIds";
const std::string NODE_POSITION = "Position";

//pin attributes
const std::string PIN_ID = "ID";
const std::string PIN_NAME = "Name";
const std::string PIN_TYPE = "Type";
const std::string PIN_KIND = "Kind";
const std::string PIN_IS_ACTIVE = "IsActive";
const std::string PIN_LINK_IDS = "LinkIds";
const std::string PIN_BUTTON = "PinButton";
const std::string PIN_BUFFER = "PinBuffer";

//button attributes
const std::string BUTTON_LABEL = "Label";

//buffer attributes
const std::string BUFFER_TYPE = "Type";
const std::string BUFFER_BUFFER = "Buffer";

//Link attributes
const std::string LINK_ID = "ID";
const std::string LINK_START_PIN_ID = "StartPinID";
const std::string LINK_END_PIN_ID = "EndPinID";
const std::string LINK_COLOR = "Color";

//json types
const std::string CASE_TOOL_NODES = "m_Nodes";
const std::string CASE_TOOL_LINKS = "m_Links";
const std::string CASE_TOOL_AGENTS = "m_Agents";
const std::string CASE_TOOL_NEXT_ID = "m_NextId";
const std::string CASE_TOOL_NEXT_AGENT_ID = "m_NextAgentId";

//json types
//node types
const int SERVICE_ID = 1;
const int FUNCTION_ID  = 2;
const int CONDITION_ID = 3;
const int CODE_ID = 4;
const int ATTRIBUTE_ID = 5;
const int NO_TYPE_ID = -1;
//attribute
const std::string TYPE_ATR = "AtrType";
const std::string TYPE = "Type";
const std::string INIT_VALUE = "InitValue";
const std::string NAME = "Name";
const std::string ATTRIBUTES = "Attributes";
const std::string ID = "ID";

//functions
const std::string FUNCTIONS = "Functions";

//reasoning types
const std::string REACTIVE = "Reactive";
const std::string AGENT_ID = "Id";
const std::string PETRI_NET = "PetriNet";
const std::string MAIN = "Main";

//Petri net reasoning
//condition
const std::string CONDITION = "Condition";
const std::string IF = "If";
const std::string ELSE = "Else";
//code, service
const std::string LINKED = "Linked";
//service
const std::string SERVICE = "Service";

const std::string SERVICES = "Services";

const std::string HIERARCHY = "Hierarchy";
const std::string DATA = "Data";

const std::string SEARCH_ATR = "//attributes";
const std::string SEARCH_FUNCT = "//functions";
const std::string SEARCH_OVERRIDE = "override;";
const std::string SEARCH_H = "ReactiveReasoning.h\"";

const std::string TEMP_ATTRIBUTE = "Attribute";
const std::string TEMP_FUNCTION_DEF = "FunctionDef";
const std::string TEMP_FUNCTION_IMPL = "FunctionImpl";
const std::string TEMP_FUNCTION_REG = "FunctionReg";
const std::string TEMP_REACTIVE_FILE_NAME = "ReactiveFileName";
const std::string TEMP_MAIN_INITMSG_DEF = "InitMessageDef";
const std::string TEMP_MAIN_INITMSG_IMPL = "InitMessageImpl";
const std::string FILE_H = "File_h";
const std::string FILE_CPP = "File_cpp";
const std::string TEMPLATE = "Template";
