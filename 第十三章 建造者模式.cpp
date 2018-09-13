#include <iostream>
#include <memory>

class CBuilder
{
public:
	virtual ~CBuilder() = default;
	virtual void BuilderPartA()const = 0;
	virtual void BuilderPartB()const = 0;
	virtual void BuilderPartC()const = 0;
	virtual void BuilderPartD()const = 0;
	virtual void BuilderPartE()const = 0;
};

class CConcreteBuilderA : public CBuilder
{
public:
	virtual void BuilderPartA()const
	{
		std::cout << "ConcreteBuilderA  BuilderPartA\n";
	}

	virtual void BuilderPartB()const
	{
		std::cout << "ConcreteBuilderA  BuilderPartB\n";
	}

	virtual void BuilderPartC()const
	{
		std::cout << "ConcreteBuilderA  BuilderPartC\n";
	}

	virtual void BuilderPartD()const
	{
		std::cout << "ConcreteBuilderA  BuilderPartD\n";
	}

	virtual void BuilderPartE()const
	{
		std::cout << "ConcreteBuilderA  BuilderPartE\n";
	}
};

class CConcreteBuilderB : public CBuilder
{
public:
	virtual void BuilderPartA()const
	{
		std::cout << "ConcreteBuilderB\nBuilderPartA\n";
	}

	virtual void BuilderPartB()const
	{
		std::cout << "ConcreteBuilderB\nBuilderPartB\n";
	}

	virtual void BuilderPartC()const
	{
		std::cout << "ConcreteBuilderB\nBuilderPartC\n";
	}

	virtual void BuilderPartD()const
	{
		std::cout << "ConcreteBuilderB\nBuilderPartD\n";
	}

	virtual void BuilderPartE()const
	{
		std::cout << "ConcreteBuilderB\nBuilderPartE\n";
	}
};
//////////////////////////////////////////////////////////////////////////

class CDirector
{
public:
	explicit CDirector(CBuilder *pb)
		: m_pb(pb)
	{

	}

	void Build()const
	{
		m_pb->BuilderPartA();
		m_pb->BuilderPartB();
		m_pb->BuilderPartC();
		m_pb->BuilderPartD();
		m_pb->BuilderPartE();
	}
private:
	std::unique_ptr<CBuilder> m_pb = nullptr;
};
//////////////////////////////////////////////////////////////////////////

int main()
{
	CDirector dta(new CConcreteBuilderA());
	dta.Build();
	std::cout << "\n\n";

	CDirector dtb(new CConcreteBuilderB());
	dtb.Build();

	return 0;
}