#pragma once
class State;

class StateMachine : public Singleton<StateMachine>
{
public:
    StateMachine();
    ~StateMachine();

    void                        pushState(State*);
    void                        update(float dt);
    void                        render();

    State*                      getCurrentState()
    {
        return m_currentState;
    }

private:
    State*                      m_currentState = nullptr;
    std::deque<State*>          m_states;
};
