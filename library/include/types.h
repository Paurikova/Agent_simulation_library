#pragma once
#include <string>
#include <functional>
#include <deque>
#include <variant>

using AgentId_t = int; // type for agent ID
using ServiceId_t = int; // type for service ID
using SimTime_t = float; // type for simulation time
using NodeId_t = int;
using ExecFunct_t = std::function<void(int, int, SimTime_t, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>>)>; // type for function callback
using ExecNode_t = std::function<NodeId_t(int, int, SimTime_t, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>>)>; // type for function callback

const AgentId_t SIMULATION_CORE_ID = 1;
const AgentId_t REASONING_ID_START = 2;
const NodeId_t UNDEFINATED_NODE =  -1;
