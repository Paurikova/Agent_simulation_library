#pragma once
#include <string>
//TODO clean it
using AgentId_t = int; // type for agent ID

const AgentId_t REASONING_ID_START = 1;

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

//functions
const std::string FUNCTIONS = "Functions";

//reasoning types
const std::string REACTIVE = "Reactive";
const std::string PETRI_NET = "PetriNet";

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
const std::string SEARCH_H = "ReactiveReasoning.h\"";

const std::string TEMP_ATTRIBUTE = "Attribute";
const std::string TEMP_FUNCTION_DEF = "FunctionDef";
const std::string TEMP_FUNCTION_IMPL = "FunctionImpl";
const std::string TEMP_FUNCTION_REG = "FunctionReg";
const std::string TEMP_REACTIVE_FILE_NAME = "ReactiveFileName";
const std::string FILE_H = "File_h";
const std::string FILE_CPP = "File_cpp";
