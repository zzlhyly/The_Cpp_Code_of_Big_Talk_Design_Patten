#include <vector>
#include <iostream>
#include <string>

template <typename T>
class CIterator
{
public:
    CIterator(const std::vector<T> &vec)
        : m_vec(vec)
    {

    }
    virtual ~CIterator() = default;
    virtual T GetFirst()const = 0;
    virtual T MoveNext() = 0;
    virtual bool IsDone()const = 0;
    virtual T GetItem()const = 0;
protected:
    std::vector<T> m_vec;
};

template <typename T>
class CConcreteIterator : public CIterator<T>
{
public:
    using CIterator::CIterator;

    virtual T GetFirst()const override
    {
        if (m_vec.empty())
        {
            return T();
        }
        else
        {
            return m_vec.at(0);
        }
    }

    virtual T MoveNext()override
    {
        ++m_current;
        if (m_current < m_vec.size())
        {
            return m_vec.at(m_current);
        }
        else
        {
            return T();
        }
    }

    virtual bool IsDone()const
    {
        return m_current >= m_vec.size() ? true : false;
    }

    virtual T GetItem()const
    {
        return m_vec.at(m_current);
    }

private:
    size_t m_current = 0;
};

int main()
{
    std::vector<std::string> vec{ "z", "z", "l", "h", "y", "l", "y" };
    CConcreteIterator<std::string> it(vec);

    auto value = it.GetFirst();
    while (!it.IsDone())
    {
        std::cout << it.GetItem() << std::endl;
        it.MoveNext();
    }


    return 0;
}