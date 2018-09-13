#include <iostream>
#include <memory>

class CImplementor
{
public:
    virtual ~CImplementor() = default;
    virtual void Run()const = 0;
};

class CConcreteImplementorA : public CImplementor
{
public:
    virtual void Run()const override
    {
        std::cout << "CConcreteImplementorA" << std::endl;
    }
};

class CConcreteImplementorB : public CImplementor
{
public:
    virtual void Run()const override
    {
        std::cout << "CConcreteImplementorB" << std::endl;
    }
};

class CAbtraction
{
public:
    virtual ~CAbtraction() = default;
    void SetImplementor(std::shared_ptr<CImplementor> p_implementor)
    {
        m_p_implementor = p_implementor;
    }

    virtual void Operation()const
    {
        std::cout << "CAbtraction\t";
        if (m_p_implementor != nullptr)
        {
            m_p_implementor->Run();
        }
    }

protected:
    std::shared_ptr<CImplementor> m_p_implementor = nullptr;
};

class CRefinedAbstraction : public CAbtraction
{
public:
    virtual void Operation()const override
    {
        std::cout << "CRefinedAbstraction\t";
        if (m_p_implementor != nullptr)
        {
            m_p_implementor->Run();
        }
    }
};

int main()
{
    CAbtraction ab;
    ab.SetImplementor(std::make_shared<CConcreteImplementorA>());
    ab.Operation();

    ab.SetImplementor(std::make_shared<CConcreteImplementorB>());
    ab.Operation();

    CRefinedAbstraction rab;
    rab.SetImplementor(std::make_shared<CConcreteImplementorA>());
    rab.Operation();

    rab.SetImplementor(std::make_shared<CConcreteImplementorB>());
    rab.Operation();

    return 0;
}