#include <iostream>
//////////////////////////////////////////////////////////////////////////
class COperationA
{
public:
	void OperationA()const
	{
		std::cout << "OperationA\n";
	}
};

class COperationB
{
public:
	void OperationB()const
	{
		std::cout << "OperationB\n";
	}
};

class COperationC
{
public:
	void OperationC()const
	{
		std::cout << "OperationC\n";
	}
};

class COperationD
{
public:
	void OperationD()const
	{
		std::cout << "OperationD\n";
	}
};

class COperationE
{
public:
	void OperationE()const
	{
		std::cout << "OperationE\n";
	}
};
//////////////////////////////////////////////////////////////////////////
class CFacade
{
public:
	void FacadeA()const
	{
		m_oa.OperationA();
		m_oc.OperationC();
		m_od.OperationD();
	}

	void FacadeB()const
	{
		m_ob.OperationB();
		m_oa.OperationA();
		m_oe.OperationE();
	}

private:
	COperationA m_oa;
	COperationB m_ob;
	COperationC m_oc;
	COperationD m_od;
	COperationE m_oe;
};
//////////////////////////////////////////////////////////////////////////
int main()
{
	CFacade cf;
	cf.FacadeA();
	std::cout << "\n\n";
	cf.FacadeB();

	return 0;
}