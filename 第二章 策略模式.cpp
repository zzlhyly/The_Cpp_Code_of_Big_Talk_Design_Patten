#include <iostream>
#include <memory>

class cash_base
{
public:
	virtual ~cash_base() = default;
	virtual double GetResult(double total_money)const = 0;
};

class cash_normal : public cash_base
{
public:
	virtual double GetResult(double total_money)const override
	{
		return total_money;
	}
};

class cash_discount : public cash_base
{
public:
	explicit cash_discount(double discount)
		: m_discount(discount)
	{

	}

	virtual double GetResult(double total_money)const override
	{
		return total_money * m_discount;
	}

private:
	double m_discount;
};

class cash_back : public cash_base
{
public:
	cash_back(double cash_radix, double cash_revert)
		: m_cash_radix(cash_radix), m_cash_revert(cash_revert)
	{

	}

	virtual double GetResult(double total_money)const override
	{
		if (total_money >= m_cash_radix)
		{
			total_money -= (static_cast<unsigned>(total_money / m_cash_radix) * m_cash_revert);
		}
		
		return total_money;
	}
protected:

private:
	double m_cash_radix;
	double m_cash_revert;
};

class cash_context
{
public:
	explicit cash_context(cash_base *p_cash_base)
		: m_cash_base(p_cash_base)
	{

	}

	~cash_context()
	{
		if (m_cash_base != nullptr)
		{
			delete m_cash_base;
			m_cash_base = nullptr;
		}
	}

	double GetResult(double total_money)const
	{
		if (m_cash_base != nullptr)
		{
			return m_cash_base->GetResult(total_money);
		}
		else
		{
			return 0;
		}
	}

private:
	cash_base *m_cash_base = nullptr;
};

int main()
{
	unsigned commodity_num = 0;
	double commodity_price = 0.0;
	char calculate_cash_type = 0;

	while (true)
	{
		std::unique_ptr<cash_context> up_cash_context(nullptr);
		std::cout << "请输入优惠类型(A(不优惠)、B(打8折)、C(满每300减100)) : ";
		std::cin >> calculate_cash_type;
		if (calculate_cash_type == 'A')
		{
			up_cash_context.reset(new cash_context(new cash_normal()));
		}
		else if (calculate_cash_type == 'B')
		{
			up_cash_context.reset(new cash_context(new cash_discount(0.8)));
		}
		else if (calculate_cash_type == 'C')
		{
			up_cash_context.reset(new cash_context(new cash_back(300, 100)));
		}

		std::cout << "请输入商品数量：";
		std::cin >> commodity_num;

		std::cout << "请输入商品价格：";
		std::cin >> commodity_price;

		if (up_cash_context != nullptr)
		{
			std::cout << "总价格为：" << up_cash_context->GetResult(commodity_num * commodity_price) << "\n\n";
		}
		else
		{
			std::cout << "不支持的优惠类型\n\n";
		}	
	}

	return 0;
}