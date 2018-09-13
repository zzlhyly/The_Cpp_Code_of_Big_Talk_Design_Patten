#include <iostream>
#include <memory>
#include <vector>

class CReceiver
{
public:
    void ActionA()const
    {
        std::cout << "执行操作A" << std::endl;
    }

    void ActionB()const
    {
        std::cout << "执行操作B" << std::endl;
    }
};

class CCommandTest
{
public:
    explicit CCommandTest(const std::shared_ptr<CReceiver> &recevier)
        : m_recevier(recevier)
    {

    }
    virtual ~CCommandTest() = default;
    virtual void Execute()const = 0;
protected:
    std::shared_ptr<CReceiver> m_recevier;
    
};

class CConcreteCommandTestA : public CCommandTest
{
public:
    using CCommandTest::CCommandTest;
    virtual void Execute()const override
    {
        if (m_recevier != nullptr)
        {
            m_recevier->ActionA();
        }
    }
};

class CConcreteCommandTestB : public CCommandTest
{
public:
    using CCommandTest::CCommandTest;
    virtual void Execute()const override
    {
        if (m_recevier != nullptr)
        {
            m_recevier->ActionB();
        }
    }
};

class CInvoker
{
public:
    void AddCommand(const std::shared_ptr<CCommandTest> &command)
    {
        m_vec.push_back(command);
    }

    void ExecuteCommand()const
    {
        for (auto command : m_vec)
        {
            command->Execute();
        }
    }
private:
    std::vector<std::shared_ptr<CCommandTest>> m_vec;
};

int main()
{
    std::shared_ptr<CReceiver> sprv = std::make_shared<CReceiver>();
    std::shared_ptr<CCommandTest> spA = std::make_shared<CConcreteCommandTestA>(sprv);
    std::shared_ptr<CCommandTest> spB = std::make_shared<CConcreteCommandTestB>(sprv);

    CInvoker iv;
    iv.AddCommand(spA);
    iv.AddCommand(spB);
    iv.AddCommand(spA);
    iv.AddCommand(spB);

    iv.ExecuteCommand();

    return 0;
}
