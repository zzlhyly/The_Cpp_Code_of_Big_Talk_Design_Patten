#include <iostream>

class CTarget
{
public:
	virtual ~CTarget() = default;
	virtual void Request()const
	{
		std::cout << "CTarget\n";
	}
};

class CAdaptee
{
public:
	void SpecifiRequest()const
	{
		std::cout << "CAdaptee\n";
	}
};

class CAdapter : public CTarget
{
public:
	virtual void Request()const override
	{
		m_ap.SpecifiRequest();
	}
private:
	CAdaptee m_ap;
};

int main()
{
	CTarget *p = new CAdapter();
	p->Request();
	delete p;
	p = nullptr;

	return 0;
}