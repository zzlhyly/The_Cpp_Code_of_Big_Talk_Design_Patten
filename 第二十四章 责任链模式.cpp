#include <iostream>
#include <memory>
#include <random>
#include <ctime>

class CHandler
{
public:
    virtual ~CHandler() = default;

    void SetSuperior(const std::shared_ptr<CHandler> &superior)
    {
        m_superior = superior;
    }

    virtual void HandlerRequest(int request)const = 0;

protected:
    std::shared_ptr<CHandler> m_superior = nullptr;
};

class CConcreteHandlerA : public CHandler
{
public:
    virtual void HandlerRequest(int request)const override
    {
        if (request < 10)
        {
            std::cout << "CConcreteHandlerA handle" << request << std::endl;
        }
        else
        {
            if (m_superior != nullptr)
            {
                m_superior->HandlerRequest(request);
            }
        }
    }
};

class CConcreteHandlerB : public CHandler
{
public:
    virtual void HandlerRequest(int request)const override
    {
        if (request < 20)
        {
            std::cout << "CConcreteHandlerB handle" << request << std::endl;
        }
        else
        {
            if (m_superior != nullptr)
            {
                m_superior->HandlerRequest(request);
            }
        }
    }
};

class CConcreteHandlerC : public CHandler
{
public:
    virtual void HandlerRequest(int request)const override
    {
        if (request < 30)
        {
            std::cout << "CConcreteHandlerC handle" << request << std::endl;
        }
        else
        {
            std::cout << "no handle" << request << std::endl;
        }
    }
};

int main()
{
    std::shared_ptr<CHandler> handlerA = std::make_shared<CConcreteHandlerA>();
    std::shared_ptr<CHandler> handlerB = std::make_shared<CConcreteHandlerB>();
    std::shared_ptr<CHandler> handlerC = std::make_shared<CConcreteHandlerC>();

    handlerA->SetSuperior(handlerB);
    handlerB->SetSuperior(handlerC);

    std::default_random_engine dre(time(nullptr));
    std::uniform_int_distribution<> uid(0, 50);

    for (size_t index = 0; index < 20; ++index)
    {
        handlerA->HandlerRequest(uid(dre));
    }

    return 0;
}