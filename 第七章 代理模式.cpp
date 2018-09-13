#include <iostream>

class subject
{
public:
	virtual ~subject() = default;
	virtual void test()const = 0;
};

class real_subject : public subject
{
public:
	virtual void test()const override
	{
		std::cout << "real_subject" << std::endl;
	}
};

class proxy : public subject
{
public:
	proxy()
	{
		rs = new real_subject();
	}

	~proxy()
	{
		if (rs != nullptr)
		{
			delete rs;
		}
	}

	virtual void test()const override
	{
		std::cout << "proxy\t";
		rs->test();
	}
private:
	real_subject *rs = nullptr;
};

int main()
{
	proxy pr;
	pr.test();

	return 0;
}