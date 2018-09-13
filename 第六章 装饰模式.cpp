#include <iostream>
#include <string>
#include <memory>

class CPerson
{
public:
	CPerson() = default;
	explicit CPerson(const std::string &name)
		: m_name(name)
	{

	}

	explicit CPerson(std::string &&name)
		: m_name(std::move(name))
	{

	}

	virtual void Show()const
	{
		std::cout << "装扮的" << m_name << std::endl;
	}

private:
	std::string m_name;
};

class CFinery : public CPerson
{
public:
	void Decorate(std::shared_ptr<CPerson> person)
	{
		m_person.swap(person);
	}

	virtual void Show()const override
	{
		if (m_person != nullptr)
		{
			m_person->Show();
		}
	}


private:
	std::shared_ptr<CPerson> m_person = nullptr;
};

class CTShirts : public CFinery
{
public:
	virtual void Show()const override 
	{
		std::cout << "大T恤\t";
		CFinery::Show();
	}
};

class CBigTrouser : public CFinery
{
public:
	virtual void Show()const override
	{
		std::cout << "垮裤\t";
		CFinery::Show();
	}
};

class CSneakers : public CFinery
{
public:
	virtual void Show()const override
	{
		std::cout << "破球鞋\t";
		CFinery::Show();
	}
};

class CSuit : public CFinery
{
public:
	virtual void Show()const override
	{
		std::cout << "西装\t";
		CFinery::Show();
	}
};

class CTie : public CFinery
{
public:
	virtual void Show()const override
	{
		std::cout << "领带\t";
		CFinery::Show();
	}
};

class CLeatherShoes : public CFinery
{
public:
	virtual void Show()const override
	{
		std::cout << "皮鞋\t";
		CFinery::Show();
	}
};

int main()
{
	std::shared_ptr<CPerson> zzl = std::make_shared<CPerson>("zzl");
	std::cout << "第一种装扮：\n";

	std::shared_ptr<CSneakers> sk = std::make_shared<CSneakers>();
	std::shared_ptr<CBigTrouser> bt = std::make_shared<CBigTrouser>();
	std::shared_ptr<CTShirts> ts = std::make_shared<CTShirts>();

	sk->Decorate(zzl);
	bt->Decorate(sk);
	ts->Decorate(bt);
	ts->Show();

	std::cout << "第二种装扮：\n";
	std::shared_ptr<CLeatherShoes> ls = std::make_shared<CLeatherShoes>();
	std::shared_ptr<CTie> ti = std::make_shared<CTie>();
	std::shared_ptr<CSuit> su = std::make_shared<CSuit>();

	ls->Decorate(zzl);
	ti->Decorate(ls);
	su->Decorate(ti);
	su->Show();

	std::cout << "第三种装扮：\n";
	sk->Decorate(zzl);
	ls->Decorate(sk);
	bt->Decorate(ls);
	ti->Decorate(bt);
	ti->Show();

	return 0;
}