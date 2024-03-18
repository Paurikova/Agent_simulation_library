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

static inline ImRect ImGui_GetItemRect()
{
    return ImRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
}

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
};

enum class PinKind
{
    Output,
    Input
};

enum class NodeType
{
    Agent,
    Function,
    Attribute,
};

struct Node;

struct Pin
{
    ed::PinId   ID;
    ::Node*     Node;
    std::string Name;
    PinType     Type;
    PinKind     Kind;

    Pin(int id, const char* name, PinType type):
            ID(id), Node(nullptr), Name(name), Type(type), Kind(PinKind::Input)
    {
    }
};

struct Node
{
    ed::NodeId ID;
    std::string Name;
    std::vector<Pin> Inputs;
    std::vector<Pin> Outputs;
    ImColor Color;
    NodeType Type;
    ImVec2 Size;

    std::string State;
    std::string SavedState;

    Node(int id, const char* name, NodeType type, ImColor color = ImColor(255, 255, 255)):
            ID(id), Name(name), Color(color), Type(type), Size(0, 0)
    {
    }
};

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

struct NodeIdLess
{
    bool operator()(const ed::NodeId& lhs, const ed::NodeId& rhs) const
    {
        return lhs.AsPointer() < rhs.AsPointer();
    }
};

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

struct Example:
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
        if (!a || !b || a == b || a->Kind == b->Kind || a->Type != b->Type || a->Node == b->Node)
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

    Node* SpawnAgentNode()
    {
        m_Nodes.emplace_back(GetNextId(), "Agent", NodeType::Agent);
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "Attributes", PinType::Attribute);
        m_Nodes.back().Inputs.emplace_back(GetNextId(), "Functions", PinType::Function);
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "Relationships", PinType::Relationship);

        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    Node* SpawnFunctionNode()
    {
        m_Nodes.emplace_back(GetNextId(), "Function", NodeType::Function, ImColor(128, 195, 248));
        m_Nodes.back().Type = NodeType::Function;
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "Name", PinType::Function);

        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }

    Node* SpawnAttributeNode()
    {
        m_Nodes.emplace_back(GetNextId(), "Attribute", NodeType::Attribute, ImColor(128, 195, 248));
        m_Nodes.back().Type = NodeType::Attribute;
        //TODO:TU CHYBA ESTE TYP
        m_Nodes.back().Outputs.emplace_back(GetNextId(), "Name", PinType::Function);

        BuildNode(&m_Nodes.back());

        return &m_Nodes.back();
    }


    void BuildNodes()
    {
        for (auto& node : m_Nodes)
            BuildNode(&node);
    }

    void OnStart() override
    {
        ed::Config config;

        //TODO: toto asi netreba
        //config.SettingsFile = "Blueprints.json";

        config.UserPointer = this;

        config.LoadNodeSettings = [](ed::NodeId nodeId, char* data, void* userPointer) -> size_t
        {
            auto self = static_cast<Example*>(userPointer);

            auto node = self->FindNode(nodeId);
            if (!node)
                return 0;

            if (data != nullptr)
                memcpy(data, node->State.data(), node->State.size());
            return node->State.size();
        };

        config.SaveNodeSettings = [](ed::NodeId nodeId, const char* data, size_t size, ed::SaveReasonFlags reason, void* userPointer) -> bool
        {
            auto self = static_cast<Example*>(userPointer);

            auto node = self->FindNode(nodeId);
            if (!node)
                return false;

            node->State.assign(data, size);

            self->TouchNode(nodeId);

            return true;
        };

        m_Editor = ed::CreateEditor(&config);
        ed::SetCurrentEditor(m_Editor);

        Node* node;
        node = SpawnAgentNode();           ed::SetNodePosition(node->ID, ImVec2(-300, 351));
        node = SpawnFunctionNode();              ed::SetNodePosition(node->ID, ImVec2(-238, 504));
        node = SpawnAttributeNode();              ed::SetNodePosition(node->ID, ImVec2(-238, 504));

        ed::NavigateToContent();

        BuildNodes();

        m_HeaderBackground = LoadTexture("data/BlueprintBackground.png");
        m_SaveIcon         = LoadTexture("data/ic_save_white_24dp.png");
        m_RestoreIcon      = LoadTexture("data/ic_restore_white_24dp.png");
    }

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

    ImColor GetIconColor(PinType type)
    {
        switch (type)
        {
            default:
            case PinType::Flow:     return ImColor(255, 255, 255); //white
            case PinType::Bool:     return ImColor(220,  48,  48); //red
            case PinType::Int:      return ImColor( 68, 201, 156); //green
            case PinType::Functi:    return ImColor(147, 226,  74); //green
            case PinType::String:   return ImColor(124,  21, 153); //purpure
            case PinType::Relationship:   return ImColor( 51, 150, 215); //mass blue
            case PinType::Function: return ImColor(218,   0, 183); //pink
            case PinType::Delegate: return ImColor(255,  48,  48); //pink
        }
    };

    void DrawPinIcon(const Pin& pin, bool connected, int alpha)
    {
        IconType iconType;
        ImColor  color = GetIconColor(pin.Type);
        color.Value.w = alpha / 255.0f;
        switch (pin.Type)
        {
            case PinType::Flow:     iconType = IconType::Flow;   break;
            case PinType::Bool:     iconType = IconType::Circle; break;
            case PinType::Int:      iconType = IconType::Circle; break;
            case PinType::Float:    iconType = IconType::Circle; break;
            case PinType::String:   iconType = IconType::Circle; break;
            case PinType::Object:   iconType = IconType::Circle; break;
            case PinType::Function: iconType = IconType::Circle; break;
            case PinType::Delegate: iconType = IconType::Square; break;
            default:
                return;
        }

        ax::Widgets::Icon(ImVec2(static_cast<float>(m_PinIconSize), static_cast<float>(m_PinIconSize)), iconType, connected, color, ImColor(32, 32, 32, alpha));
    };

    int                  m_NextId = 1;
    const int            m_PinIconSize = 24;
    std::vector<Node>    m_Nodes;
    std::vector<Link>    m_Links;
    ImTextureID          m_HeaderBackground = nullptr;
    ImTextureID          m_SaveIcon = nullptr;
    ImTextureID          m_RestoreIcon = nullptr;
    const float          m_TouchTime = 1.0f;
    std::map<ed::NodeId, float, NodeIdLess> m_NodeTouchTime;
    bool                 m_ShowOrdinals = false;
};

int Main(int argc, char** argv)
{
    return 0;
}