#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <deque>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "../../application/include/application.h"
#include "../utilities/builders.h"
#include "../utilities/widgets.h"
#include "../../../external/imgui_node/imgui_node_editor.h"
#include "../../../external/imgui/imgui_internal.h"
#include "agentGenerator.h"

namespace ed = ax::NodeEditor;
namespace util = ax::NodeEditor::Utilities;
using json = nlohmann::json;

using namespace ax;

using ax::Widgets::IconType;

enum class PinType
{
    Function,
    Attribute,
    Relationship,
    Service,
    Reasoning,
    Type,
    InitValue,
};

enum class PinKind
{
    Output,
    Input
};

enum class NodeType
{
    ExtAgent,
    RespService,
    ReasService,
    RespReasoningReactive,
    RespReasoningIntelligent,
    RespAgent,
    Attribute,
    Group,
    SimpleCond,
    SimpleCode,
    Function,
};

enum class BufferType
{
    Name,
    Type,
    InitValue,
    ServiceId,
    Id,
    Empty,
};

enum ReasoningType {
    Reactive,
    Intelligent,
};

struct Node;

/**
 * Structure for pin input.
 */
struct TextBuffer {
    BufferType Type;
    char Buffer[128];
    explicit TextBuffer(BufferType type);
    // Deserialize
    explicit TextBuffer(const json& data);
    json Serialize() const;
};

/**
 * Structure for condition node.
 */
struct Button {
    std::string Label = "";
    explicit Button(std::string label);
    // Deserialize
    explicit Button(const json& data);
    json Serialize() const;
};

/**
 * From imgui-node-editor-master.
 * Modified.
 */
struct Pin {
    ed::PinId   ID;
    TextBuffer* PinBuffer;
    ed::NodeId  NodeId;
    std::string Name;
    PinType     Type;
    PinKind     Kind;
    bool        IsActive;
    std::vector<ed::LinkId> LinkIds;
    Button*     PinButton;

    Pin(int id, const char* name, PinType type, TextBuffer* buffer, bool active = true);
    // Deserialize
    Pin(const json& data, ed::NodeId nodeId);
    json Serialize() const;
};

/**
 * From imgui-node-editor-master.
 * Modified.
 */
struct Node {
    ed::NodeId ID;
    AgentId_t AgentId;
    std::string Name;
    std::vector<Pin> Inputs;
    std::vector<Pin> Outputs;
    ed::NodeId OutsideId;
    std::vector<ed::NodeId> InsideIds;
    ImColor Color;
    NodeType Type;
    ImVec2 Size;
    std::vector<ed::NodeId> AssociatedIds;
    bool Deleted;

    std::string State;
    std::string SavedState;
    Node(int id, std::string name, NodeType type, ed::NodeId outsideId, ImColor color, AgentId_t agentId = -1);
    // Deserialize
    Node(const json& data);
    json Serialize() const;
    
private:
    json serializeVector(const std::vector<Pin>& pins) const;
    json serializeNodeIds(const std::vector<ed::NodeId>& ids) const;
};

/**
 * From imgui-node-editor-master.
 */
struct Link {
    ed::LinkId ID;
    ed::PinId StartPinID;
    ed::PinId EndPinID;
    ImColor Color;

    Link(ed::LinkId id, ed::PinId startPinId, ed::PinId endPinId);
    // Deserialize
    Link(const json& data);
    json Serialize() const;
};

/**
 * From imgui-node-editor-master.
 */
struct NodeIdLess {
    bool operator()(const ed::NodeId& lhs, const ed::NodeId& rhs) const;
};

/**
 * From imgui-node-editor-master.
 */
bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size = -1.0f);

# ifdef _MSC_VER
# define portable_strcpy    strcpy_s
# define portable_sprintf   sprintf_s
# else
# define portable_strcpy    strcpy
# endif

struct CASE_tool : public Application {
    using Application::Application;
    const std::string PROJECT_PATH = "/home/miska/CLionProjects/Agent_simulation_library";
    const std::string CASE_TOOL_PATH = PROJECT_PATH + "/frontend/CASE_tool";
    const std::string RESOURCE_PATH = CASE_TOOL_PATH + "/resources"; /**< Default path to resources. */
    typedef int AgentId;

private:
    ed::EditorContext* m_Editor;
    int                  m_NextId = 1;
    AgentId_t            m_NextAgentId = 1;
    const int            m_PinIconSize = 24;
    const int            MANAGER_AGENT_ID = 1; // << if of agent manager
    std::vector<Node>    m_Nodes;
    std::vector<ed::NodeId>  m_Agents;
    std::vector<Link>    m_Links;
    ImTextureID          m_HeaderBackground = nullptr;
    ImTextureID          m_SaveIcon = nullptr;
    ImTextureID          m_RestoreIcon = nullptr;
    const float          m_TouchTime = 1.0f;
    std::map<ed::NodeId, float, NodeIdLess> m_NodeTouchTime;
    ed::NodeId           m_ContextNodeId = 0; // << id of context node
    ed::NodeId           m_Inside = 0; // << id of the node we are currently on
    Button*              m_ActiveButton = nullptr; // << pointer to active button in condition node
    std::unique_ptr<AgentGenerator> agentGenerator = std::make_unique<AgentGenerator>();
    std::unique_ptr<FileManager> fileManager = std::make_unique<FileManager>();
    char m_renamed[64] = "";
    int counter = 1;
public:
    /**
     * Constructor.
     */
    CASE_tool();
    
    /**
     * Destructor.
     */
    ~CASE_tool();
private:
    /**
     * For correct application destructed.
     */
    void ReleaseTextures();

    /**
     * Get next node Id.
     * @return ID
     */
    int GetNextId();

    /**
     * Get next agent Id.
     * @return ID
     */
    int GetNextAgentId();

    /**
     * From imgui-node-editor-master.
     */
    void TouchNode(ed::NodeId id);

    /**
     * From imgui-node-editor-master.
     */
    void UpdateTouch();

    /**
     * From imgui-node-editor-master.
     */
    Node *FindNode(ed::NodeId id);

    /**
     * From imgui-node-editor-master.
     */
    Link *FindLink(ed::LinkId id);

    /**
     * From imgui-node-editor-master.
     */
    Pin *FindPin(ed::PinId id);

    /**
     * From imgui-node-editor-master.
     */
    bool IsPinLinked(ed::PinId id);

    /**
     * From imgui-node-editor-master.
     */
    static bool CanCreateLink(Pin *a, Pin *b);

    /**
     * From imgui-node-editor-master.
     */
    static void BuildNode(Node *node);

    /**
     * Create new text buffer.
     * @param type buffer type
     * @return     created buffer
     */
    static TextBuffer* NewTextBuffer(BufferType type);

    /**
     * Set label of button.
     */
    static void SetButtonLabel(Button* button, const char* label);

    /**
     * Creates node for representation agents' relationships.
     * @return created node
     */
    Node* SpawnAgentNodeTree();

    /**
     * Creates node for representation of agent's responsibilities
     * and types of decision making.
     * @param outsideId the ID of node that is hierarchically higher
     * @return          created node
     */
    Node* SpawnAgentNodeResponsibilities(ed::NodeId outsideId);

    /**
     * Creates node as box for agent reasoning attributes.
     * @param outsideId the ID of node that is hierarchically higher
     * @return          created node
     */
    Node* SpawnReasoningAttributes(ed::NodeId outsideId);

    /**
     * Creates node of agent intelligent reasoning.
     * For all added services in agent responsibility creates new node on reasoning level.
     * @param position  position of created node in canvas
     * @param outsideId the ID of node that is hierarchically higher
     * @return          created node
     */
    Node* SpawnIntelligentReasoningNode(ImVec2 position, ed::NodeId outsideId);

    /**
     * Creates node of agent reactive reasoning.
     * For all added services in agent responsibility creates new node on reasoning level.
     * @param position position of created node in canvas
     * @param outsideId the ID of node that is hierarchically higher
     * @return          created node
     */
    Node* SpawnReactiveReasoningNode(ImVec2 position, ed::NodeId outsideId);

    /**
     * Return reasoning type as string.
     * @param type type of reasoning
     * @return     string form of reasoning type
     */
    static std::string GetReasoningTypeAsString(ReasoningType type);

    /**
     * Get type of node based of reasoning type.
     * @param type reasoning type
     * @return     type of node
     */
    static NodeType GetNodeTypeFromReasoningType(ReasoningType type);

    /**
     * Creates nodes for representation of agent's relationships and responsibilities.
     * @param position  nodes position
     */
    void SpawnAgent(ImVec2 position);

    /**
     * Creates service on responsibility level.
     * @param outsideId     id of outside node
     * @return              created node
     */
    Node* SpawnServiceIdNodeResponsibilities(ed::NodeId outsideId);

    /**
     * Creates service node on reasoning level.
     * @param outsideId  id of outside node
     * @param buffer     buffer from associated service from responsibility level
     * @param associatedId  id of associated service from responsibility level
     * @return              created node
     */
    Node* SpawnServiceIdNodeReasoning(ed::NodeId outsideId, TextBuffer* buffer, ed::NodeId associatedId);

    /**
     * Creates service on responsibility level.
     * @param position  node position
     * @param outsideId ID of outside node
     * @return          created node
     */
    void SpawnServiceIdNode(ImVec2 position, ed::NodeId outsideId);

    /**
     * Creates node of attribute.
     * @param outsideId  ID of outside node
     * @return           created node
     */
    Node* SpawnAttributeNode(ed::NodeId outsideId);

    /**
     * Creates node of condition for creating Petri net.
     * @param outsideId  ID of outside node
     * @return           created node
     */
    Node* SpawnConditionNode(ed::NodeId outsideId);

    /**
     * Creates node of code in Petri net.
     * @param outsideId  ID of outside node
     * @return           created node
     */
    Node* SpawnCodeNode(ed::NodeId outsideId);

    /**
     * Creates node of function.
     * @param outsideId  ID of outside node
     * @return           created node
     */
    Node* SpawnFunctionNode(ed::NodeId outsideId);

    /**
     * From imgui-node-editor-master.
     * Preparation before GUI running.
     */
    void OnStart() override;

    /**
     * From imgui-node-editor-master.
     * End of the running GUI.
     */
    void OnStop() override;

    /**
     * From imgui-node-editor-master.
     */
    void ShowLeftPane(float paneWidth);

    /**
     * @brief Shows nodes in the left pane of the interface.
     *
     * This method iterates through the nodes stored in m_Nodes and displays those
     * of type NodeType::ExtAgent in the left pane using DepthSearching().
     */
    void ShowLeftPaneNodes();

    /**
     * @brief Recursively performs depth-first search starting from the given node.
     *
     * This method processes the given node and then recursively searches through its
     * child nodes, adjusting their position with each level of depth.
     *
     * @param node The starting node for the depth-first search.
     * @param shift The amount of shift to apply to the node's position.
     */
    void DepthSearching(Node& node, ImVec2 shift);

    /**
     * Display node text and provide control over its selection.
     * @param node      input node
     * @param shift     shift of node from left side of the panel
     */
    void DoWithNode(Node& node, const ImVec2& shift);

    /**
     * From imgui-node-editor-master.
     * Show inputs of blueprint and simple nodes.
     */
    void BlueprintAndSimpleInputs(Node& node, Pin* newLinkPin, util::BlueprintNodeBuilder &builder);

    /**
     * From imgui-node-editor-master.
     * Show outputs of blueprint and simple nodes.
     */
    void BlueprintAndSimpleOutputs(Node& node, Pin* newLinkPin, util::BlueprintNodeBuilder& builder);

    /**
     * From imgui-node-editor-master.
     * During GUI running.
     */
    void OnFrame(float deltaTime) override;

    /**
     * Delete links associated from pin.
     * We have to delete link ids from all ossiciated pins too.
     * @param pin   Id of pin
     */
    void DeleteLinks(Pin& pin);

    /**
     * Delete link associated from pin.
     * We have to delete link ids from all ossiciated pins too.
     * @param linkId deleted link id
     */
    void DeleteLink(ed::LinkId linkId);

    /**
     * Delete link id from pin list od its associated links.
     * @param otherPin pin id from that we delete link id
     * @param linkId    deleted link id
     */
    static void DeleteLinkId(Pin* otherPin, ed::LinkId linkId);

    /**
     * From imgui-node-editor-master.
     */
    void BuildNodes();

    /**
     * From imgui-node-editor-master.
     */
    ImColor GetIconColor(PinType type) const;

    /**
     * From imgui-node-editor-master.
     */
    void DrawPinIcon(const Pin& pin, bool connected, int alpha) const;

    /**
     * Add node to its outside node.
     * @param outsideId outside node id
     * @param insideId  added node id
     */
    void AddInsideNodeId(ed::NodeId outsideId, ed::NodeId insideId);

    /**
     * Add link id to list in its associated pin.
     * @param pinId     associated pin id
     * @param linkId    added link id
     */
    void AddLinkToPin(ed::PinId pinId, ed::LinkId linkId);

    /**
     * Delete node and all associated nodes.
     * @param nodeId deleted node id
     */
    void DeleteNode(ed::NodeId nodeId);

    /**
     * This method converts the internal state of the CASE_tool object, including nodes,
     * links, agents, and IDs, into a JSON format suitable for saving or transferring.
     *
     * @return json
     */
    json Serialize();

    /**
    * Loads project data from a JSON object.
    * @param data The JSON object containing project data to load.
    */
    void Deserialize(const json& data);

    /**
     * Helper function to serialize nodes.
     * @return serialized nodes
     */
    json SerializeNodes() const;

    /**
     * Helper function to serialize links.
     * @return serialized links
     */
    json SerializeLinks() const;

    /**
     * Helper function to serialize agents.
     * @return serialized agents
     */
    json SerializeAgents() const;

    /**
    * Helper function to deserialize nodes.
    * @return deserialized nodes
    */
    std::vector<Node> DeserializeNodes(const json& nodes_data);

    /**
     * Helper function to deserialize links.
     * @return deserialized links
     */
    std::vector<Link> DeserializeLinks(const json& links_data);
    
    /**
     * Helper function to deserialize agents.
     * @return deserialized agents
     */
    std::vector<ed::NodeId> DeserializeAgents(const json& agents_data);
    
    /**
     * @brief Retrieves data from the current state of the application and saves it as JSON.
     *
     * This method iterates through all external agents in the application, retrieves their data,
     * and constructs a JSON object representing the state of the system. The JSON data is then
     * saved to a file in a specified location.
     *
     * @throws std::runtime_error if the file cannot be opened for writing.
     */
    json GetData();

    /**
     * @brief Adds linked node to a JSON object.
     *
     * This function adds linked node represented by the provided link to a JSON object.
     * The linked node is added under the specified key in the JSON object.
     * If there is more than one linked node, only the first one will be accepted.
     *
     * @param links The vector of link IDs representing the links between nodes.
     * @param key The key under which the linked nodes will be added in the JSON object.
     * @param data The JSON object to which the linked nodes will be added.
     */
    void AddLinkedNode(std::vector<ed::LinkId> &links, std::string key, json &data);

    void ShowProjectEditor(bool* show = nullptr);
    void ShowGenerateCodeEditor(bool* show = nullptr);
    void ShowErrorMessageEditor(bool* show = nullptr);
    std::deque<Node*> GetEndNodes(Pin* pin);
    ed::LinkId GetNextLinkId();
    //void LoadProject(json input);
};