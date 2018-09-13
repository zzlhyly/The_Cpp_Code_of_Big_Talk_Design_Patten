#include <iostream>
#include <string>
#include <memory>

struct WorkExperience
{
	std::string m_workDate = "";
	std::string m_company = "";
};

class CResume
{
public:
	explicit CResume(const std::string &name)
		: m_name(name)
	{
		m_workExperience = std::make_shared<WorkExperience>();
	}

	void SetPersonalInfo(const std::string &sex, const std::string &age)
	{
		m_sex = sex;
		m_age = age;
	}

	void SetWorkExperience(const std::string &workdDate, const std::string &company)
	{
		m_workExperience->m_workDate = workdDate;
		m_workExperience->m_company = company;
	}

	void Display()const
	{
		std::cout << m_name << "\t" << m_sex << "\t" << m_age << "\n";
		std::cout << "工作经历：" << m_workExperience->m_workDate << "\t" << m_workExperience->m_company << std::endl;
	}

private:
	std::string m_name = "";
	std::string m_sex = "";
	std::string m_age = "";
	std::shared_ptr<WorkExperience> m_workExperience = nullptr;
};

int main()
{
	CResume resumeA("zzl");
	resumeA.SetPersonalInfo("男", "25");
	resumeA.SetWorkExperience("1997-2005", "XX公司");

	CResume resumeB(resumeA);
	resumeB.SetWorkExperience("2005-2008", "YY公司");

	CResume resumeC(resumeA);
	resumeC.SetWorkExperience("2008-2011", "ZZ公司");

	resumeA.Display();
	resumeB.Display();
	resumeC.Display();

	return 0;
}