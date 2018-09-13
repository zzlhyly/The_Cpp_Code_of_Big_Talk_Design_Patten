#include <iostream>

class CSingleton
{
public:
    static CSingleton* GetInstance()
    {
        if (sm_instance == nullptr)
        {
            sm_instance = new CSingleton();
        }

        return sm_instance;
    }

protected:
private:
    CSingleton() = default;

    static CSingleton* sm_instance;
};

CSingleton *CSingleton::sm_instance = nullptr;

int main()
{
    auto a = CSingleton::GetInstance();
    auto b = CSingleton::GetInstance();

    if (a == b)
    {
        std::cout << "same" << std::endl;
    }

    return 0;
}