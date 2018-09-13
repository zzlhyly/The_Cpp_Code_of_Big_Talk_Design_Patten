#include <iostream>
#include <string>

class CColleague;
class CMediator
{
public:
    virtual ~CMediator() = default;
    virtual void Send(const std::string &message, const CColleague *colleague)const = 0;
};

class CColleague
{
public:
    explicit CColleague(CMediator *mediator)
        : m_p_mediator(mediator)
    {

    }

    virtual ~CColleague() = default;

    void Send(const std::string &messgae)const
    {
        if (m_p_mediator != nullptr)
        {
            m_p_mediator->Send(messgae, this);
        }
    }

    virtual void Notify(const std::string &message)const = 0;

protected:
    CMediator *m_p_mediator = nullptr;
};

class CConcreteColleagueA : public CColleague
{
public:
    using CColleague::CColleague;
    virtual void Notify(const std::string &message)const override
    {
        std::cout << "CConcreteColleagueA get " << message << std::endl;
    }
};

class CConcreteColleagueB : public CColleague
{
public:
    using CColleague::CColleague;
    virtual void Notify(const std::string &message)const override
    {
        std::cout << "CConcreteColleagueB get " << message << std::endl;
    }
};

class CConcreteMediator : public CMediator
{
public:
    void SetColleagueA(CColleague *p_colleagueA)
    {
        m_p_colleagueA = p_colleagueA;
    }

    void SetColleagueB(CColleague *p_colleagueB)
    {
        m_p_colleagueB = p_colleagueB;
    }

    virtual void Send(const std::string &message, const CColleague *colleague)const override
    {
        const CConcreteColleagueA *pca = dynamic_cast<const CConcreteColleagueA *>(colleague);
        const CConcreteColleagueB *pcb = dynamic_cast<const CConcreteColleagueB *>(colleague);
        if (nullptr != pca)
        {
            if (m_p_colleagueB != nullptr)
            {
                m_p_colleagueB->Notify(message);
            }
        }

        if (nullptr != pcb)
        {
            if (m_p_colleagueA != nullptr)
            {
                m_p_colleagueA->Notify(message);
            }
        }
    }
private:
    CColleague *m_p_colleagueA = nullptr;
    CColleague *m_p_colleagueB = nullptr;
};

int main()
{
    CConcreteMediator cm;
    CConcreteColleagueA ca(&cm);
    CConcreteColleagueB cb(&cm);

    cm.SetColleagueA(&ca);
    cm.SetColleagueB(&cb);

    ca.Send("aaa");
    cb.Send("bbb");

    return 0;
}