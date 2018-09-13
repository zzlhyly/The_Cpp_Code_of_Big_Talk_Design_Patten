#include <iostream>
#include <memory>

//////////////////////////////////////////////////////////////////////////
class CUser
{
public:
	virtual ~CUser() = default;
	virtual void SetUser() = 0;
	virtual void GetUser()const = 0;
};

class CHylyUser : public CUser
{
public:
	virtual void SetUser()override
	{
		std::cout << "CHylyUser SetUser" << std::endl;
	}

	virtual void GetUser()const override
	{
		std::cout << "CHylyUser GetUser" << std::endl;
	}
};

class CZzlUser : public CUser
{
public:
	virtual void SetUser()override
	{
		std::cout << "CZzlUser SetUser" << std::endl;
	}

	virtual void GetUser()const override
	{
		std::cout << "CZzlUser GetUser" << std::endl;
	}
};
//////////////////////////////////////////////////////////////////////////

class CDepartment
{
public:
	virtual ~CDepartment() = default;
	virtual void SetDepartment() = 0;
	virtual void GetDepartment()const = 0;
};

class CHylyDepartment : public CDepartment
{
	void SetDepartment()override
	{
		std::cout << "CHylyUser SetDepartment" << std::endl;
	}

	virtual void GetDepartment()const override
	{
		std::cout << "CHylyUser GetDepartment" << std::endl;
	}
};

class CZzlDepartment : public CDepartment
{
	void SetDepartment()override
	{
		std::cout << "CZzlDepartment SetDepartment" << std::endl;
	}

	virtual void GetDepartment()const override
	{
		std::cout << "CZzlDepartment GetDepartment" << std::endl;
	}
};
//////////////////////////////////////////////////////////////////////////

class CFactory
{
public:
	virtual ~CFactory() = default;
	virtual std::unique_ptr<CUser> CreateUser()const = 0;
	virtual std::unique_ptr<CDepartment> CreateDepartment()const = 0;
};

class CHylyFactory : public CFactory
{
public:
	virtual std::unique_ptr<CUser> CreateUser()const override
	{
		return std::make_unique<CHylyUser>();
	}

	virtual std::unique_ptr<CDepartment> CreateDepartment()const
	{
		return std::make_unique<CHylyDepartment>();
	}
};

class CZzlFactory : public CFactory
{
public:
	virtual std::unique_ptr<CUser> CreateUser()const override
	{
		return std::make_unique<CZzlUser>();
	}

	virtual std::unique_ptr<CDepartment> CreateDepartment()const
	{
		return std::make_unique<CZzlDepartment>();
	}
};
//////////////////////////////////////////////////////////////////////////

int main()
{
	std::unique_ptr<CFactory> upFactory = std::make_unique<CZzlFactory>();
	auto user = upFactory->CreateUser();
	auto department = upFactory->CreateDepartment();

	user->SetUser();
	user->GetUser();
	department->SetDepartment();
	department->GetDepartment();

	return 0;
}