#include <iostream>
#include <memory>

class arithmetic_operation_base
{
public:
	virtual ~arithmetic_operation_base() = default;

	virtual double GetResult(double operation_num_a, double operation_num_b)const = 0;
};

class arithmetic_operation_add : public arithmetic_operation_base
{
	virtual double GetResult(double operation_num_a, double operation_num_b)const override
	{
		return operation_num_a + operation_num_b;
	}
};

class arithmetic_operation_subtract : public arithmetic_operation_base
{
	virtual double GetResult(double operation_num_a, double operation_num_b)const override
	{
		return operation_num_a - operation_num_b;
	}
};

class arithmetic_operation_mutiply : public arithmetic_operation_base
{
	virtual double GetResult(double operation_num_a, double operation_num_b)const override
	{
		return operation_num_a * operation_num_b;
	}
};

class arithmetic_operation_division : public arithmetic_operation_base
{
	virtual double GetResult(double operation_num_a, double operation_num_b)const override
	{
		return operation_num_a / operation_num_b;
	}
};

std::unique_ptr<arithmetic_operation_base> GetOperation(char operation_symbol)
{
	std::unique_ptr<arithmetic_operation_base> operation_base(nullptr);
	switch (operation_symbol)
	{
	case '+':
	{
		operation_base = std::make_unique<arithmetic_operation_add>();
	}
	break;
	case '-':
	{
		operation_base = std::make_unique<arithmetic_operation_subtract>();
	}
	break;
	case '*':
	{
		operation_base = std::make_unique<arithmetic_operation_mutiply>();
	}
	break;
	case '/':
	{
		operation_base = std::make_unique<arithmetic_operation_division>();
	}
	break;
	default:
	{
		//输入了不支持的运算符
	}
	break;
	}

	return operation_base;
}

int main()
{
	double operation_num_a = 0.0;
	double operation_num_b = 0.0;
	char operation_symbol = 0;
	std::unique_ptr<arithmetic_operation_base> operation_base;
	while (true)
	{
		std::cout << "请输入算式的第一个数：";
		std::cin >> operation_num_a;
		std::cout << "请输入算式的第二个数：";
		std::cin >> operation_num_b;
		std::cout << "请输入算式的运算符(+, -, *, /)：";
		std::cin >> operation_symbol;

		operation_base.swap(GetOperation(operation_symbol));
		if (operation_base == nullptr)
		{
			if (operation_symbol == '/')
			{
				std::cout << "除法运算中除数不能为0！\n";
			}
			else
			{
				std::cout << "输入了不支持的运算符\n";
			}
		}
		else
		{
			std::cout << "计算结果为：" << operation_base->GetResult(operation_num_a, operation_num_b) << "\n";
		}

		std::cout << "算式处理完成\n\n" << std::flush;
	}

	return 0;
}