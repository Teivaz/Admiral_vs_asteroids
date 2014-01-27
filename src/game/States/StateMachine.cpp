#include "Precompiled.h"
#include "StateMachine.h"
#include "State.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::pushState(State* st)
{
    m_states.push_back(st);
}

void StateMachine::update(float dt)
{
    if (!m_currentState)
    {
        if (m_states.empty())
            return;
        m_currentState = m_states.front();
        m_states.pop_front();
        m_currentState->onEnter();
    }

    m_currentState->update(dt);
    
    if (m_currentState->isFinished())
    {
        m_currentState->onFinish();
        delete m_currentState;
        m_currentState = nullptr;
    }
}

void StateMachine::render()
{
    if (m_currentState)
    {
        m_currentState->render();
    }
}
