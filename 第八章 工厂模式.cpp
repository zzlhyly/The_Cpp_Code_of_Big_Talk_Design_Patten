#include <iostream>
#include <memory>

class COperation
{
public:
	virtual ~COperation() = default;
	virtual double CalculateOperation(double numA, double numB)const = 0;
};

class COperationAdd : public COperation
{
public:
	virtual double CalculateOperation(double numA, double numB)const override
	{
		return numA + numB;
	}
};

class COperationSub : public COperation
{
public:
	virtual double CalculateOperation(double numA, double numB)const override
	{
		return numA - numB;
	}
};

class COperationMul : public COperation
{
public:
	virtual double CalculateOperation(double numA, double numB)const override
	{
		return numA * numB;
	}
};

class COperationDiv : public COperation
{
public:
	virtual double CalculateOperation(double numA, double numB)const override
	{
		return numA / numB;
	}
};
//////////////////////////////////////////////////////////////////////////
class COperationFactory
{
public:
	virtual ~COperationFactory() = default;
	virtual std::unique_ptr<COperation> GetOperator()const = 0;
};

class COperationFactoryAdd : public COperationFactory
{
public:
	virtual std::unique_ptr<COperation> GetOperator()const override
	{
		return std::make_unique<COperationAdd>();
	}
};

class COperationFactorySub : public COperationFactory
{
public:
	virtual std::unique_ptr<COperation> GetOperator()const override
	{
		return std::make_unique<COperationSub>();
	}
};

class COperationFactoryMul : public COperationFactory
{
public:
	virtual std::unique_ptr<COperation> GetOperator()const override
	{
		return std::make_unique<COperationMul>();
	}
};

class COperationFactoryDiv : public COperationFactory
{
public:
	virtual std::unique_ptr<COperation> GetOperator()const override
	{
		return std::make_unique<COperationDiv>();
	}
};
//////////////////////////////////////////////////////////////////////////
int main()
{
	std::unique_ptr<COperationFactory> upFactory = std::make_unique<COperationFactoryAdd>();
	std::unique_ptr<COperation> up = upFactory->GetOperator();

	std::cout << up->CalculateOperation(1, 2) << std::endl;

	return 0;
}