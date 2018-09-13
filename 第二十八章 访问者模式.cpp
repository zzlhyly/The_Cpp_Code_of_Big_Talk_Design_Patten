#include <iostream>
#include <memory>
#include <vector>

class CConcreteElementA;
class CConcreteElementB;

class CVistor
{
public:
    virtual ~CVistor() = default;
    virtual void VisitConcreteElementA(CConcreteElementA *concreteElementA)const = 0;
    virtual void VisitConcreteElementB(CConcreteElementB *concreteElementB)const = 0;
};

class CElement
{
public:
    virtual ~CElement() = default;
    virtual void Accept(const std::shared_ptr<CVistor> &vistor)= 0;
};

class CConcreteElementA : public CElement
{
public:
    virtual void Accept(const std::shared_ptr<CVistor> &vistor)override
    {
        vistor->VisitConcreteElementA(this);
    }
};

class CConcreteElementB : public CElement
{
public:
    virtual void Accept(const std::shared_ptr<CVistor> &vistor)override
    {
        vistor->VisitConcreteElementB(this);
    }
};

class CConcreteVistorA : public CVistor
{
public:
    virtual void VisitConcreteElementA(CConcreteElementA *concreteElementA)const override
    {
        std::cout << "CConcreteElementA CConcreteVistorA" << std::endl;
    }

    virtual void VisitConcreteElementB(CConcreteElementB *concreteElementB)const override
    {
        std::cout << "CConcreteElementB CConcreteVistorA" << std::endl;
    }
};

class CConcreteVistorB : public CVistor
{
public:
    virtual void VisitConcreteElementA(CConcreteElementA *concreteElementA)const override
    {
        std::cout << "CConcreteElementA CConcreteVistorB" << std::endl;
    }

    virtual void VisitConcreteElementB(CConcreteElementB *concreteElementB)const override
    {
        std::cout << "CConcreteElementB CConcreteVistorB" << std::endl;
    }
};

class CObjectStructure
{
public:
    void Attach(std::shared_ptr<CElement> element)
    {
        m_elements.push_back(element);
    }

    void detach(std::shared_ptr<CElement> elment)
    {
        auto it = m_elements.begin();
        while (it != m_elements.end())
        {
            if (*it == elment)
            {
                it = m_elements.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void accept(std::shared_ptr<CVistor> vistor)
    {
        for (auto element : m_elements)
        {
            element->Accept(vistor);
        }
    }

private:
    std::vector<std::shared_ptr<CElement>> m_elements;
};

int main()
{
    CObjectStructure os;
    os.Attach(std::make_shared<CConcreteElementA>());
    os.Attach(std::make_shared<CConcreteElementB>());

    std::shared_ptr<CConcreteVistorA> va = std::make_shared<CConcreteVistorA>();
    std::shared_ptr<CConcreteVistorB> vb = std::make_shared<CConcreteVistorB>();

    os.accept(va);
    os.accept(vb);

    return 0;
}