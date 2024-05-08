#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <stdexcept>

#include "application.h"
#include "utilities/builders.h"
#include "utilities/widgets.h"
#include "imgui_project/imgui_node_editor.h"
#include "imgui_internal.h"

namespace ed = ax::NodeEditor;
namespace util = ax::NodeEditor::Utilities;

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
};

/**
 * Structure for condition node.
 */
struct Button {
    const char* Label;
    explicit Button(const char* label);
    ~Button();
};

/**
 * From imgui-node-editor-master.
 * Modified.
 */
struct Pin {
    ed::PinId   ID;
    TextBuffer* PinBuffer;
    ::Node*     Node;
    std::string Name;
    PinType     Type;
    PinKind     Kind;
    bool        IsActive;
    std::vector<ed::LinkId> LinkIds;
    Button*     PinButton;

    Pin(int id, const char* name, PinType type, TextBuffer* buffer, bool active = true);
};

/**
 * From imgui-node-editor-master.
 * Modified.
 */
struct Node {
    ed::NodeId ID;
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

    Node(int id, const char* name, NodeType type, ed::NodeId outsideId, ImColor color = ImColor(255, 255, 255));
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
private:
    ed::EditorContext* m_Editor;
    int                  m_NextId = 1;
    const int            m_PinIconSize = 24;
    const int            MANAGER_AGENT_ID = 1; // << if of agent manager
    std::vector<Node>    m_Nodes;
    std::vector<Link>    m_Links;
    ImTextureID          m_HeaderBackground = nullptr;
    ImTextureID          m_SaveIcon = nullptr;
    ImTextureID          m_RestoreIcon = nullptr;
    const float          m_TouchTime = 1.0f;
    std::map<ed::NodeId, float, NodeIdLess> m_NodeTouchTime;
    ed::NodeId           m_ContextNodeId = 0; // << id of context node
    ed::NodeId           m_Inside = 0; // << id of the node we are currently on
    Button*              m_ActiveButton = nullptr; // << pointer to active button in condition node
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
     * Get next agent Id.
     * @return ID
     */
    int GetNextId();

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
    bool CanCreateLink(Pin *a, Pin *b);

    /**
     * From imgui-node-editor-master.
     */
    void BuildNode(Node *node);

    /**
     * Create new text buffer.
     * @param type buffer type
     * @return     created buffer
     */
    TextBuffer* NewTextBuffer(BufferType type);

    /**
     * Set label of button.
     */
    void SetButtonLabel(Button* button, const char* label);

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
    std::string GetReasoningTypeAsString(ReasoningType type);

    /**
     * Get type of node based of reasoning type.
     * @param type reasoning type
     * @return     type of node
     */
    NodeType GetNodeTypeFromReasoningType(ReasoningType type);

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

    //TODO: we added shift attribute to imgui library - add it to documentation for future library updating
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
     * @param pin
     */
    void DeleteLink(Pin& pin);

    /**
     * Delete link id from pin list od its associated links.
     * @param otherPin pin id from that we delete link id
     * @param linkId    deleted link id
     */
    void DeleteLinkId(Pin* otherPin, ed::LinkId linkId);

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
     * From imgui-node-editor-master.
     */
    void ShowStyleEditor(bool* show = nullptr);

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
};