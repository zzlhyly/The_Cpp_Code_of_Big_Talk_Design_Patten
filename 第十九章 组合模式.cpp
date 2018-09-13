#include <iostream>
#include <string>
#include <memory>
#include <vector>

class CComponent
{
public:
    explicit CComponent(const std::string &name)
        : m_name(name)
    {

    }

    virtual ~CComponent() = default;

    virtual void Add(const std::shared_ptr<CComponent> &com) = 0;
    virtual void Remove(const std::shared_ptr<CComponent> &com) = 0;
    virtual void Display(unsigned depth)const = 0;
protected:
    std::string m_name;
};

class CComposite : public CComponent
{
public:
    using CComponent::CComponent;

    virtual void Add(const std::shared_ptr<CComponent> &com)override
    {
        m_coms.push_back(com);
    }

    virtual void Remove(const std::shared_ptr<CComponent> &com)override
    {
        auto it = m_coms.cbegin();
        auto it_end = m_coms.cend();
        for (; it != it_end; ++it)
        {
            if (*it == com)
            {
                m_coms.erase(it);
                break;
            }
        }
    }

    virtual void Display(unsigned depth)const override
    {
        std::cout << std::string(depth, '-') << m_name << std::endl;
        for (auto com : m_coms)
        {
            com->Display(depth + 2);
        }
    }

private:
    std::vector<std::shared_ptr<CComponent>> m_coms;
};

class CLeaf : public CComponent
{
public:
    using CComponent::CComponent;

    virtual void Add(const std::shared_ptr<CComponent> &com)override
    {

    }

    virtual void Remove(const std::shared_ptr<CComponent> &com)override
    {

    }

    virtual void Display(unsigned depth)const
    {
        std::cout << std::string(depth, '-') << m_name << std::endl;
    }
};

int main()
{
    std::shared_ptr<CComponent> root = std::make_shared<CComposite>("zzl");
    root->Add(std::make_shared<CLeaf>("z"));
    root->Add(std::make_shared<CLeaf>("z"));
    root->Add(std::make_shared<CLeaf>("l"));

    std::shared_ptr<CComponent> comA = std::make_shared<CComposite>("hyly");
    comA->Add(std::make_shared<CLeaf>("h"));
    comA->Add(std::make_shared<CLeaf>("y"));
    comA->Add(std::make_shared<CLeaf>("l"));
    comA->Add(std::make_shared<CLeaf>("y"));
    root->Add(comA);

    std::shared_ptr<CComponent> comB = std::make_shared<CComposite>("xxx");
    comB->Add(std::make_shared<CLeaf>("x"));
    comB->Add(std::make_shared<CLeaf>("x"));
    comB->Add(std::make_shared<CLeaf>("x"));
    comA->Add(comB);

    root->Add(std::make_shared<CLeaf>("x"));

    std::shared_ptr<CLeaf> l = std::make_shared<CLeaf>("l");
    root->Add(l);
    root->Remove(l);

    root->Display(2);

    return 0;
}
