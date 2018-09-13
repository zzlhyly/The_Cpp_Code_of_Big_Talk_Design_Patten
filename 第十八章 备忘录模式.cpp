#include <iostream>

class CMemento
{
public:
    CMemento() = default;
    CMemento(int stateA, int stateB)
        : m_stateA(stateA), m_stateB(stateB)
    {

    }

    int GetStateA()const
    {
        return m_stateA;
    }

    int GetStateB()const
    {
        return m_stateB;
    }

private:
    int m_stateA = 0;
    int m_stateB = 0;;
};

class COriginator
{
public:
    void InitState()
    {
        m_stateA = 100;
        m_stateB = 100;
    }

    void DisplayState()const
    {
        std::cout << "StateA " << m_stateA << "\tStateB " << m_stateB << std::endl;
    }

    void ChangeState()
    {
        m_stateA = 0;
        m_stateB = 0;
    }

    void RecoveryState(const CMemento &me)
    {
        m_stateA = me.GetStateA();
        m_stateB = me.GetStateB();
    }

    CMemento SaveState()const
    {
        return CMemento(m_stateA, m_stateB);
    }

private:
    int m_stateA = 0;
    int m_stateB = 0;
};

class CCaretaker
{
public:
    void SaveMemento(const CMemento &me)
    {
        m_me = me;
    }

    CMemento GetMemento()const
    {
        return m_me;
    }

private:
    CMemento m_me;
};

int main()
{
    COriginator org;
    org.InitState();;
    org.DisplayState();

    CCaretaker ct;
    ct.SaveMemento(org.SaveState());

    org.ChangeState();
    org.DisplayState();

    org.RecoveryState(ct.GetMemento());
    org.DisplayState();

    return 0;
}