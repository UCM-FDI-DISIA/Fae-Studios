#include "../checkML.h"
#include "GameStateMachine.h"

GameState* GameStateMachine::currentState() const {
    return stateStack.top();
}

void GameStateMachine::pushState(GameState* state) {
    stateStack.push(state);
}

void GameStateMachine::changeState(GameState* state) {
    if(!stateStack.empty()) {
        if(stateStack.top()->getStateID() == state->getStateID()) return; //Si el estado que queremos sustituir es el mismo, no hacemos nada
        delete stateStack.top();
        stateStack.top()->setDelete();
        stateStack.pop();
    }
    stateStack.push(state);
}

void GameStateMachine::popState() {
    if(!stateStack.empty()) {
        delete stateStack.top();
        stateStack.top()->setDelete();
        stateStack.pop();
    }
}

void GameStateMachine::emptyStack() {
    while (!empty()) popState();
}

bool GameStateMachine::empty() {
    return stateStack.empty();
}

GameState* GameStateMachine::pop() {
    GameState* top = stateStack.top();
    stateStack.pop();
    return top;
}