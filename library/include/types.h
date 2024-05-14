#pragma once
#include <string>
#include <functional>

using AgentId_t = int; // type for agent ID
using ServiceId_t = int; // type for service ID
using SimTime_t = float; // type for simulation time
using ExecFunct_t = std::function<void(int, SimTime_t)>; // type for function callback

//enum class AgentType {REACTIVE, INTELLIGENT};

const AgentId_t SIMULATION_CORE_ID = 1;
const AgentId_t REASONING_ID_START = 2;

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