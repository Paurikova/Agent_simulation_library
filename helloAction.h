#pragma once
#include "action.h"
#include <string>
using namespace std;

class HelloAction: public Action {
public:
    HelloAction(string name) : Action(name) {};
    void process() override;
};
