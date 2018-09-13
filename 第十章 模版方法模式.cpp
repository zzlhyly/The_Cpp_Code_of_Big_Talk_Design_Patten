#include <iostream>
#include <memory>

class CAbstractClass
{
public:
	virtual ~CAbstractClass() = default;
	void TemplateMethod()
	{
		PrimitiveOperationA();
		PrimitiveOperationB();
		PrimitiveOperationC();
	}
protected:
	virtual void PrimitiveOperationA()const = 0;
	virtual void PrimitiveOperationB()const = 0;
	virtual void PrimitiveOperationC()const = 0;
};

class CConcreteClassA : public CAbstractClass
{
protected:
	virtual void PrimitiveOperationA()const override
	{
		std::cout << "z\t";
	}

	virtual void PrimitiveOperationB()const override
	{
		std::cout << "z\t";
	}

	virtual void PrimitiveOperationC()const override
	{
		std::cout << "l\n";
	}
};

class CConcreteClassB : public CAbstractClass
{
protected:
	virtual void PrimitiveOperationA()const override
	{
		std::cout << "Z\n";
	}

	virtual void PrimitiveOperationB()const override
	{
		std::cout << "Z\n";
	}

	virtual void PrimitiveOperationC()const override
	{
		std::cout << "L\n";
	}
};

int main()
{
	std::unique_ptr<CAbstractClass> up = std::make_unique<CConcreteClassA>();
	up->TemplateMethod();

	up.reset(new CConcreteClassB());
	up->TemplateMethod();

	return 0;
}