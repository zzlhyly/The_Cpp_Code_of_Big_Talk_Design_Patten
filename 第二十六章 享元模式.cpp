#include <iostream>
#include <memory>
#include <map>
#include <string>

class CFlyWeight
{
public:
    virtual ~CFlyWeight() = default;
    virtual void Operation(int extrinsic_state)const = 0;
};

class CConcreteFlyWeight : public CFlyWeight
{
public:
    virtual void Operation(int extrinsic_state)const override
    {
        std::cout << "CConcreteFlyWeight\t" << extrinsic_state << std::endl;
    }
};

class CUnsharedConcreteFlyWeight : public CFlyWeight
{
public:
    virtual void Operation(int extrinsic_state)const override
    {
        std::cout << "CUnsharedConcreteFlyWeight\t" << extrinsic_state << std::endl;
    }
};

class CFlyWeightFactory
{
public:
    CFlyWeightFactory()
    {
        m_fly_weights["xx"] = std::make_shared<CConcreteFlyWeight>();
        m_fly_weights["yy"] = std::make_shared<CConcreteFlyWeight>();
        m_fly_weights["zz"] = std::make_shared<CConcreteFlyWeight>();
    }

    std::shared_ptr<CFlyWeight> GetFlyWeight(const std::string &stringKey)
    {
        if (m_fly_weights.find(stringKey) != m_fly_weights.cend())
        {
            return m_fly_weights[stringKey];
        }
        else
        {
            m_fly_weights[stringKey] = std::make_shared<CConcreteFlyWeight>();
            return m_fly_weights[stringKey];
        }
    }

    size_t GetFlyWeightCount()const
    {
        return m_fly_weights.size();
    }

private:
    std::map<std::string, std::shared_ptr<CFlyWeight>> m_fly_weights;
};

int main()
{
    int extrinsic_state = 22;
    CFlyWeightFactory fly_weight_factory;
    
    auto fx = fly_weight_factory.GetFlyWeight("xx");
    fx->Operation(extrinsic_state--);

    auto fy = fly_weight_factory.GetFlyWeight("yy");
    fy->Operation(extrinsic_state--);

    auto fz = fly_weight_factory.GetFlyWeight("zz");
    fy->Operation(extrinsic_state--);

    auto fxx = fly_weight_factory.GetFlyWeight("xx");
    fx->Operation(extrinsic_state--);

    auto fyy = fly_weight_factory.GetFlyWeight("yy");
    fy->Operation(extrinsic_state--);

    auto fzz = fly_weight_factory.GetFlyWeight("zz");
    fy->Operation(extrinsic_state--);

    auto fxxx = fly_weight_factory.GetFlyWeight("xx");
    fx->Operation(extrinsic_state--);

    auto fyyy = fly_weight_factory.GetFlyWeight("yy");
    fy->Operation(extrinsic_state--);

    auto fzzz = fly_weight_factory.GetFlyWeight("zz");
    fy->Operation(extrinsic_state--);

    CUnsharedConcreteFlyWeight ucfw;
    ucfw.Operation(extrinsic_state);

    std::cout << fly_weight_factory.GetFlyWeightCount() << std::endl;

    return 0;
}