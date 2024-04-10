#define IMGUI_DEFINE_MATH_OPERATORS
#include <application.h>
#include "utilities/builders.h"
#include "utilities/widgets.h"

#include <imgui_project/imgui_node_editor.h>
#include <imgui_internal.h>

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <stdexcept>

//TODO
//popup option in conditions

/**
 * From imgui-node-editor-master.
 */
static inline ImRect ImGui_GetItemRect()
{
    return ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
}

/**
 * From imgui-node-editor-master.
 */
static inline ImRect ImRect_Expanded(const ImRect& rect, float x, float y)
{
    auto result = rect;
    result.Min.x -= x;
    result.Min.y -= y;
    result.Max.x += x;
    result.Max.y += y;
    return result;
}

namespace ed = ax::NodeEditor;
namespace util = ax::NodeEditor::Utilities;

using namespace ax;

using ax::Widgets::IconType;

static ed::EditorContext* m_Editor = nullptr;

enum class PinType
{
    Function,
    Attribute,
    Relationship,
    Service,
    Reasoning,
    Type,
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
    IntAgent,
    SimpleCond,
    SimpleCode,
    Function,
};

enum class BufferType
{
    Name,
    Type,
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
 * Definition of text buffer for the pin.
 */
struct TextBuffer {
    BufferType Type; //< initialization text value of the buffer
    char Buffer[128];

    /**
     * Constuctor for initialization buffer.
     * @param type Type of pin that is converted to string.
     */
    TextBuffer(BufferType type) : Type(type) {
        // Set the initialization text of Buffer based on the pin type
        switch (type) {
            case BufferType::Name:
                strcpy(Buffer, "Name");
                break;
            case BufferType::Type:
                strcpy(Buffer, "Type");
                break;
            case BufferType::ServiceId:
                strcpy(Buffer, "ServiceId");
                break;
            case BufferType::Id:
                strcpy(Buffer, "Id");
                break;
            default: strcpy(Buffer, "Edit me");
                break;
        }
    }
};

struct Button
{
    char* Label;
    Button(char* label): Label(label) {}
};

/**
 * From imgui-node-master-editor.
 * Structure represents node pin.
 * The nodes are connected by them.
 */
struct Pin
{
    ed::PinId   ID;
    TextBuffer* PinBuffer;  //< buffer for user text input
    ::Node*     Node;
    std::string Name;
    PinType     Type;
    PinKind     Kind;
    bool        IsActive;   //< value if by this pin can be node connected by other node
    std::vector<ed::LinkId> LinkIds; //< ids of links that are associated by the pin
    Button*     PinButton; //< Button for user choice from options

    Pin(int id, const char* name, PinType type, TextBuffer* buffer, bool active = true):
            ID(id), Node(nullptr), Name(name), Type(type), Kind(PinKind::Input), PinBuffer(buffer), IsActive(active)
    {
    }
};

/**
 * From imgui-node-master-editor.
 * Structure represents node.
 */
struct Node
{
    ed::NodeId ID;
    std::string Name;
    std::vector<Pin> Inputs;
    std::vector<Pin> Outputs;
    ed::NodeId OutsideId;   //< id of node that is over this node
    std::vector<ed::NodeId> InsideIds;  //ids of nodes that are under this node
    ImColor Color;
    NodeType Type;
    ImVec2 Size;
    std::vector<ed::NodeId> AssociatedIds; // node id by which is node associated
    bool Deleted; //< true if is node deleting

    std::string State;
    std::string SavedState;

    Node(int id, const char* name, NodeType type, ed::NodeId outsideId, ImColor color = ImColor(255, 255, 255)):
            ID(id), Name(name), Color(color), Type(type), Size(0, 0), OutsideId(outsideId),
            Deleted(false)
    {
    }
};

/**
 * From imgui-node-editor-master.
 * Structure for connecting of the two nodes.
 */
struct Link
{
    ed::LinkId ID;

    ed::PinId StartPinID;
    ed::PinId EndPinID;

    ImColor Color;

    Link(ed::LinkId id, ed::PinId startPinId, ed::PinId endPinId):
            ID(id), StartPinID(startPinId), EndPinID(endPinId), Color(255, 255, 255)
    {
    }
};

/**
 * From imgui-node-editor-master.
 */
struct NodeIdLess
{
    bool operator()(const ed::NodeId& lhs, const ed::NodeId& rhs) const
    {
        return lhs.AsPointer() < rhs.AsPointer();
    }
};

/**
 * From imgui-node-editor-master.
 */
static bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size = -1.0f)
{
    using namespace ImGui;
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;
    ImGuiID id = window->GetID("##Splitter");
    ImRect bb;
    bb.Min = window->DC.CursorPos + (split_vertically ? ImVec2(*size1, 0.0f) : ImVec2(0.0f, *size1));
    bb.Max = bb.Min + CalcItemSize(split_vertically ? ImVec2(thickness, splitter_long_axis_size) : ImVec2(splitter_long_axis_size, thickness), 0.0f, 0.0f);
    return SplitterBehavior(bb, id, split_vertically ? ImGuiAxis_X : ImGuiAxis_Y, size1, size2, min_size1, min_size2, 0.0f);
}

# ifdef _MSC_VER
# define portable_strcpy    strcpy_s
# define portable_sprintf   sprintf_s
# else
# define portable_strcpy    strcpy
# endif

struct CASE_tool:
        public Application {
    using Application::Application;

    int GetNextId() {
        return m_NextId++;
    }

    ed::LinkId GetNextLinkId() {
        return ed::LinkId(GetNextId());
    }

    void TouchNode(ed::NodeId id) {
        m_NodeTouchTime[id] = m_TouchTime;
    }

    float GetTouchProgress(ed::NodeId id) {
        auto it = m_NodeTouchTime.find(id);
        if (it != m_NodeTouchTime.end() && it->second > 0.0f)
            return (m_TouchTime - it->second) / m_TouchTime;
        else
            return 0.0f;
    }

    void UpdateTouch() {
        const auto deltaTime = ImGui::GetIO().DeltaTime;
        for (auto &entry: m_NodeTouchTime) {
            if (entry.second > 0.0f)
                entry.second -= deltaTime;
        }
    }

    Node *FindNode(ed::NodeId id) {
        for (auto &node: m_Nodes)
            if (node.ID == id)
                return &node;

        return nullptr;
    }

    Link *FindLink(ed::LinkId id) {
        for (auto &link: m_Links)
            if (link.ID == id)
                return &link;

        return nullptr;
    }

    Pin *FindPin(ed::PinId id) {
        if (!id)
            return nullptr;

        for (auto &node: m_Nodes) {
            for (auto &pin: node.Inputs)
                if (pin.ID == id)
                    return &pin;

            for (auto &pin: node.Outputs)
                if (pin.ID == id)
                    return &pin;
        }

        return nullptr;
    }

    bool IsPinLinked(ed::PinId id) {
        if (!id)
            return false;

        for (auto &link: m_Links)
            if (link.StartPinID == id || link.EndPinID == id)
                return true;

        return false;
    }

    bool CanCreateLink(Pin *a, Pin *b) {
        if (!a || !b || a == b || !a->IsActive || !b->IsActive || a->Kind == b->Kind || a->Type != b->Type || a->Node == b->Node)
            return false;

        return true;
    }

    void BuildNode(Node *node) {
        for (auto &input: node->Inputs) {
            input.Node = node;
            input.Kind = PinKind::Input;
        }

        for (auto &output: node->Outputs) {
            output.Node = node;
            output.Kind = PinKind::Output;
        }
    }

    /**
     * Returns new text buffer based on input buffer type.
     * @param type type of buffer
     * @return     created buffer
     */
    TextBuffer* NewTextBuffer(BufferType type) {
        return new TextBuffer(type);
    }

    /**
     * Method sets label of button by user input.
     * @param button  button
     * @param label   new label
     */
    void SetButtonLabel(Button* button, char* label) {
        button->Label = label;
    }

    /**
     * Creates node for representation agents' relationships.
     * @return created node
     */
    Node* SpawnAgentNodeTree()
    {
        m_Nodes.emplace_back(GetNextId(), "Agent Relationships", NodeType::ExtAgent, 0);
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Relationship, NewTextBuffer(BufferType::Empty));
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Relationship, NewTextBuffer(BufferType::Empty));
        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    /**
     * Creates node for representation of agent's responsibilities
     * and types of decision making.
     * @param outsideId the ID of node that is hierarchically higher
     * @return          created node
     */
    Node* SpawnAgentNodeResponsibilities(ed::NodeId outsideId)
    {
        m_Nodes.emplace_back(GetNextId(), "Agent Responsibilities", NodeType::RespAgent, outsideId);
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "Reasoning", PinType::Reasoning, NewTextBuffer(BufferType::Empty));
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "Services", PinType::Service, NewTextBuffer(BufferType::Empty));
        BuildNode(&m_Nodes.back());
        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        return &m_Nodes.back();
    }

    /**
     * Creates node for agent's attribute.
     * @param outsideId the ID of node that is hierarchically higher
     * @return          created node
     */
    Node* SpawnAgentNodeAttributes(ed::NodeId outsideId)
    {
        m_Nodes.emplace_back(GetNextId(), "Agent Features", NodeType::IntAgent, outsideId);
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "Attributes", PinType::Attribute, NewTextBuffer(BufferType::Empty));
        BuildNode(&m_Nodes.back());
        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        return &m_Nodes.back();
    }

    /**
     * Creates node of agent intelligent reasoning.
     * For all added services in agent responsibility creates new node on reasoning level.
     * @param position  position of created node in canvas
     * @param outsideId the ID of node that is hierarchically higher
     * @return          created node
     */
    Node* SpawnIntelligentReasoningNode(ImVec2 position, ed::NodeId outsideId)
    {
        ReasoningType type = ReasoningType::Intelligent;
        m_Nodes.emplace_back(GetNextId(), "Reasoning", GetNodeTypeFromReasoningType(type), outsideId, ImColor(153,255,153));
        m_Nodes.back().Outputs.emplace_back(GetNextId(), GetReasiningTypeAsString(type).c_str(), PinType::Reasoning, NewTextBuffer(BufferType::Empty));
        BuildNode(&m_Nodes.back());
        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        ed::NodeId reasoningId = m_Nodes.back().ID;
        ed::SetNodePosition(reasoningId, position);
        //create service node if service exists on level of responsibility
        Node* outsideNode = FindNode(outsideId);
        for (ed::NodeId id : outsideNode->InsideIds) {
            // find outside node
            Node* insideNode = FindNode(id);
            // Is node type of Service?
            if (insideNode->Type != NodeType::RespService)
                continue;
            // create service node on reasoning level
            Node* serviceNode = SpawnServiceIdNodeReasoning(reasoningId, insideNode->Inputs.back().PinBuffer, id);
            ed::SetNodePosition(serviceNode->ID, position);
            position.y = position.y + 50;
            //add associated node to RespService
            insideNode->AssociatedIds.push_back(serviceNode->ID);
        }
        return FindNode(reasoningId);
    }

    /**
     * Creates node of agent reactive reasoning.
     * For all added services in agent responsibility creates new node on reasoning level.
     * @param position position of created node in canvas
     * @param outsideId the ID of node that is hierarchically higher
     * @return          created node
     */
    Node* SpawnReactiveReasoningNode(ImVec2 position, ed::NodeId outsideId) {
        ReasoningType type = ReasoningType::Reactive;
        m_Nodes.emplace_back(GetNextId(), "Reasoning", GetNodeTypeFromReasoningType(type), outsideId, ImColor(0,204,102));
        m_Nodes.back().Outputs.emplace_back(GetNextId(), GetReasiningTypeAsString(type).c_str(), PinType::Reasoning, NewTextBuffer(BufferType::Empty));
        BuildNode(&m_Nodes.back());
        // add node to its outside node
        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        ed::NodeId reasoningId = m_Nodes.back().ID;
        ed::SetNodePosition(reasoningId, position);
        //create service node if service exists
        Node* outsideNode = FindNode(outsideId);
        for (ed::NodeId id : outsideNode->InsideIds) {
            Node* insideNode = FindNode(id);
            if (insideNode->Type != NodeType::RespService)
                continue;
            Node* serviceNode = SpawnServiceIdNodeReasoning(reasoningId, insideNode->Inputs.back().PinBuffer, id);
            ed::SetNodePosition(serviceNode->ID, position);
            position.y = position.y + 50;
            //add associated node to RespService
            insideNode->AssociatedIds.push_back(serviceNode->ID);
        }
        return FindNode(reasoningId);
    }

    /**
     * Return reasoning type as string.
     * @param type type of reasoning
     * @return     string form of reasoning type
     */
    std::string GetReasiningTypeAsString(ReasoningType type) {
        switch(type) {
            case(ReasoningType::Reactive): return "Reactive";
            case(ReasoningType::Intelligent): return "Intelligent";
            default: throw std::runtime_error("String version for input doesn't exist.");
        }
    }

    /**
     * Get type of node based of reasoning type.
     * @param type reasoning type
     * @return     type of node
     */
    NodeType GetNodeTypeFromReasoningType(ReasoningType type) {
        switch (type) {
            case (ReasoningType::Reactive): return NodeType::RespReasoningReactive;
            case (ReasoningType::Intelligent): return NodeType::RespReasoningIntelligent;
            default: throw std::runtime_error("NodeType for input ReasoningType doesn't exist.");
        }
    }

    /**
     * Creates nodes for representation of agent's relationships, responsibilities and features.
     * @param position  nodes position
     */
    void SpawnAgent(ImVec2 position) {
        // relationships
        Node* node = SpawnAgentNodeTree(); ed::SetNodePosition(node->ID, position);
        // responsibilities
        node = SpawnAgentNodeResponsibilities(node->ID); ed::SetNodePosition(node->ID, position);
        // features
        node = SpawnAgentNodeAttributes(node->ID); ed::SetNodePosition(node->ID, position);
    }

    /**
     * Creates service on responsibility level.
     * @param outsideId     id of outside node
     * @return              created node
     */
    Node* SpawnServiceIdNodeResponsibilities(ed::NodeId outsideId)
    {
        m_Nodes.emplace_back(GetNextId(), "Service", NodeType::RespService, outsideId,ImColor(128, 195, 248));
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "Id", PinType::Service, NewTextBuffer(BufferType::Id));

        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        BuildNode(&m_Nodes.back());
        return &m_Nodes.back();
    }

    /**
     * Creates service node on reasoning level.
     * @param outsideId  id of outside node
     * @param buffer     buffer from associated service from responsibility level
     * @param associatedId  id of associated service from responsibility level
     * @return              created node
     */
    Node* SpawnServiceIdNodeReasoning(ed::NodeId outsideId, TextBuffer* buffer, ed::NodeId associatedId)
    {
        m_Nodes.emplace_back(GetNextId(), "Service", NodeType::ReasService, outsideId,ImColor(128, 195, 248));
        // add associated ID to node
        m_Nodes.back().AssociatedIds.push_back(associatedId);
        Node* outsideNode = FindNode(outsideId);
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "Id", PinType::Function, buffer);
        // add node to its outside node
        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        BuildNode(&m_Nodes.back());
        return &m_Nodes.back();
    }

    /**
     * Creates service on responsibility level.
     * @param position  node position
     * @param outsideId ID of outside node
     * @return          created node
     */
    Node* SpawnServiceIdNode(ImVec2 position, ed::NodeId outsideId) {
        // create service on responsibility level
        Node *node = SpawnServiceIdNodeResponsibilities(outsideId);
        ed::SetNodePosition(node->ID, position);
        Node* outsideNode = FindNode(outsideId);
        // find reasoning nodes added to agent
        for(ed::NodeId id: outsideNode->InsideIds) {
            Node* insideNode = FindNode(id);
            if (insideNode->Type == NodeType::RespReasoningIntelligent || insideNode->Type == NodeType::RespReasoningReactive) {
                // create service node in reasoning level
                // associate it with created node
                Node* serviceNode = SpawnServiceIdNodeReasoning(id, node->Inputs.back().PinBuffer, node->ID);
                // add created service ID to node associated IDs
                node->AssociatedIds.push_back(serviceNode->ID);
            }
        }
    }

    /**
     * Creates node of attribute.
     * @param outsideId  ID of outside node
     * @return           created node
     */
    Node* SpawnAttributeNode(ed::NodeId outsideId)
    {
        m_Nodes.emplace_back(GetNextId(), "Attribute", NodeType::IntAgent, outsideId, ImColor(128, 195, 248));

        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Type, NewTextBuffer(BufferType::Type));
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Attribute, NewTextBuffer(BufferType::Name));
        BuildNode(&m_Nodes.back());
        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        return &m_Nodes.back();
    }

    /**
     * Creates node of condition for creating Petri net.
     * @param outsideId  ID of outside node
     * @return           created node
     */
    Node* SpawnConditionNode(ed::NodeId outsideId)
    {
        m_Nodes.emplace_back(GetNextId(), "", NodeType::SimpleCond, outsideId,ImColor(128, 195, 248));
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Function, NewTextBuffer(BufferType::Empty));
        //An option for user choice of condition from menu
        m_Nodes.back().Inputs.back().PinButton = new Button("Condition");
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "IF", PinType::Function, NewTextBuffer(BufferType::Empty));
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "ElSE", PinType::Function, NewTextBuffer(BufferType::Empty));
        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    /**
     * Creates node of code in Petri net.
     * @param outsideId  ID of outside node
     * @return           created node
     */
    Node* SpawnCodeNode(ed::NodeId outsideId)
    {
        m_Nodes.emplace_back(GetNextId(), "Code", NodeType::SimpleCode, outsideId,ImColor(128, 195, 248));

        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Function, NewTextBuffer(BufferType::Empty));
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Function, NewTextBuffer(BufferType::Empty));
        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    /**
     * Creates node of function.
     * @param outsideId  ID of outside node
     * @return           created node
     */
    Node* SpawnFunctionNode(ed::NodeId outsideId)
    {
        m_Nodes.emplace_back(GetNextId(), "Function", NodeType::Function, outsideId,ImColor(255,178,102));
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Function, NewTextBuffer(BufferType::Name));
        AddInsideNodeId(outsideId, m_Nodes.back().ID);
        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    /**
     * From imgui-node-editor-master.
     */
    void BuildNodes()
    {
        for (auto& node : m_Nodes)
            BuildNode(&node);
    }

    /**
     * From imgui-node-editor-master.
     * Preparation before GUI running.
     */
    void OnStart() override
    {
        ed::Config config;

        config.UserPointer = this;

        config.LoadNodeSettings = [](ed::NodeId nodeId, char* data, void* userPointer) -> size_t
        {
            auto self = static_cast<CASE_tool*>(userPointer);

            auto node = self->FindNode(nodeId);
            if (!node)
                return 0;

            if (data != nullptr)
                memcpy(data, node->State.data(), node->State.size());
            return node->State.size();
        };

        config.SaveNodeSettings = [](ed::NodeId nodeId, const char* data, size_t size, ed::SaveReasonFlags reason, void* userPointer) -> bool
        {
            auto self = static_cast<CASE_tool*>(userPointer);

            auto node = self->FindNode(nodeId);
            if (!node)
                return false;

            node->State.assign(data, size);

            self->TouchNode(nodeId);

            return true;
        };

        // create and prepare editor
        m_Editor = ed::CreateEditor(&config);
        ed::SetCurrentEditor(m_Editor);

        // create agent master and his internal nodes
        SpawnAgent(ImVec2(-300, 351));
        ed::NavigateToContent();

        BuildNodes();

        m_HeaderBackground = LoadTexture("data/RespAgentBackground.png");
        m_SaveIcon         = LoadTexture("data/ic_save_white_24dp.png");
        m_RestoreIcon      = LoadTexture("data/ic_restore_white_24dp.png");
    }

    /**
     * From imgui-node-editor-master.
     * End of the running GUI.
     */
    void OnStop() override
    {
        auto releaseTexture = [this](ImTextureID& id)
        {
            if (id)
            {
                DestroyTexture(id);
                id = nullptr;
            }
        };

        releaseTexture(m_RestoreIcon);
        releaseTexture(m_SaveIcon);
        releaseTexture(m_HeaderBackground);

        if (m_Editor)
        {
            ed::DestroyEditor(m_Editor);
            m_Editor = nullptr;
        }
    }

    /**
     * From imgui-node-editor-master.
     */
    ImColor GetIconColor(PinType type)
    {
        switch (type)
        {
            default:
            case PinType::Attribute:      return ImColor( 255,255,255); // white
            case PinType::Function:    return ImColor(51, 150, 215); // mass blue
            case PinType::Relationship:   return { 255, 255, 255}; // white
            case PinType::Service:    return ImColor(51, 150, 215); // mass blue
            case PinType::Reasoning:    return ImColor(255,255,255); // white
        }
    };

    /**
     * From imgui-node-editor-master.
     */
    void DrawPinIcon(const Pin& pin, bool connected, int alpha)
    {
        IconType iconType;
        ImColor  color = GetIconColor(pin.Type);
        color.Value.w = alpha / 255.0f;
        switch (pin.Type)
        {
            case PinType::Relationship:  iconType = IconType::Flow;   break;
            case PinType::Attribute:     iconType = IconType::Circle; break;
            case PinType::Function:      iconType = IconType::Circle; break;
            case PinType::Service:       iconType = IconType::Circle; break;
            case PinType::Reasoning:       iconType = IconType::Circle; break;
            default:
                return;
        }

        ax::Widgets::Icon(ImVec2(static_cast<float>(m_PinIconSize), static_cast<float>(m_PinIconSize)), iconType, connected, color, ImColor(32, 32, 32, alpha));
    };

    /**
     * From imgui-node-editor-master.
     */
    void ShowStyleEditor(bool* show = nullptr)
    {
        if (!ImGui::Begin("Style", show))
        {
            ImGui::End();
            return;
        }

        auto paneWidth = ImGui::GetContentRegionAvail().x;

        auto& editorStyle = ed::GetStyle();
        ImGui::BeginHorizontal("Style buttons", ImVec2(paneWidth, 0), 1.0f);
        ImGui::TextUnformatted("Values");
        ImGui::Spring();
        if (ImGui::Button("Reset to defaults"))
            editorStyle = ed::Style();
        ImGui::EndHorizontal();
        ImGui::Spacing();
        ImGui::DragFloat4("Node Padding", &editorStyle.NodePadding.x, 0.1f, 0.0f, 40.0f);
        ImGui::DragFloat("Node Rounding", &editorStyle.NodeRounding, 0.1f, 0.0f, 40.0f);
        ImGui::DragFloat("Node Border Width", &editorStyle.NodeBorderWidth, 0.1f, 0.0f, 15.0f);
        ImGui::DragFloat("Hovered Node Border Width", &editorStyle.HoveredNodeBorderWidth, 0.1f, 0.0f, 15.0f);
        ImGui::DragFloat("Hovered Node Border Offset", &editorStyle.HoverNodeBorderOffset, 0.1f, -40.0f, 40.0f);
        ImGui::DragFloat("Selected Node Border Width", &editorStyle.SelectedNodeBorderWidth, 0.1f, 0.0f, 15.0f);
        ImGui::DragFloat("Selected Node Border Offset", &editorStyle.SelectedNodeBorderOffset, 0.1f, -40.0f, 40.0f);
        ImGui::DragFloat("Pin Rounding", &editorStyle.PinRounding, 0.1f, 0.0f, 40.0f);
        ImGui::DragFloat("Pin Border Width", &editorStyle.PinBorderWidth, 0.1f, 0.0f, 15.0f);
        ImGui::DragFloat("Link Strength", &editorStyle.LinkStrength, 1.0f, 0.0f, 500.0f);
        ImGui::DragFloat("Scroll Duration", &editorStyle.ScrollDuration, 0.001f, 0.0f, 2.0f);
        ImGui::DragFloat("Flow Marker Distance", &editorStyle.FlowMarkerDistance, 1.0f, 1.0f, 200.0f);
        ImGui::DragFloat("Flow Speed", &editorStyle.FlowSpeed, 1.0f, 1.0f, 2000.0f);
        ImGui::DragFloat("Flow Duration", &editorStyle.FlowDuration, 0.001f, 0.0f, 5.0f);
        ImGui::DragFloat("Group Rounding", &editorStyle.GroupRounding, 0.1f, 0.0f, 40.0f);
        ImGui::DragFloat("Group Border Width", &editorStyle.GroupBorderWidth, 0.1f, 0.0f, 15.0f);

        ImGui::Separator();

        static ImGuiColorEditFlags edit_mode = ImGuiColorEditFlags_DisplayRGB;
        ImGui::BeginHorizontal("Color Mode", ImVec2(paneWidth, 0), 1.0f);
        ImGui::TextUnformatted("Filter Colors");
        ImGui::Spring();
        ImGui::RadioButton("RGB", &edit_mode, ImGuiColorEditFlags_DisplayRGB);
        ImGui::Spring(0);
        ImGui::RadioButton("HSV", &edit_mode, ImGuiColorEditFlags_DisplayHSV);
        ImGui::Spring(0);
        ImGui::RadioButton("HEX", &edit_mode, ImGuiColorEditFlags_DisplayHex);
        ImGui::EndHorizontal();

        static ImGuiTextFilter filter;
        filter.Draw("##filter", paneWidth);

        ImGui::Spacing();

        ImGui::PushItemWidth(-160);
        for (int i = 0; i < ed::StyleColor_Count; ++i)
        {
            auto name = ed::GetStyleColorName((ed::StyleColor)i);
            if (!filter.PassFilter(name))
                continue;

            ImGui::ColorEdit4(name, &editorStyle.Colors[i].x, edit_mode);
        }
        ImGui::PopItemWidth();

        ImGui::End();
    }

    /**
     * From imgui-node-editor-master.
     */
    void ShowLeftPane(float paneWidth)
    {
        auto& io = ImGui::GetIO();

        ImGui::BeginChild("Selection", ImVec2(paneWidth, 0));

        paneWidth = ImGui::GetContentRegionAvail().x;

        static bool showStyleEditor = false;
        ImGui::BeginHorizontal("Style Editor", ImVec2(paneWidth, 0));
        ImGui::Spring(0.0f, 0.0f);
        if (ImGui::Button("Zoom to Content"))
            ed::NavigateToContent();
        ImGui::Spring(0.0f);
        ImGui::EndHorizontal();

        if (showStyleEditor)
            ShowStyleEditor(&showStyleEditor);

        ImGui::GetWindowDrawList()->AddRectFilled(
                ImGui::GetCursorScreenPos(),
                ImGui::GetCursorScreenPos() + ImVec2(paneWidth, ImGui::GetTextLineHeight()),
                ImColor(ImGui::GetStyle().Colors[ImGuiCol_HeaderActive]), ImGui::GetTextLineHeight() * 0.25f);
        ImGui::Spacing(); ImGui::SameLine();
        ImGui::TextUnformatted("Nodes");
        ImGui::Indent();
        ShowLeftPaneNodes();
        ImGui::Unindent();

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Z)))
            for (auto& link : m_Links)
                ed::Flow(link.ID);

        ImGui::EndChild();
    }

    /**
     * @brief Shows nodes in the left pane of the interface.
     *
     * This method iterates through the nodes stored in m_Nodes and displays those
     * of type NodeType::ExtAgent in the left pane using DepthSearching().
     */
    void ShowLeftPaneNodes() {
        for (auto& node : m_Nodes)
        {
            if (node.Type != NodeType::ExtAgent) {
                continue;
            }
            DepthSearching(node, ImVec2(0,0));
        }
    }

    /**
     * @brief Recursively performs depth-first search starting from the given node.
     *
     * This method processes the given node and then recursively searches through its
     * child nodes, adjusting their position with each level of depth.
     *
     * @param node The starting node for the depth-first search.
     * @param shift The amount of shift to apply to the node's position.
     */
    void DepthSearching(Node& node, ImVec2 shift) {
        DoWithNode(node, shift);
        if (node.InsideIds.size() < 0)
            return;
        shift = ImVec2(shift.x + 15,0);
        for (auto& id : node.InsideIds) {
            Node* insideNode = FindNode(id);
            DepthSearching(*insideNode, shift);
        }
    }

    /**
     * Display node text and provide control over its selection.
     * @param node      input node
     * @param shift     shift of node from left side of the panel
     */
    void DoWithNode(Node& node, const ImVec2& shift) {
        ImGui::PushID(node.ID.AsPointer());
        auto start = ImGui::GetCursorScreenPos();
        bool isSelected;
# if IMGUI_VERSION_NUM >= 18967
        ImGui::SetNextItemAllowOverlap();
# endif
        if (ImGui::Selectable((node.Name + "##" + std::to_string(reinterpret_cast<uintptr_t>(node.ID.AsPointer()))).c_str(), &isSelected, 0, ImVec2(0,0), shift))
        {
            if (node.Type == NodeType::ExtAgent) {
                m_Inside = 0;
                ed::SelectNode(node.ID, false);
            } else {
                m_Inside = node.OutsideId;
                ed::SelectNode(node.ID, false);
            }
            ed::NavigateToSelection();
        }
        auto drawList = ImGui::GetWindowDrawList();
        ImGui::PopID();
    }

    /**
     * From imgui-node-editor-master.
     * Show inputs of blueprint and simple nodes.
     */
    void BlueprintAndSimpleInputs(Node& node, Pin* newLinkPin, util::BlueprintNodeBuilder &builder) {
        for (auto &input: node.Inputs)
        {
            auto alpha = ImGui::GetStyle().Alpha;
            if (newLinkPin && !CanCreateLink(newLinkPin, &input) && &input != newLinkPin)
                alpha = alpha * (48.0f / 255.0f);

            builder.Input(input.ID, input.IsActive);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
            DrawPinIcon(input, IsPinLinked(input.ID), (int) (alpha * 255));
            ImGui::Spring(0);

            if (input.PinBuffer->Type != BufferType::Empty) {
                static bool wasActive = false;

                ImGui::PushItemWidth(100.0f);
                ImGui::InputText("##edit", input.PinBuffer->Buffer, 127);
                ImGui::PopItemWidth();

                if (ImGui::IsItemActive() && !wasActive) {
                    ed::EnableShortcuts(false);
                    wasActive = true;
                } else if (!ImGui::IsItemActive() && wasActive) {
                    ed::EnableShortcuts(true);
                    wasActive = false;
                }
                ImGui::Spring(0);
            }

            if (!input.Name.empty())
            {
                ImGui::TextUnformatted(input.Name.c_str());
                ImGui::Spring(0);
            }
            ImGui::PopStyleVar();

            //Button definition for condition node
            if (node.Type == NodeType::SimpleCond) {
                if (ImGui::Button(input.PinButton->Label)) {
                    m_ActiveButton = input.PinButton;
                }
            }
            builder.EndInput();
        }
    }

    /**
     * From imgui-node-editor-master.
     * Show outputs of blueprint and simple nodes.
     */
    void BlueprintAndSimpleOutputs(Node& node, Pin* newLinkPin, util::BlueprintNodeBuilder& builder) {
        for (auto& output : node.Outputs)
        {
            auto alpha = ImGui::GetStyle().Alpha;
            if (newLinkPin && !CanCreateLink(newLinkPin, &output) && &output != newLinkPin)
                alpha = alpha * (48.0f / 255.0f);

            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
            builder.Output(output.ID, output.IsActive);
            if (output.PinBuffer->Type != BufferType::Empty) {
                static bool wasActive = false;

                ImGui::PushItemWidth(100.0f);
                ImGui::InputText("##edit", output.PinBuffer->Buffer, 127);
                ImGui::PopItemWidth();
                if (ImGui::IsItemActive() && !wasActive) {
                    ed::EnableShortcuts(false);
                    wasActive = true;
                } else if (!ImGui::IsItemActive() && wasActive) {
                    ed::EnableShortcuts(true);
                    wasActive = false;
                }
                ImGui::Spring(0);
            }
            if (!output.Name.empty())
            {
                ImGui::Spring(0);
                ImGui::TextUnformatted(output.Name.c_str());
            }
            ImGui::Spring(0);
            DrawPinIcon(output, IsPinLinked(output.ID), (int)(alpha * 255));
            ImGui::PopStyleVar();
            builder.EndOutput();
        }
    }

    /**
     * From imgui-node-editor-master.
     * During GUI running.
     */
    void OnFrame(float deltaTime) override {
        UpdateTouch();
        ed::SetCurrentEditor(m_Editor);

# if 0
        {
            for (auto x = -io.DisplaySize.y; x < io.DisplaySize.x; x += 10.0f)
            {
                ImGui::GetWindowDrawList()->AddLine(ImVec2(x, 0), ImVec2(x + io.DisplaySize.y, io.DisplaySize.y),
                    IM_COL32(255, 255, 0, 255));
            }
        }
# endif

        static ed::NodeId contextNodeId = 0;
        static ed::LinkId contextLinkId = 0;
        static ed::PinId contextPinId = 0;
        static bool createNewNode = false;
        static Pin *newNodeLinkPin = nullptr;
        static Pin *newLinkPin = nullptr;

        static float leftPaneWidth = 400.0f;
        static float rightPaneWidth = 800.0f;
        Splitter(true, 4.0f, &leftPaneWidth, &rightPaneWidth, 50.0f, 50.0f);
        ShowLeftPane(leftPaneWidth - 4.0f);

        ImGui::SameLine(0.0f, 12.0f);

        ed::Begin("Node editor");
        {
            auto cursorTopLeft = ImGui::GetCursorScreenPos();

            util::BlueprintNodeBuilder builder(m_HeaderBackground, GetTextureWidth(m_HeaderBackground),
                                               GetTextureHeight(m_HeaderBackground));

            // create blueprint and simple nodes
            for (auto &node: m_Nodes) {
                if (node.Type == NodeType::ExtAgent
                    || m_Inside.Get() == 0 || node.OutsideId.Get() != m_Inside.Get())
                    continue;
                builder.Begin(node.ID);
                bool isSimple = node.Type == NodeType::SimpleCond|| node.Type == NodeType::SimpleCode;
                if (!isSimple) {
                    builder.Header(node.Color);
                    ImGui::Spring(0);
                    ImGui::TextUnformatted(node.Name.c_str());
                    ImGui::Spring(1);
                    ImGui::Dummy(ImVec2(0, 28));

                    ImGui::Spring(0);
                    builder.EndHeader();
                }
                BlueprintAndSimpleInputs(node, newLinkPin, builder);

                if (isSimple) {
                    builder.Middle();

                    ImGui::Spring(1, 0);
                    ImGui::TextUnformatted(node.Name.c_str());
                    ImGui::Spring(1, 0);
                }

                BlueprintAndSimpleOutputs(node, newLinkPin, builder);

                builder.End();
            }

            // create tree nodes
            for (auto &node: m_Nodes) {
                if (node.Type != NodeType::ExtAgent || m_Inside != ed::NodeId(0))
                    continue;

                const float rounding = 5.0f;
                const float padding = 12.0f;

                const auto pinBackground = ed::GetStyle().Colors[ed::StyleColor_NodeBg];

                ed::PushStyleColor(ed::StyleColor_NodeBg, ImColor(128, 128, 128, 200));
                ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(32, 32, 32, 200));
                ed::PushStyleColor(ed::StyleColor_PinRect, ImColor(60, 180, 255, 150));
                ed::PushStyleColor(ed::StyleColor_PinRectBorder, ImColor(60, 180, 255, 150));

                ed::PushStyleVar(ed::StyleVar_NodePadding, ImVec4(0, 0, 0, 0));
                ed::PushStyleVar(ed::StyleVar_NodeRounding, rounding);
                ed::PushStyleVar(ed::StyleVar_SourceDirection, ImVec2(0.0f, 1.0f));
                ed::PushStyleVar(ed::StyleVar_TargetDirection, ImVec2(0.0f, -1.0f));
                ed::PushStyleVar(ed::StyleVar_LinkStrength, 0.0f);
                ed::PushStyleVar(ed::StyleVar_PinBorderWidth, 1.0f);
                ed::PushStyleVar(ed::StyleVar_PinRadius, 5.0f);
                ed::BeginNode(node.ID);

                ImGui::BeginVertical(node.ID.AsPointer());
                ImGui::BeginHorizontal("inputs");
                ImGui::Spring(0, padding * 2);

                ImRect inputsRect;
                int inputAlpha = 200;
                if (!node.Inputs.empty()) {
                    auto &pin = node.Inputs[0];
                    ImGui::Dummy(ImVec2(0, padding));
                    ImGui::Spring(1, 0);
                    inputsRect = ImGui_GetItemRect();

                    ed::PushStyleVar(ed::StyleVar_PinArrowSize, 10.0f);
                    ed::PushStyleVar(ed::StyleVar_PinArrowWidth, 10.0f);
#if IMGUI_VERSION_NUM > 18101
                    ed::PushStyleVar(ed::StyleVar_PinCorners, ImDrawFlags_RoundCornersBottom);
#else
                    ed::PushStyleVar(ed::StyleVar_PinCorners, 12);
#endif
                    ed::BeginPin(pin.ID, ed::PinKind::Input);
                    ed::PinPivotRect(inputsRect.GetTL(), inputsRect.GetBR());
                    ed::PinRect(inputsRect.GetTL(), inputsRect.GetBR());
                    ed::EndPin();
                    ed::PopStyleVar(3);

                    if (newLinkPin && !CanCreateLink(newLinkPin, &pin) && &pin != newLinkPin)
                        inputAlpha = (int) (255 * ImGui::GetStyle().Alpha * (48.0f / 255.0f));
                } else
                    ImGui::Dummy(ImVec2(0, padding));

                ImGui::Spring(0, padding * 2);
                ImGui::EndHorizontal();

                ImGui::BeginHorizontal("content_frame");
                ImGui::Spring(1, padding);

                ImGui::BeginVertical("content", ImVec2(0.0f, 0.0f));
                ImGui::Dummy(ImVec2(160, 0));
                ImGui::Spring(1);
                ImGui::TextUnformatted(node.Name.c_str());
                ImGui::Spring(1);
                ImGui::EndVertical();
                auto contentRect = ImGui_GetItemRect();

                ImGui::Spring(1, padding);
                ImGui::EndHorizontal();

                ImGui::BeginHorizontal("outputs");
                ImGui::Spring(0, padding * 2);

                ImRect outputsRect;
                int outputAlpha = 200;
                if (!node.Outputs.empty()) {
                    auto &pin = node.Outputs[0];
                    ImGui::Dummy(ImVec2(0, padding));
                    ImGui::Spring(1, 0);
                    outputsRect = ImGui_GetItemRect();

#if IMGUI_VERSION_NUM > 18101
                    ed::PushStyleVar(ed::StyleVar_PinCorners, ImDrawFlags_RoundCornersTop);
#else
                    ed::PushStyleVar(ed::StyleVar_PinCorners, 3);
#endif
                    ed::BeginPin(pin.ID, ed::PinKind::Output);
                    ed::PinPivotRect(outputsRect.GetTL(), outputsRect.GetBR());
                    ed::PinRect(outputsRect.GetTL(), outputsRect.GetBR());
                    ed::EndPin();
                    ed::PopStyleVar();

                    if (newLinkPin && !CanCreateLink(newLinkPin, &pin) && &pin != newLinkPin)
                        outputAlpha = (int) (255 * ImGui::GetStyle().Alpha * (48.0f / 255.0f));
                } else
                    ImGui::Dummy(ImVec2(0, padding));

                ImGui::Spring(0, padding * 2);
                ImGui::EndHorizontal();

                ImGui::EndVertical();

                ed::EndNode();
                ed::PopStyleVar(7);
                ed::PopStyleColor(4);

                auto drawList = ed::GetNodeBackgroundDrawList(node.ID);

#if IMGUI_VERSION_NUM > 18101
                const auto topRoundCornersFlags = ImDrawFlags_RoundCornersTop;
                const auto bottomRoundCornersFlags = ImDrawFlags_RoundCornersBottom;
#else
                const auto    topRoundCornersFlags = 1 | 2;
                const auto bottomRoundCornersFlags = 4 | 8;
#endif

                drawList->AddRectFilled(inputsRect.GetTL() + ImVec2(0, 1), inputsRect.GetBR(),
                                        IM_COL32((int) (255 * pinBackground.x), (int) (255 * pinBackground.y),
                                                 (int) (255 * pinBackground.z), inputAlpha), 4.0f,
                                        bottomRoundCornersFlags);
                drawList->AddRect(inputsRect.GetTL() + ImVec2(0, 1), inputsRect.GetBR(),
                                  IM_COL32((int) (255 * pinBackground.x), (int) (255 * pinBackground.y),
                                           (int) (255 * pinBackground.z), inputAlpha), 4.0f, bottomRoundCornersFlags);
                drawList->AddRectFilled(outputsRect.GetTL(), outputsRect.GetBR() - ImVec2(0, 1),
                                        IM_COL32((int) (255 * pinBackground.x), (int) (255 * pinBackground.y),
                                                 (int) (255 * pinBackground.z), outputAlpha), 4.0f,
                                        topRoundCornersFlags);
                drawList->AddRect(outputsRect.GetTL(), outputsRect.GetBR() - ImVec2(0, 1),
                                  IM_COL32((int) (255 * pinBackground.x), (int) (255 * pinBackground.y),
                                           (int) (255 * pinBackground.z), outputAlpha), 4.0f, topRoundCornersFlags);
                drawList->AddRectFilled(contentRect.GetTL(), contentRect.GetBR(), IM_COL32(24, 64, 128, 200), 0.0f);
                drawList->AddRect(
                        contentRect.GetTL(),
                        contentRect.GetBR(),
                        IM_COL32(48, 128, 255, 100), 0.0f);
            }

            // create links
            for (auto &link: m_Links)
                ed::Link(link.ID, link.StartPinID, link.EndPinID, link.Color, 2.0f);

            if (!createNewNode) {
                if (ed::BeginCreate(ImColor(255, 255, 255), 2.0f)) {
                    auto showLabel = [](const char *label, ImColor color) {
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetTextLineHeight());
                        auto size = ImGui::CalcTextSize(label);

                        auto padding = ImGui::GetStyle().FramePadding;
                        auto spacing = ImGui::GetStyle().ItemSpacing;

                        ImGui::SetCursorPos(ImGui::GetCursorPos() + ImVec2(spacing.x, -spacing.y));

                        auto rectMin = ImGui::GetCursorScreenPos() - padding;
                        auto rectMax = ImGui::GetCursorScreenPos() + size + padding;

                        auto drawList = ImGui::GetWindowDrawList();
                        drawList->AddRectFilled(rectMin, rectMax, color, size.y * 0.15f);
                        ImGui::TextUnformatted(label);
                    };

                    ed::PinId startPinId = 0, endPinId = 0;
                    if (ed::QueryNewLink(&startPinId, &endPinId)) {
                        auto startPin = FindPin(startPinId);
                        auto endPin = FindPin(endPinId);

                        newLinkPin = startPin ? startPin : endPin;

                        if (startPin->Kind == PinKind::Input) {
                            std::swap(startPin, endPin);
                            std::swap(startPinId, endPinId);
                        }

                        if (startPin && endPin) {
                            if (endPin == startPin) {
                                ed::RejectNewItem(ImColor(255, 0, 0), 2.0f);
                            } else if (endPin->Kind == startPin->Kind) {
                                showLabel("x Incompatible Pin Kind", ImColor(45, 32, 32, 180));
                                ed::RejectNewItem(ImColor(255, 0, 0), 2.0f);
                            } else if (endPin->Type != startPin->Type) {
                                showLabel("x Incompatible Pin Type", ImColor(45, 32, 32, 180));
                                ed::RejectNewItem(ImColor(255, 128, 128), 1.0f);
                            } else {
                                showLabel("+ Create Link", ImColor(32, 45, 32, 180));
                                if (ed::AcceptNewItem(ImColor(128, 255, 128), 4.0f)) {
                                    m_Links.emplace_back(Link(GetNextId(), startPinId, endPinId));
                                    m_Links.back().Color = GetIconColor(startPin->Type);
                                    // add link to its associated pins
                                    AddLinkToPin(startPinId, m_Links.back().ID);
                                    AddLinkToPin(endPinId, m_Links.back().ID);
                                }
                            }
                        }
                    }

                    ed::PinId pinId = 0;
                    if (ed::QueryNewNode(&pinId)) {
                        newLinkPin = FindPin(pinId);
                        if (newLinkPin)
                            showLabel("+ Create Node", ImColor(32, 45, 32, 180));

                        if (ed::AcceptNewItem()) {
                            createNewNode = true;
                            newNodeLinkPin = FindPin(pinId);
                            newLinkPin = nullptr;
                            ed::Suspend();
                            ImGui::OpenPopup("Create New Node");
                            ed::Resume();
                        }
                    }
                } else
                    newLinkPin = nullptr;

                ed::EndCreate();

                if (ed::BeginDelete()) {
                    std::vector<ed::NodeId> deletedNodes;
                    ed::NodeId nodeId = 0;
                    bool deleted = false;
                    while (ed::QueryDeletedNode(&nodeId)) {
                        if (ed::AcceptDeletedItem()) {
                            deleted = true;
                            // delete all nodes that are associated with deleted node
                            // and all associated links
                            // user cannot delete main agent
                            if (nodeId.Get() != MANAGER_AGENT_ID)
                                DeleteNode(nodeId);
                        }
                    }


                    ed::LinkId linkId = 0;
                    while (ed::QueryDeletedLink(&linkId)) {
                        // delete link only it it hasn't been already deleted by node
                        if (!deleted && ed::AcceptDeletedItem()) {
                            auto id = std::find_if(m_Links.begin(), m_Links.end(),
                                                   [linkId](auto &link) { return link.ID == linkId; });
                            if (id != m_Links.end()) {
                                Link *link = FindLink(linkId);
                                Pin *pin = FindPin(link->StartPinID);
                                // delete link id from pin
                                DeleteLink(*pin);
                                pin = FindPin(link->EndPinID);
                                // delete link in from pin
                                DeleteLink(*pin);
                            }
                        }
                    }
                }
                ed::EndDelete();
            }

            ImGui::SetCursorScreenPos(cursorTopLeft);
        }

# if 1
        ed::Suspend();
        // control if user has made double click
        // if double click was activated, we change level of nodes
        if (ed::GoInsertNode(&contextNodeId)) {
            // id of marked node
            m_ContextNodeId = contextNodeId.Get();
            if (m_ContextNodeId.Get() == 0) {
                // outside view to agent structure
                m_Inside = 0;
            } else {
                Node *node = FindNode(contextNodeId);
                if (node->Type == NodeType::ExtAgent || node->Type == NodeType::RespAgent ||
                    node->Type == NodeType::RespReasoningReactive || node->Type == NodeType::RespReasoningIntelligent) {
                    // inside view to agent
                    m_Inside = node->ID;
                } else {
                    // back to inside view of agent
                    Node *outsideNode = FindNode(node->OutsideId);
                    if (outsideNode->OutsideId.Get() == 0) {
                        m_Inside = 0;
                    } else {
                        m_Inside = outsideNode->OutsideId;
                    }
                }
            }
        }
        ed::Resume();
        auto openPopupPosition = ImGui::GetMousePos();
        ed::Suspend();
        if (ed::ShowNodeContextMenu(&contextNodeId))
            ImGui::OpenPopup("Node Context Menu");
        else if (ed::ShowPinContextMenu(&contextPinId))
            ImGui::OpenPopup("Pin Context Menu");
        else if (ed::ShowLinkContextMenu(&contextLinkId))
            ImGui::OpenPopup("Link Context Menu");
        else if (ed::ShowBackgroundContextMenu()) {
            ImGui::OpenPopup("Create New Node");
            newNodeLinkPin = nullptr;
        } else if (m_ActiveButton) {
            ImGui::OpenPopup("Conditions");
        }
        ed::Resume();

        ed::Suspend();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
        if (ImGui::BeginPopup("Node Context Menu")) {
            auto node = FindNode(contextNodeId);
            if (ImGui::MenuItem("Delete"))
                ed::DeleteNode(contextNodeId);
            ImGui::EndPopup();
        }

        //TODO: definition condition for petri net
        if (ImGui::BeginPopup("Conditions")) {
            if (ImGui::MenuItem("Conditions1")) {
                SetButtonLabel(m_ActiveButton, "Conditions1");
                m_ActiveButton = nullptr;
            }
            if (ImGui::MenuItem("Conditions2")) {
                SetButtonLabel(m_ActiveButton, "Conditions2");
                m_ActiveButton = nullptr;
            }
            if (ImGui::MenuItem("Conditions3")) {
                SetButtonLabel(m_ActiveButton, "Conditions3");
                m_ActiveButton = nullptr;
            }
            ImGui::EndPopup();
        }


        if (ImGui::BeginPopup("Pin Context Menu")) {
            auto pin = FindPin(contextPinId);

            ImGui::TextUnformatted("Pin Context Menu");
            ImGui::Separator();
            if (pin) {
                ImGui::Text("ID: %p", pin->ID.AsPointer());
                if (pin->Node)
                    ImGui::Text("Node: %p", pin->Node->ID.AsPointer());
                else
                    ImGui::Text("Node: %s", "<none>");
            } else
                ImGui::Text("Unknown pin: %p", contextPinId.AsPointer());

            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("Link Context Menu")) {
            auto link = FindLink(contextLinkId);

            ImGui::TextUnformatted("Link Context Menu");
            ImGui::Separator();
            if (link) {
                ImGui::Text("ID: %p", link->ID.AsPointer());
                ImGui::Text("From: %p", link->StartPinID.AsPointer());
                ImGui::Text("To: %p", link->EndPinID.AsPointer());
            } else
                ImGui::Text("Unknown link: %p", contextLinkId.AsPointer());
            ImGui::Separator();
            if (ImGui::MenuItem("Delete"))
                ed::DeleteLink(contextLinkId);
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("Create New Node")) {
            auto newNodePostion = openPopupPosition;
            Node *node = nullptr;
            if (m_Inside.Get() == 0) {
                // outside view to agents structure
                // user can only create new agent
                if (ImGui::MenuItem("Agent"))
                    SpawnAgent(newNodePostion);
            } else {
                Node *node = FindNode(m_Inside);
                // level of agent's responsibilities
                if (node->Type == NodeType::ExtAgent) {
                    if (ImGui::MenuItem("Service")) {
                        SpawnServiceIdNode(newNodePostion, node->ID);
                    }
                    if (ImGui::MenuItem("Reactive")) {
                        SpawnReactiveReasoningNode(newNodePostion, node->ID);
                    }
                    if (ImGui::MenuItem("Intelligent")) {
                        SpawnIntelligentReasoningNode(newNodePostion, node->ID);
                    }
                } else if (node->Type == NodeType::RespAgent) {
                    //level of agent's features
                    if (ImGui::MenuItem("Attribute")) {
                        node = SpawnAttributeNode(node->ID);
                    }
                } else if (node->Type == NodeType::RespReasoningReactive) {
                    //level of agent's reactive reasoning
                    if (ImGui::MenuItem("Function")) {
                        node = SpawnFunctionNode(node->ID);
                    }
                } else if (node->Type == NodeType::RespReasoningIntelligent) {
                    // level of agent's intelligent reasoning
                    if (ImGui::MenuItem("Condition")) {
                        node = SpawnConditionNode(node->ID);
                    }
                    if (ImGui::MenuItem("Code")) {
                        node = SpawnCodeNode(node->ID);
                    }
                    if (ImGui::MenuItem("Function")) {
                        node = SpawnFunctionNode(node->ID);
                    }
                }
            }
            // in each level can user made step back - step to higher level
            if (ImGui::MenuItem("Back")) {
                //step back
                if (m_Inside.Get() != 0) {
                    Node *nodeInside = FindNode(m_Inside);
                    if (nodeInside->Type != NodeType::ExtAgent)
                        m_Inside = (FindNode(nodeInside->OutsideId))->ID;
                    else
                        m_Inside = 0;
                }
            }

            if (node) {
                BuildNodes();
                createNewNode = false;
                ed::SetNodePosition(node->ID, newNodePostion);
                if (auto startPin = newNodeLinkPin) {
                    auto &pins = startPin->Kind == PinKind::Input ? node->Outputs : node->Inputs;

                    for (auto &pin: pins) {
                        if (CanCreateLink(startPin, &pin)) {
                            auto endPin = &pin;
                            if (startPin->Kind == PinKind::Input)
                                std::swap(startPin, endPin);

                            m_Links.emplace_back(Link(GetNextId(), startPin->ID, endPin->ID));
                            m_Links.back().Color = GetIconColor(startPin->Type);
                            AddLinkToPin(startPin->ID, m_Links.back().ID);
                            AddLinkToPin(endPin->ID, m_Links.back().ID);
                            break;
                        }
                    }
                }
            }
            ImGui::EndPopup();
            }
            else
                createNewNode = false;
            ImGui::PopStyleVar();
            ed::Resume();
    # endif

        ed::End();

        auto editorMin = ImGui::GetItemRectMin();
        auto editorMax = ImGui::GetItemRectMax();
    }

    /**
     * Delete node and all associated nodes.
     * @param nodeId deleted node id
     */
    void DeleteNode(ed::NodeId nodeId) {
        // find deleted node
        Node* node = FindNode(nodeId);
        // prevents to never ending loop in deleting
        node->Deleted = true;
        // if deleted node is responsible or internal agent, remove the whole agent
        if (node->Type == NodeType::RespAgent || node->Type == NodeType::IntAgent) {
            ed::NodeId outsideId = node->OutsideId;
            Node* outsideNode = FindNode(outsideId);
            if (!outsideNode->Deleted) {
                outsideNode->Deleted = true;
                if (outsideNode->Type == NodeType::RespAgent) {
                    outsideId = outsideNode->OutsideId;
                    outsideNode = FindNode(outsideId);
                    if (!outsideNode->Deleted) {
                        outsideNode->Deleted = true;
                    }
                }
                node = outsideNode;
                nodeId = outsideId;
            }
        }
        // if node is Service, delete service node that is associated with this node
        if (node->Type == NodeType::RespService || node->Type == NodeType::ReasService) {
            for (ed::NodeId id : node->AssociatedIds) {
                Node *associatedNode = FindNode(id);
                if (!associatedNode->Deleted) {
                    DeleteNode(id);
                }
            }
        }
        // if node is associated by other node, delete them as first
        if (node->InsideIds.size() != 0) {
            //delete all inside nodes
            for (auto &id: node->InsideIds)
                DeleteNode(id);
        }
        // delete node links
        for(Pin& pin: node->Inputs) {
            DeleteLink(pin);
        }
        for(Pin& pin: node->Outputs) {
            DeleteLink(pin);
        }
        //delete node id from outside node
        if (node->OutsideId.Get() != 0) {
            Node* outsideNode = FindNode(node->OutsideId);
            auto id = std::find_if(outsideNode->InsideIds.begin(), outsideNode->InsideIds.end(),
                                   [nodeId](auto &insideId) { return insideId == nodeId; });
            if (id != outsideNode->InsideIds.end())
                outsideNode->InsideIds.erase(id);
        }
        //delete node
        //if node is ext agent, go up
        if (node->Type == NodeType::ExtAgent)
            m_Inside = 0;
        auto id = std::find_if(m_Nodes.begin(), m_Nodes.end(),
                               [nodeId](auto &node) { return node.ID == nodeId; });
        if (id != m_Nodes.end()) {
            m_Nodes.erase(id);
        }
    }

    /**
     * Delete links associated from pin.
     * We have to delete link ids from all ossiciated pins too.
     * @param pin
     */
    void DeleteLink(Pin& pin) {
        //loop over all link id assocaited with the pin
        for (auto& linkId : pin.LinkIds) {
            auto id = std::find_if(m_Links.begin(), m_Links.end(),
                                   [linkId](auto &link) { return link.ID == linkId; });
            if (id != m_Links.end()) {
                //find link
                Link* link = FindLink(linkId);
                //delete link id from associated pin
                if (link->StartPinID.Get() != linkId.Get()) {
                    Pin* otherPin = FindPin(link->StartPinID);
                    DeleteLinkId(otherPin, linkId);
                } else {
                    Pin* otherPin = FindPin(link->EndPinID);
                    DeleteLinkId(otherPin, linkId);
                }
                m_Links.erase(id);
            }
        }
    }

    /**
     * Delete link id from pin list od its associated links.
     * @param otherPin pin id from that we delete link id
     * @param linkId    deleted link id
     */
    void DeleteLinkId(Pin* otherPin, ed::LinkId linkId) {
        auto otherId = std::find_if(otherPin->LinkIds.begin(), otherPin->LinkIds.end(),
                                    [linkId](auto &otherLinkId) { return otherLinkId == linkId; });
        otherPin->LinkIds.erase(otherId);
    }

    /**
     * Add node to its outside node.
     * @param outsideId outside node id
     * @param insideId  added node id
     */
    void AddInsideNodeId(ed::NodeId outsideId, ed::NodeId insideId) {
        Node* outsideNode = FindNode(outsideId);
        outsideNode->InsideIds.push_back(insideId);
    }

    /**
     * Add link id to list in its associated pin.
     * @param pinId     associated pin id
     * @param linkId    added link id
     */
    void AddLinkToPin(ed::PinId pinId, ed::LinkId linkId) {
        Pin* pin = FindPin(pinId);
        pin->LinkIds.push_back(linkId);
    }

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
};

int Main(int argc, char** argv)
{
    CASE_tool tool("Agent simulation library", argc, argv);

    if (tool.Create())
        return tool.Run();

    return 0;
}