#include "CASE_tool.h"

#include "imgui_internal.h"
#include "types.h"

static inline auto ImGui_GetItemRect() -> ImRect
{
    return { ImGui::GetItemRectMin(), ImGui::GetItemRectMax() };
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

TextBuffer::TextBuffer(BufferType type) : Type(type), Buffer{} {
    // Set the initialization text of Buffer based on the pin type
    switch (type) {
        case BufferType::Name:
            portable_strcpy(Buffer, "Name");
            break;
        case BufferType::Type:
            portable_strcpy(Buffer, "Type");
            break;
        case BufferType::InitValue:
            portable_strcpy(Buffer, "InitValue");
            break;
        case BufferType::ServiceId:
            portable_strcpy(Buffer, "ServiceId");
            break;
        case BufferType::Id:
            portable_strcpy(Buffer, "Id");
            break;
        default:
            portable_strcpy(Buffer, "Edit me");
            break;
    }
}

json TextBuffer::Serialize() const {
    return {
            { BUFFER_TYPE, static_cast<int>(Type) },  // Serialize enum as int
            { BUFFER_BUFFER, std::string(Buffer) }            // Convert char array to std::string
    };
}

TextBuffer::TextBuffer(const json& data) : Type(static_cast<BufferType>(data.at(BUFFER_TYPE).get<int>())), // Initialize Type
            Buffer{} // Initialize Buffer to an empty string
    {
    // Copy the buffer string from JSON data
    std::string bufferStr = data.at(BUFFER_BUFFER).get<std::string>();
    std::strncpy(Buffer, bufferStr.c_str(), sizeof(Buffer) - 1);
    Buffer[sizeof(Buffer) - 1] = '\0'; // Ensure null termination
}

Button::Button(std::string label): Label(label.c_str()) {}

json Button::Serialize() const {
    return {
            { BUTTON_LABEL, std::string(Label) } // Convert const char* to std::string
    };
}

Button::Button(const json& data): Label(data.at(BUTTON_LABEL).get<std::string>()){}

Pin::Pin(int id, const char* name, PinType type, TextBuffer* buffer, bool active):
        ID(id), NodeId(-1), Name(name), Type(type), Kind(PinKind::Input), PinBuffer(buffer), IsActive(active),
        PinButton{}
{
}

json Pin::Serialize() const {
    json jsonData = {
            {PIN_ID, ID.Get()},
            {PIN_NAME, Name},
            {PIN_TYPE, static_cast<int>(Type)},
            {PIN_KIND, static_cast<int>(Kind)},
            {PIN_IS_ACTIVE, IsActive},
            {PIN_LINK_IDS, json::array()},
            {PIN_BUFFER, PinBuffer->Serialize()}
    };
    // Populate LinkIds
    for (const auto& linkId : LinkIds) {
        jsonData[PIN_LINK_IDS].push_back(linkId.Get());
    }
    // Serialize PinButton if it exists
    if (PinButton) {
        jsonData[PIN_BUTTON] = PinButton->Serialize();
    }
    return jsonData;
}

Pin::Pin(const json& data, ed::NodeId nodeId) : ID(ed::PinId(data.at(PIN_ID).get<int>())),
                                                Name(data.at(PIN_NAME).get<std::string>()),
                                                Type(static_cast<PinType>(data.at(PIN_TYPE).get<int>())),
                                                IsActive(data.at(PIN_IS_ACTIVE).get<bool>()),
                                                NodeId(nodeId),
                                                LinkIds(), // Initialize LinkIds
                                                PinButton(nullptr) // Initialize PinButton
{
    // Create the TextBuffer from JSON
    PinBuffer = new TextBuffer(data.at(PIN_BUFFER)); // Assuming PinBuffer is a pointer

    // Deserialize LinkIds
    for (const auto& linkId : data.at(PIN_LINK_IDS)) {
        LinkIds.push_back(ed::LinkId(linkId.get<int>()));
    }
    // Deserialize PinButton if it exists
    if (data.contains(PIN_BUTTON)) {
        PinButton = new Button(data.at(PIN_BUTTON)); // Handle memory management
    }
}

Node::Node(int id, std::string name, NodeType type, ed::NodeId outsideId, ImColor color, AgentId_t agentId):
        ID(id), AgentId(agentId), Name(name), Color(color), Type(type), Size(0, 0), OutsideId(outsideId), Deleted(false)
{
}

json Node::Serialize() const {
    json jsonData = {
            {NODE_ID,             ID.Get()},
            {NODE_AGENT_ID,       AgentId},
            {NODE_NAME,           Name},
            {NODE_OUTSIDE_ID,     OutsideId.Get()},
            {NODE_COLOR,          {Color.Value.x,           Color.Value.y, Color.Value.z}},
            {NODE_TYPE,           static_cast<int>(Type)},
            {NODE_SIZE,           {Size.x,                  Size.y}},
            {NODE_DELETED,        Deleted},
            {NODE_INPUTS,         serializeVector(Inputs)},
            {NODE_OUTPUTS,        serializeVector(Outputs)},
            {NODE_INSIDE_IDS,     serializeNodeIds(InsideIds)},
            {NODE_ASSOCIATED_IDS, serializeNodeIds(AssociatedIds)},
            {NODE_POSITION,       {ed::GetNodePosition(ID).x, ed::GetNodePosition(ID).y}}
    };
    if (!State.empty()) {
        jsonData.push_back({NODE_STATE, State});
    }
    if (!SavedState.empty()) {
        jsonData.push_back({NODE_SAVED_STATE, SavedState});
    }
    return jsonData;
}

// Helper function to serialize a vector of Pins
json Node::serializeVector(const std::vector<Pin>& pins) const {
    json array = json::array();
    for (const auto& pin : pins) {
        array.push_back(pin.Serialize());
    }
    return array;
}

// Helper function to serialize a vector of Node IDs
json Node::serializeNodeIds(const std::vector<ed::NodeId>& ids) const {
    json array = json::array();
    for (const auto& id : ids) {
        array.push_back(id.Get());
    }
    return array;
}

Node::Node(const json& data)
        : ID(ed::NodeId(data.at(NODE_ID).get<int>())),
          AgentId(data.at(NODE_AGENT_ID).get<AgentId_t>()),
          Name(data.at(NODE_NAME).get<std::string>()),
          OutsideId(ed::NodeId(data.at(NODE_OUTSIDE_ID).get<int>())),
          Color(ImColor(data.at(NODE_COLOR)[0].get<float>(),
                        data.at(NODE_COLOR)[1].get<float>(),
                        data.at(NODE_COLOR)[2].get<float>())),
          Type(static_cast<NodeType>(data.at(NODE_TYPE).get<int>())),
          Deleted(data.at(NODE_DELETED).get<bool>()),
          Size({data.at(NODE_SIZE)[0].get<float>(), data.at(NODE_SIZE)[1].get<float>()})
{
    if (data.contains(NODE_STATE)) {
        State = data.at(NODE_STATE).get<std::string>();

    }
    if (data.contains(NODE_SAVED_STATE)) {
        SavedState = data.at(NODE_SAVED_STATE).get<std::string>();

    }
    // Deserialize Inputs
    for (const auto& pinData : data.at(NODE_INPUTS)) {
        Inputs.push_back(Pin(pinData, ID)); // Assuming Pin has a fromJson method
    }

    // Deserialize Outputs
    for (const auto& pinData : data.at(NODE_OUTPUTS)) {
        Outputs.push_back(Pin(pinData, ID)); // Assuming Pin has a fromJson method
    }

    // Deserialize InsideIds
    for (const auto& id : data.at(NODE_INSIDE_IDS)) {
        InsideIds.push_back(ed::NodeId(id.get<int>()));
    }

    // Deserialize AssociatedIds
    for (const auto& id : data.at(NODE_ASSOCIATED_IDS)) {
        AssociatedIds.push_back(ed::NodeId(id.get<int>()));
    }

    // Set node position
    ed::SetNodePosition(ID, ImVec2(data.at(NODE_POSITION)[0].get<float>(), data.at(NODE_POSITION)[1].get<float>()));
}

Link::Link(ed::LinkId id, ed::PinId startPinId, ed::PinId endPinId):
        ID(id), StartPinID(startPinId), EndPinID(endPinId), Color(255, 255, 255)
{
}

json Link::Serialize() const {
    return {
            {LINK_ID, ID.Get()},
            {LINK_START_PIN_ID, StartPinID.Get()},
            {LINK_END_PIN_ID, EndPinID.Get()},
            {LINK_COLOR, {Color.Value.x, Color.Value.y, Color.Value.z}} // Serialize ImColor as an array
    };
}

Link::Link(const json& data)
        : ID(ed::LinkId(data.at(LINK_ID).get<int>())),
          StartPinID(ed::PinId(data.at(LINK_START_PIN_ID).get<int>())),
          EndPinID(ed::PinId(data.at(LINK_END_PIN_ID).get<int>()))
{
    Color = ImColor(data.at(LINK_COLOR)[0].get<float>(),
                          data.at(LINK_COLOR)[1].get<float>(),
                          data.at(LINK_COLOR)[2].get<float>());
}

bool NodeIdLess::operator()(const ed::NodeId& lhs, const ed::NodeId& rhs) const
{
    return lhs.AsPointer() < rhs.AsPointer();
}

bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size)
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

CASE_tool::CASE_tool() : Application("CASE_tool"),
        m_Editor(nullptr),
        m_NextId(1),
        m_PinIconSize(24),
        MANAGER_AGENT_ID(1),
        m_Nodes(),
        m_Agents(),
        m_Links(),
        m_HeaderBackground(nullptr),
        m_SaveIcon(nullptr),
        m_RestoreIcon(nullptr),
        m_TouchTime(1.0f),
        m_NodeTouchTime(),
        m_ContextNodeId(0),
        m_Inside(0),
        m_ActiveButton(nullptr)
{
}

CASE_tool::~CASE_tool() {
    ReleaseTextures();

    if (m_Editor)
    {
        ed::DestroyEditor(m_Editor);
        m_Editor = nullptr;
    }
}

void CASE_tool::ReleaseTextures() {
    // Release or deallocate any textures used in the CASE_tool class
    if (m_HeaderBackground) {
        DestroyTexture(m_HeaderBackground);
        m_HeaderBackground = nullptr;
    }

    if (m_SaveIcon) {
        DestroyTexture(m_SaveIcon);
        m_SaveIcon = nullptr;
    }

    if (m_RestoreIcon) {
        DestroyTexture(m_RestoreIcon);
        m_RestoreIcon = nullptr;
    }
}

int CASE_tool::GetNextId() {
    return m_NextId++;
}

AgentId_t CASE_tool::GetNextAgentId() {
    return m_NextAgentId++;
}

void CASE_tool::TouchNode(ed::NodeId id) {
    m_NodeTouchTime[id] = m_TouchTime;
}

void CASE_tool::UpdateTouch() {
    const auto deltaTime = ImGui::GetIO().DeltaTime;
    for (auto &entry: m_NodeTouchTime) {
        if (entry.second > 0.0f)
            entry.second -= deltaTime;
    }
}

Node* CASE_tool::FindNode(ed::NodeId id) {
    for (auto &node: m_Nodes)
        if (node.ID == id)
            return &node;

    return nullptr;
}

Link* CASE_tool::FindLink(ed::LinkId id) {
    for (auto &link: m_Links)
        if (link.ID == id)
            return &link;

    return nullptr;
}

Pin* CASE_tool::FindPin(ed::PinId id) {
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

bool CASE_tool::IsPinLinked(ed::PinId id) {
    if (!id)
        return false;

    return std::any_of(m_Links.begin(), m_Links.end(), [id](const auto& link) {
        return link.StartPinID == id || link.EndPinID == id;
    });
}

bool CASE_tool::CanCreateLink(Pin *a, Pin *b) {
    if (!a || !b || a == b || !a->IsActive || !b->IsActive || a->Kind == b->Kind || a->Type != b->Type || a->NodeId.Get() == b->NodeId.Get())
        return false;

    return true;
}

void CASE_tool::BuildNode(Node *node) {
    for (auto &input: node->Inputs) {
        input.NodeId = node->ID;
        input.Kind = PinKind::Input;
    }

    for (auto &output: node->Outputs) {
        output.NodeId = node->ID;
        output.Kind = PinKind::Output;
    }
}

TextBuffer* CASE_tool::NewTextBuffer(BufferType type) {
    return new TextBuffer(type);
}

void CASE_tool::SetButtonLabel(Button* button, const char* label) {
    button->Label = label;
}

Node* CASE_tool::SpawnAgentNodeTree()
{
    AgentId_t agentId = GetNextAgentId();
    m_Nodes.emplace_back(GetNextId(), "Agent Relationships " + std::to_string(agentId), NodeType::ExtAgent, 0, ImColor(255, 255, 255), agentId);
    m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Relationship, NewTextBuffer(BufferType::Empty));
    m_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Relationship, NewTextBuffer(BufferType::Empty));
    BuildNode(&m_Nodes.back());
    //add to list of all agents
    m_Agents.push_back(m_Nodes.back().ID);
    return &m_Nodes.back();
}

Node* CASE_tool::SpawnAgentNodeResponsibilities(ed::NodeId outsideId)
{
    m_Nodes.emplace_back(GetNextId(), "Agent Responsibilities", NodeType::RespAgent, outsideId, ImColor(255, 255, 255));
    m_Nodes.back().Inputs.emplace_back(GetNextId(), "Reasoning", PinType::Reasoning, NewTextBuffer(BufferType::Empty));
    m_Nodes.back().Outputs.emplace_back(GetNextId(), "Services", PinType::Service, NewTextBuffer(BufferType::Empty));
    BuildNode(&m_Nodes.back());
    AddInsideNodeId(outsideId, m_Nodes.back().ID);
    return &m_Nodes.back();
}

Node* CASE_tool::SpawnReasoningAttributes(ed::NodeId outsideId)
{
    m_Nodes.emplace_back(GetNextId(), "Attributes", NodeType::Group, outsideId, ImColor(255, 255, 255));
    m_Nodes.back().Size = ImVec2(280, 500);
    return &m_Nodes.back();
}

Node* CASE_tool::SpawnIntelligentReasoningNode(ImVec2 position, ed::NodeId outsideId)
{
    ReasoningType type = ReasoningType::Intelligent;
    m_Nodes.emplace_back(GetNextId(), "Reasoning", GetNodeTypeFromReasoningType(type), outsideId, ImColor(153,255,153));
    m_Nodes.back().Outputs.emplace_back(GetNextId(), GetReasoningTypeAsString(type).c_str(), PinType::Reasoning, NewTextBuffer(BufferType::Empty));
    BuildNode(&m_Nodes.back());
    AddInsideNodeId(outsideId, m_Nodes.back().ID);
    ed::NodeId reasoningId = m_Nodes.back().ID;
    ed::SetNodePosition(reasoningId, position);
    //create node for attributes
    Node* attributeNode = SpawnReasoningAttributes(reasoningId);
    position.x = position.x + 100;
    ed::SetNodePosition(attributeNode->ID, position);
    AddInsideNodeId(reasoningId, attributeNode->ID);
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

Node* CASE_tool::SpawnReactiveReasoningNode(ImVec2 position, ed::NodeId outsideId) {
    ReasoningType type = ReasoningType::Reactive;
    m_Nodes.emplace_back(GetNextId(), "Reasoning", GetNodeTypeFromReasoningType(type), outsideId, ImColor(0,204,102));
    m_Nodes.back().Outputs.emplace_back(GetNextId(), GetReasoningTypeAsString(type).c_str(), PinType::Reasoning, NewTextBuffer(BufferType::Empty));
    BuildNode(&m_Nodes.back());
    // add node to its outside node
    AddInsideNodeId(outsideId, m_Nodes.back().ID);
    ed::NodeId reasoningId = m_Nodes.back().ID;
    ed::SetNodePosition(reasoningId, position);
    //create node for attributes
    Node* attributeNode = SpawnReasoningAttributes(reasoningId);
    position.x = position.x + 100;
    ed::SetNodePosition(attributeNode->ID, position);
    AddInsideNodeId(reasoningId, attributeNode->ID);
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

std::string CASE_tool::GetReasoningTypeAsString(ReasoningType type) {
    switch(type) {
        case(ReasoningType::Reactive): return "Reactive";
        case(ReasoningType::Intelligent): return "Intelligent";
        default: throw std::runtime_error("String version for input doesn't exist.");
    }
}

NodeType CASE_tool::GetNodeTypeFromReasoningType(ReasoningType type) {
    switch (type) {
        case (ReasoningType::Reactive): return NodeType::RespReasoningReactive;
        case (ReasoningType::Intelligent): return NodeType::RespReasoningIntelligent;
        default: throw std::runtime_error("NodeType for input ReasoningType doesn't exist.");
    }
}

void CASE_tool::SpawnAgent(ImVec2 position) {
    // relationships
    Node* node = SpawnAgentNodeTree(); ed::SetNodePosition(node->ID, position);
    // responsibilities
    node = SpawnAgentNodeResponsibilities(node->ID);
}

Node* CASE_tool::SpawnServiceIdNodeResponsibilities(ed::NodeId outsideId)
{
    m_Nodes.emplace_back(GetNextId(), "Service", NodeType::RespService, outsideId,ImColor(128, 195, 248));
    m_Nodes.back().Inputs.emplace_back(GetNextId(), "Id", PinType::Service, NewTextBuffer(BufferType::Id));

    AddInsideNodeId(outsideId, m_Nodes.back().ID);
    BuildNode(&m_Nodes.back());
    return &m_Nodes.back();
}

Node* CASE_tool::SpawnServiceIdNodeReasoning(ed::NodeId outsideId, TextBuffer* buffer, ed::NodeId associatedId)
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

void CASE_tool::SpawnServiceIdNode(ImVec2 position, ed::NodeId outsideId) {
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

Node* CASE_tool::SpawnAttributeNode(ed::NodeId outsideId)
{
    m_Nodes.emplace_back(GetNextId(), "Attribute", NodeType::Attribute, outsideId, ImColor(128, 195, 248));

    m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Type, NewTextBuffer(BufferType::Type), false);
    m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::InitValue, NewTextBuffer(BufferType::InitValue), false);
    m_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Attribute, NewTextBuffer(BufferType::Name), false);
    BuildNode(&m_Nodes.back());
    AddInsideNodeId(outsideId, m_Nodes.back().ID);
    return &m_Nodes.back();
}

Node* CASE_tool::SpawnConditionNode(ed::NodeId outsideId)
{
    m_Nodes.emplace_back(GetNextId(), "", NodeType::SimpleCond, outsideId,ImColor(128, 195, 248));
    m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Function, NewTextBuffer(BufferType::Empty));
    //An option for user choice of condition from menu
    m_Nodes.back().Inputs.back().PinButton = new Button(std::string ("Condition"));
    m_Nodes.back().Outputs.emplace_back(GetNextId(), "IF", PinType::Function, NewTextBuffer(BufferType::Empty));
    m_Nodes.back().Outputs.emplace_back(GetNextId(), "ElSE", PinType::Function, NewTextBuffer(BufferType::Empty));
    AddInsideNodeId(outsideId, m_Nodes.back().ID);
    BuildNode(&m_Nodes.back());

    return &m_Nodes.back();
}

Node* CASE_tool::SpawnCodeNode(ed::NodeId outsideId)
{
    m_Nodes.emplace_back(GetNextId(), "Code", NodeType::SimpleCode, outsideId,ImColor(128, 195, 248));

    m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Function, NewTextBuffer(BufferType::Empty));
    m_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Function, NewTextBuffer(BufferType::Empty));
    AddInsideNodeId(outsideId, m_Nodes.back().ID);
    BuildNode(&m_Nodes.back());

    return &m_Nodes.back();
}

Node* CASE_tool::SpawnFunctionNode(ed::NodeId outsideId)
{
    m_Nodes.emplace_back(GetNextId(), "Function", NodeType::Function, outsideId,ImColor(255,178,102));
    m_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Function, NewTextBuffer(BufferType::Name));
    AddInsideNodeId(outsideId, m_Nodes.back().ID);
    BuildNode(&m_Nodes.back());

    return &m_Nodes.back();
}

void CASE_tool::BuildNodes()
{
    for (auto& node : m_Nodes)
        BuildNode(&node);
}

void CASE_tool::OnStart()
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

void CASE_tool::OnStop()
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

ImColor CASE_tool::GetIconColor(PinType type) const
{
    switch (type)
    {
        default:
        case PinType::Function:    return {51, 150, 215}; // mass blue
        case PinType::Relationship:   return {255, 255, 255}; // white
        case PinType::Service:    return {51, 150, 215}; // mass blue
        case PinType::Reasoning:    return {255, 255, 255}; // white
    }
}

void CASE_tool::DrawPinIcon(const Pin& pin, bool connected, int alpha) const
{
    IconType iconType;
    ImColor color = GetIconColor(pin.Type);
    color.Value.w = static_cast<float>(alpha) / 255.0f;

    switch (pin.Type)
    {
        case PinType::Relationship:
            iconType = IconType::Flow;
            break;
        case PinType::Function:
        case PinType::Service:
        case PinType::Reasoning:
            iconType = IconType::Circle;
            break;
        default:
            return;
    }

    ax::Widgets::Icon(ImVec2(static_cast<float>(m_PinIconSize), static_cast<float>(m_PinIconSize)), iconType, connected, color, ImColor(32, 32, 32, alpha));
}

void CASE_tool::ShowLeftPane(float paneWidth)
{
    auto& io = ImGui::GetIO();

    ImGui::BeginChild("Selection", ImVec2(paneWidth, 0));

    paneWidth = ImGui::GetContentRegionAvail().x;

    static bool showProjectEditor = false;
    static bool showGenerateCodeEditor = false;
    static bool showErrorMessageEditor = false;

    ImGui::BeginHorizontal("Style Editor", ImVec2(paneWidth, 0));
    ImGui::Spring(0.0f, 0.0f);
    if (ImGui::Button("Zoom to Content"))
        ed::NavigateToContent();
    ImGui::Spring(0.0f);
        if (ImGui::Button("Generate Code"))
            showGenerateCodeEditor = true;
        if (ImGui::Button("Project")) {
            showProjectEditor = true;
        }
    ImGui::Spring();
    ImGui::EndHorizontal();

    if (showProjectEditor) {
        try {
            ShowProjectEditor(&showProjectEditor);
        } catch (const std::runtime_error& e) {
            showErrorMessageEditor = true;
        }
    }

    if (showGenerateCodeEditor) {
        try {
            ShowGenerateCodeEditor(&showGenerateCodeEditor);
        } catch (const std::runtime_error& e) {
            showErrorMessageEditor = true;
        }
    }

    if (showErrorMessageEditor) {
        ShowErrorMessageEditor(&showErrorMessageEditor);
    }

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

void CASE_tool::ShowLeftPaneNodes() {
    for (auto& node : m_Nodes)
    {
        if (node.Type != NodeType::ExtAgent) {
            continue;
        }
        DepthSearching(node, ImVec2(0,0));
    }
}

void CASE_tool::DepthSearching(Node& node, ImVec2 shift) {
    DoWithNode(node, shift);
    if (node.InsideIds.empty())
        return;
    shift.x += 15;
    for (auto& id : node.InsideIds) {
        Node* insideNode = FindNode(id);
        DepthSearching(*insideNode, shift);
    }
}

void CASE_tool::DoWithNode(Node& node, const ImVec2& shift) {
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

void CASE_tool::BlueprintAndSimpleInputs(Node& node, Pin* newLinkPin, util::BlueprintNodeBuilder &builder) {
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
            if (ImGui::Button(input.PinButton->Label.c_str())) {
                m_ActiveButton = input.PinButton;
            }
        }
        builder.EndInput();
    }
}

void CASE_tool::BlueprintAndSimpleOutputs(Node& node, Pin* newLinkPin, util::BlueprintNodeBuilder& builder) {
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

void CASE_tool::OnFrame(float deltaTime) {
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
            if (node.Type == NodeType::ExtAgent || node.Type == NodeType::Group
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

        // create comment
        for (auto& node : m_Nodes)
        {
            if (node.Type != NodeType::Group || node.OutsideId.Get() != m_Inside.Get())
                continue;

            const float commentAlpha = 0.75f;

            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, commentAlpha);
            ed::PushStyleColor(ed::StyleColor_NodeBg, ImColor(255, 255, 255, 64));
            ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(255, 255, 255, 64));
            ed::BeginNode(node.ID);
            ImGui::PushID(node.ID.AsPointer());
            ImGui::BeginVertical("content");
            ImGui::BeginHorizontal("horizontal");
            ImGui::Spring(1);
            ImGui::TextUnformatted(node.Name.c_str());
            ImGui::Spring(1);
            ImGui::EndHorizontal();
            ed::Group(node.Size);
            ImGui::EndVertical();
            ImGui::PopID();
            ed::EndNode();
            ed::PopStyleColor(2);
            ImGui::PopStyleVar();
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
                                m_Links.emplace_back(GetNextId(), startPinId, endPinId);
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
                        DeleteLink(linkId);
                    }
                }
            }
            ed::EndDelete();
        }

        ImGui::SetCursorScreenPos(cursorTopLeft);
    }

# if 1
    ed::Suspend();
    //control if user made doubleclick on node
    ed::NodeId doubleClickedNode = ed::GetDoubleClickedNode();
    if (doubleClickedNode.Get() > 0) {
        Node *node = FindNode(doubleClickedNode);
        if (node->Type == NodeType::ExtAgent ||
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
            if (pin->NodeId)
                ImGui::Text("Node: %p", pin->NodeId.AsPointer());
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
            node = FindNode(m_Inside);
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
                if (ImGui::MenuItem("Attribute")) {
                    node = SpawnAttributeNode(node->ID);
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
                if (ImGui::MenuItem("Attribute")) {
                    node = SpawnAttributeNode(node->ID);
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

                        m_Links.emplace_back(GetNextId(), startPin->ID, endPin->ID);
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

void CASE_tool::DeleteNode(ed::NodeId nodeId) {
    // find deleted node
    Node* node = FindNode(nodeId);
    //we don't wanna delete master node
    if ((node->Type == NodeType::ExtAgent && node->ID.Get() == 1) ||
            (node->Type == NodeType::RespAgent && FindNode(node->OutsideId)->ID.Get() == 1))
        return;
    // prevents to never ending loop in deleting
    node->Deleted = true;
    // if deleted node is responsible agent, remove the whole agent
    if (node->Type == NodeType::RespAgent) {
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
    // if node is Responsible Service, delete service node that is associated with this node
    if (node->Type == NodeType::RespService) {
        for (ed::NodeId id : node->AssociatedIds) {
            Node *associatedNode = FindNode(id);
            if (!associatedNode->Deleted) {
                DeleteNode(id);
            }
        }
    }
    // if node is Reasoning Service, delete it from associated list of its associated node
    if (node->Type == NodeType::ReasService) {
        // control, if node is deleted because its outside node is deleted or its associated node is deleted
        // else we cannot delete reasoning service node
        Node* outsideNode = FindNode(node->OutsideId);
        Node* assocNode = FindNode(node->AssociatedIds.at(0));
        if (!outsideNode->Deleted && !assocNode->Deleted) {
            node->Deleted = false;
            return;
        }
        if (!assocNode->Deleted) {
            auto id = std::find_if(assocNode->AssociatedIds.begin(), assocNode->AssociatedIds.end(),
                                   [nodeId](auto &insideId) { return insideId == nodeId; });
            if (id != assocNode->AssociatedIds.end())
                assocNode->AssociatedIds.erase(id);
        }
    }
    // if node is associated by other node, delete them as first
    if (!node->InsideIds.empty()) {
        //delete all inside nodes
        for (auto &id: node->InsideIds)
            DeleteNode(id);
    }
    // delete node links
    for(Pin& pin: node->Inputs) {
        DeleteLinks(pin);
    }
    for(Pin& pin: node->Outputs) {
        DeleteLinks(pin);
    }
    //delete node id from outside node
    if (node->OutsideId.Get() != 0) {
        Node* outsideNode = FindNode(node->OutsideId);
        if (!outsideNode->Deleted) {
            auto id = std::find_if(outsideNode->InsideIds.begin(), outsideNode->InsideIds.end(),
                                   [nodeId](auto &insideId) { return insideId == nodeId; });
            if (id != outsideNode->InsideIds.end())
                outsideNode->InsideIds.erase(id);
        }
    }
    //delete node
    //if node is ext agent, delete it from agent list and go up
    if (node->Type == NodeType::ExtAgent) {
        auto id = std::find_if(m_Agents.begin(), m_Agents.end(),
                               [nodeId](auto &insideId) { return insideId == nodeId; });
        if (id != m_Agents.end()) {
            m_Agents.erase(id);
        }
        m_Inside = 0;
    }
    auto id = std::find_if(m_Nodes.begin(), m_Nodes.end(),
                           [nodeId](auto &node) { return node.ID == nodeId; });
    if (id != m_Nodes.end()) {
        m_Nodes.erase(id);
    }
}

void CASE_tool::DeleteLinks(Pin& pin) {
    //loop over all link id assocaited with the pin
    for (auto& linkId : pin.LinkIds) {
        DeleteLink(linkId);
    }
}

void CASE_tool::DeleteLink(ed::LinkId linkId) {
    auto id = std::find_if(m_Links.begin(), m_Links.end(),
                           [linkId](auto &link) { return link.ID == linkId; });
    if (id != m_Links.end()) {
        Link* link = FindLink(linkId);
        //delete link id from associated pins
        Pin* pin = FindPin(link->StartPinID);
        DeleteLinkId(pin, linkId);
        pin = FindPin(link->EndPinID);
        DeleteLinkId(pin, linkId);
        m_Links.erase(id);
    }
}

void CASE_tool::DeleteLinkId(Pin* otherPin, ed::LinkId linkId) {
    auto otherId = std::find_if(otherPin->LinkIds.begin(), otherPin->LinkIds.end(),
                                [linkId](auto &otherLinkId) { return otherLinkId == linkId; });
    otherPin->LinkIds.erase(otherId);
}

void CASE_tool::AddInsideNodeId(ed::NodeId outsideId, ed::NodeId insideId) {
    Node* outsideNode = FindNode(outsideId);
    outsideNode->InsideIds.push_back(insideId);
}

void CASE_tool::AddLinkToPin(ed::PinId pinId, ed::LinkId linkId) {
    Pin* pin = FindPin(pinId);
    pin->LinkIds.push_back(linkId);
}

json CASE_tool::Serialize() {
    json data_json = {
            {CASE_TOOL_NODES, SerializeNodes()},
            {CASE_TOOL_LINKS, SerializeLinks()},
            {CASE_TOOL_AGENTS, SerializeAgents()},
            {CASE_TOOL_NEXT_ID, m_NextId},
            {CASE_TOOL_NEXT_AGENT_ID, m_NextAgentId}
    };
    return data_json;
}

void CASE_tool::Deserialize(const json &data) {
    m_NextId = data.at(CASE_TOOL_NEXT_ID).get<int>();
    m_NextAgentId = data.at(CASE_TOOL_NEXT_AGENT_ID).get<int>();
    m_Nodes.clear();
    m_Nodes = DeserializeNodes(data.at(CASE_TOOL_NODES));
    m_Agents.clear();
    m_Agents = DeserializeAgents(data.at(CASE_TOOL_AGENTS));
    m_Links.clear();
    m_Links = DeserializeLinks(data.at(CASE_TOOL_LINKS));

    m_Inside = 0;
}

// Helper function to serialize nodes
json CASE_tool::SerializeNodes() const {
    json nodes_array = json::array();
    for (const Node& node : m_Nodes) {
        nodes_array.push_back(node.Serialize());
    }
    return nodes_array;
}

// Helper function to serialize links
json CASE_tool::SerializeLinks() const {
    json links_array = json::array();
    for (const Link& link : m_Links) {
        links_array.push_back(link.Serialize());
    }
    return links_array;
}

// Helper function to serialize agents
json CASE_tool::SerializeAgents() const {
    json agents_array = json::array();
    for (const ed::NodeId& id : m_Agents) {
        agents_array.push_back(id.Get());
    }
    return agents_array;
}

// Helper function to deserialize nodes
std::vector<Node> CASE_tool::DeserializeNodes(const json& nodes_data) {
    std::vector<Node> nodes;
    for (const auto& node_data : nodes_data) {
        nodes.emplace_back(Node(node_data)); // Assuming Node has a constructor that takes json
    }
    return nodes;
}

// Helper function to deserialize links
std::vector<Link> CASE_tool::DeserializeLinks(const json& links_data) {
    std::vector<Link> links;
    for (const auto& link_data : links_data) {
        links.emplace_back(Link(link_data)); // Assuming Link has a constructor that takes json
    }
    return links;
}

// Helper function to deserialize agents
std::vector<ed::NodeId> CASE_tool::DeserializeAgents(const json& agents_data) {
    std::vector<ed::NodeId> agents;
    for (const auto& agent_id : agents_data) {
        agents.emplace_back(ed::NodeId(agent_id.get<int>())); // Assuming ed::NodeId has a constructor that takes int
    }
    return agents;
}

//TODO: petri net missing, agent relationships missing
json CASE_tool::GetData() {
    // JSON object to hold the data
    json data_json = {};
    // JSON object for agent hierarchy
    json hierarchy_json = {};
    // Iterate through all external agents
    for (ed::NodeId id : m_Agents) {
        // Get the current agent node
        Node *node = FindNode(id);
        // Add agent and his parent to the hierarchy JSON
        if (id.Get() != 1 && node->Inputs.at(0).LinkIds.empty()) {
            // We don't want data about an agent that is not part of the hierarchy, except for the master agent
            continue;
       } else if (id.Get() != 1) {
            // we don't wanna register master agent to hierarchy
            //find parent ID
            Pin *parentPin = FindPin(FindLink(node->Inputs.at(0).LinkIds.at(0))->StartPinID);
            hierarchy_json[std::to_string(id.Get())] = std::to_string(parentPin->NodeId.Get());
       }

        // Get the responsible agent node
        Node *respAgent = FindNode(node->InsideIds.at(0));
        // Set to hold associated services' IDs
        std::unordered_set<unsigned long> associatedServicesId;

        // Find associated services connected with the responsible agent
        for (ed::NodeId respId: node->InsideIds) {
            Node *respNode = FindNode(respId);
            if (respNode->Type == NodeType::RespService) {
                // Ensure the service is connected to the responsible agent
                if (respNode->Inputs.at(0).LinkIds.empty() ||
                    FindLink(respNode->Inputs.at(0).LinkIds.at(0))->StartPinID != respAgent->Outputs.at(0).ID)
                    continue;
                // Store associated service IDs
                for (auto assocId : respNode->AssociatedIds) {
                    associatedServicesId.insert(assocId.Get());
                }
            }
        }

        // Create JSON data from agent reasoning
        json agent_json = {};
        // Add Agent Id
        agent_json[AGENT_ID] = node->AgentId;
        for (ed::NodeId respId: node->InsideIds) {
            Node *respNode = FindNode(respId);
            // Check if it's reactive reasoning
            if (respNode->Type == NodeType::RespReasoningReactive) {
                // Ensure node is connected to the responsible agent
                if (respNode->Outputs.at(0).LinkIds.empty() ||
                    FindLink(respNode->Outputs.at(0).LinkIds.at(0))->EndPinID != respAgent->Inputs.at(0).ID) {
                    continue;
                }
                // JSON object to store reactive reasoning data
                json reactive_json = {};
                json services_json = json::array();
                json attributes_json = json::array();
                for (ed::NodeId innerId : respNode->InsideIds) {
                    Node* innerNode = FindNode(innerId);
                    json node_json = {};
                    //control if innerNode is Service type
                    if (innerNode->Type == NodeType::ReasService) {
                        auto it = associatedServicesId.find(innerNode->ID.Get());
                        // Is it linked at responsible level?
                        if (innerNode->Outputs.at(0).LinkIds.empty() || it == associatedServicesId.end())
                            continue;
                    }
                    switch (innerNode->Type) {
                        case (NodeType::Attribute):
                            node_json[TYPE] = ATTRIBUTE_ID;
                            node_json[TYPE_ATR] = innerNode->Inputs.at(0).PinBuffer->Buffer;
                            node_json[INIT_VALUE] = innerNode->Inputs.at(1).PinBuffer->Buffer;
                            node_json[NAME] = innerNode->Outputs.at(0).PinBuffer->Buffer;
                            attributes_json.push_back(std::to_string(innerId.Get()));
                            break;
                        case (NodeType::Function):
                            node_json[TYPE] = FUNCTION_ID;
                            node_json[NAME] = innerNode->Inputs.at(0).PinBuffer->Buffer;
                            break;
                        case (NodeType::ReasService):
                            node_json[TYPE] = SERVICE_ID;
                            node_json[SERVICE] = innerNode->Outputs.at(0).PinBuffer->Buffer;
                            AddLinkedNodes(innerNode->Outputs.at(0).LinkIds, LINKED, node_json);
                            services_json.push_back(std::to_string(innerId.Get()));
                            break;
                        default:
                            continue;
                    }
                    reactive_json[std::to_string(innerId.Get())] = node_json;
                }
                reactive_json[SERVICES] = services_json;
                reactive_json[ATTRIBUTES] = attributes_json;
                // Add reactive reasoning data to the agent JSON object
                agent_json[REACTIVE] = reactive_json;
            }
            if (respNode->Type == NodeType::RespReasoningIntelligent) {
                // Ensure node is connected to the responsible agent
                if (respNode->Outputs.at(0).LinkIds.empty() ||
                    FindLink(respNode->Outputs.at(0).LinkIds.at(0))->EndPinID != respAgent->Inputs.at(0).ID) {
                    continue;
                }
                // JSON object to store petri net reasoning data
                json petriNet_json = {};
                json services_json = json::array();
                json attributes_json = json::array();
                // Find all service nodes and attributes
                for (ed::NodeId innerId : respNode->InsideIds) {
                    Node* innerNode = FindNode(innerId);
                    // If innerNode is Service type, is it correctly connected ?
                    if (innerNode->Type == NodeType::ReasService) {
                        auto it = associatedServicesId.find(innerNode->ID.Get());
                        if (innerNode->Outputs.at(0).LinkIds.empty() || it == associatedServicesId.end())
                            continue;
                    }
                    json node_json = {};
                    node_json[ID] = innerNode->ID.Get();
                    switch (innerNode->Type) {
                        case (NodeType::ReasService):
                            node_json[TYPE] = SERVICE_ID;
                            node_json[SERVICE] = innerNode->Outputs.at(0).PinBuffer->Buffer;
                            AddLinkedNodes(innerNode->Outputs.at(0).LinkIds, LINKED, node_json);
                            services_json.push_back(std::to_string(innerId.Get()));
                            break;
                        case (NodeType::Attribute):
                            node_json[TYPE] = ATTRIBUTE_ID;
                            node_json[TYPE_ATR] = innerNode->Inputs.at(0).PinBuffer->Buffer;
                            node_json[INIT_VALUE] = innerNode->Inputs.at(1).PinBuffer->Buffer;
                            node_json[NAME] = innerNode->Outputs.at(0).PinBuffer->Buffer;
                            attributes_json.push_back(std::to_string(innerId.Get()));
                            break;
                        case (NodeType::SimpleCond):
                            node_json[TYPE] = CONDITION_ID;
                            node_json[CONDITION] = innerNode->Inputs.at(0).PinButton->Label;
                            AddLinkedNodes(innerNode->Outputs.at(0).LinkIds, IF, node_json);
                            AddLinkedNodes(innerNode->Outputs.at(0).LinkIds, ELSE, node_json);
                            break;
                        case (NodeType::SimpleCode):
                            node_json[TYPE] = CODE_ID;
                            AddLinkedNodes(innerNode->Outputs.at(0).LinkIds, LINKED, node_json);
                            break;
                        case (NodeType::Function):
                            node_json[TYPE] = FUNCTION_ID;
                            node_json[NAME] = innerNode->Inputs.at(0).PinBuffer->Buffer;
                            break;
                        default:
                            continue;
                    }
                    petriNet_json[std::to_string(innerId.Get())] = node_json;
                }
                petriNet_json[SERVICES] = services_json;
                petriNet_json[ATTRIBUTES] = attributes_json;
                // Add reactive reasoning data to the agent JSON object
                agent_json[PETRI_NET] = petriNet_json;
            }
        }
        // Add agent data to the main JSON object
        data_json[std::to_string(id.Get())] = agent_json;
    }

    json output_json = {};
    output_json[HIERARCHY] = hierarchy_json;
    output_json[DATA] = data_json;
    return output_json;
}

//void CASE_tool::PetriNetNode(std::deque<Node*> deque) {
//    while (!deque.empty()) {
//        Node* node = deque.front();
//        deque.pop_front();
//        // Iterate through all outputs
//        for (Pin pin : node->Outputs) {
//            std::deque<Node *> dequeNodes = GetEndNodes(&pin);
//            deque.insert(deque.end(), dequeNodes.begin(), dequeNodes.end());
//        }
//    }
//
//
//
//}

void CASE_tool::AddLinkedNodes(std::vector<ed::LinkId> &links, std::string key, json &data) {
    data[key] = json::array();
    for (auto id : links) {
        data[key].push_back(std::to_string(FindPin(FindLink(id)->EndPinID)->NodeId.Get()));
    }
}

std::deque<Node*> CASE_tool::GetEndNodes(Pin* pin) {
    std::deque<Node*> deque;
    // Iterate through all connected links
    for(ed::LinkId linkId : pin->LinkIds)  {
        Link* link = FindLink(linkId);
        Pin* endPin = FindPin(link->EndPinID);
        // Save found end node
        deque.push_back(FindNode(endPin->NodeId));
    }
    return deque;
}


void CASE_tool::ShowProjectEditor(bool* show) {
    if (!ImGui::Begin("Project options", show)) {
        ImGui::End();
        return;
    }
    static char strFileName[128] = "Input";
    ImGui::InputText("File Name", strFileName, IM_ARRAYSIZE(strFileName));
    static char strFilePath[128] = "Input";
    ImGui::InputText("File Path", strFilePath, IM_ARRAYSIZE(strFilePath));
    try {
        if (ImGui::Button("Load")) {
            *show = false;
            Deserialize(fileManager->readJson(strFilePath, strFileName));
        }
        if (ImGui::Button("Save")) {
            *show = false;
            fileManager->saveJson(strFilePath, strFileName, Serialize());
        }
    } catch (const std::runtime_error &e) {
        ImGui::End();
        throw e;
    }
    ImGui::End();
}


void CASE_tool::ShowGenerateCodeEditor(bool* show) {
    if (!ImGui::Begin("Generate code options", show)) {
        ImGui::End();
        return;
    }
    static char strFilePath[128] = "Input";
    ImGui::InputText("File Path", strFilePath, IM_ARRAYSIZE(strFilePath));
    try {
        if (ImGui::Button("Generate")) {
            *show = false;
            json data = GetData();
            fileManager->saveJson("/home/miska/CLionProjects/Agent_simulation_library", "test-generovanie", data);
            agentGenerator->processJson(data, strFilePath);
        }
    } catch (const std::runtime_error &e) {
        ImGui::End();
        throw e;
    }
    ImGui::End();
}


void CASE_tool::ShowErrorMessageEditor(bool* show) {
    if (!ImGui::Begin("Message window", show)) {
        ImGui::End();
        return;
    }
    ImGui::Text("Error during file processing");
    if (ImGui::Button("OK")) {
        *show = false;
    }
    ImGui::End();
}

ed::LinkId CASE_tool::GetNextLinkId()
{
    return ed::LinkId(GetNextId());
}

int Main(int argc, char** argv)
{
    CASE_tool tool("Agent simulation library", argc, argv);

    if (tool.Create())
        return tool.Run();

    return 0;
}
