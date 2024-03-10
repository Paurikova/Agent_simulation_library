#include "agent.h"

void Agent::registerFunction(int msgId, Funct func) {
    functionMap[msgId] = func;
}

void Agent::unregisterFunction(int eventId) {
    auto it = functionMap.find(eventId);
    if (it != functionMap.end()) {
        functionMap.erase(it);
    } else {
        throw std::runtime_error("Function with event ID " + std::to_string(eventId) + " does not exist in the map");
    }
}

void Agent::process(int messageId, int sender) {
    auto it = functionMap.find(messageId);
    if (it != functionMap.end()) {
        // Retrieve the function pointer and call it
        it->second(sender);
    } else {
        // Throw an exception if the function does not exist
        throw std::runtime_error("Function with event ID " + std::to_string(messageId) + " does not exist in the map.");
    }
}

void Agent::doTick(int time) {
    //set execute to false
    execute = false;
    currTime = time;
    //process all messages for current time
    Message* message = schedule->popMessage(time);
    while (message) {
        process(message->id, message->sender);
        message = schedule->popMessage(time);
    }
}

void Agent::setExecute(bool pExecute) {
    execute = pExecute;
}

bool Agent::getExecute() {
    return execute;
}

Message Agent::getTopMessage() {
    // Define a "null" message
    const Message nullMessage;
    // Get the top message from the vector
    if (outBox->empty()) {
        return nullMessage;
    }
    Message topMessage = outBox->back(); // Get the last message
    outBox->pop_back(); // Remove the last message
    return topMessage;
}

Message Agent::receiveMessage(Message msg) {
    //agent got new message
    //It is necessary to determine i
    // f there is anything else that needs to be done in the current tick
    execute = true;
    //add message to agent's schedule
    schedule->pushMessage(msg);
}

void Agent::sendMessage(int id, int receiver, int time, int priority) {
    // Create a new message
    Message newMessage;
    newMessage.id = id;
    newMessage.sender = getId();
    newMessage.receiver = receiver;
    newMessage.time = time;
    newMessage.priority = priority;

    // Add the new message to the message box
    outBox->push_back(newMessage);
}

int Agent::getCurrTime() {
    return currTime;
}