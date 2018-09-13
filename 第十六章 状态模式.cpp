#include <iostream>
#include <memory>

/*
class CWork
{
public:
	void SetHour(int hour)
	{
		m_hour = hour;
	}

	void SetTaskFinishFlag(bool task_finish_flag)
	{
		m_task_finish_flag = task_finish_flag;
	}

	void WriteProgram()const
	{
		if (m_hour < 12)
		{
			std::cout << "morning\n";
		}
		else if (m_hour < 13)
		{
			std::cout << "noon\n";
		}
		else if (m_hour < 18)
		{
			std::cout << "afternoon\n";
		}
		else
		{
			if (m_task_finish_flag)
			{
				std::cout << "evening off duty\n";
			}
			else
			{
				if (m_hour < 21)
				{
					std::cout << "evening overtime\n";
				}
				else
				{
					std::cout << "evening sleep\n";
				}
			}
		}
	}

protected:
private:
	int m_hour = 0;
	bool m_task_finish_flag = false;
};
*/

class CWork;
class CState
{
public:
	virtual ~CState() = default;
	virtual void Handle(CWork *wk) = 0;
};

class CWork
{
public:
	void SetHour(int hour)
	{
		m_hour = hour;
	}

	int GetHour()const
	{
		return m_hour;
	}

	void SetTaskFinishFlag(bool task_finish_flag)
	{
		m_task_finish_flag = task_finish_flag;
	}

	bool GetTaskFinishFlag()const
	{
		return m_task_finish_flag;
	}

	void SetState(std::unique_ptr<CState> state)
	{
		m_state.swap(std::move(state));
	}

	void WriteProgram()
	{
		m_state->Handle(this);
	}

private:
	int m_hour = 0;
	bool m_task_finish_flag = false;
	std::unique_ptr<CState> m_state = nullptr;
};

class CSleepState : public CState
{
public:
	virtual void Handle(CWork *wk)override
	{
		std::cout << "sleep\n";
	}
};

class CRestState : public CState
{
public:
	virtual void Handle(CWork *wk)override
	{
		std::cout << "rest\n";
	}
};

class CEveningState : public CState
{
public:
	virtual void Handle(CWork *wk)override
	{
		if (wk != nullptr)
		{
			if (wk->GetTaskFinishFlag())
			{
				wk->SetState(std::make_unique<CRestState>());
				wk->WriteProgram();
			}
			else
			{
				if (wk->GetHour() < 21)
				{
					std::cout << "evening overtime\n";
				}
				else
				{
					wk->SetState(std::make_unique<CSleepState>());
					wk->WriteProgram();
				}
			}
		}
	}
};

class CAfternoonState : public CState
{
public:
	virtual void Handle(CWork *wk)override
	{
		if (wk != nullptr)
		{
			if (wk->GetHour() < 18)
			{
				std::cout << "afternoon\n";
			}
			else
			{
				wk->SetState(std::make_unique<CEveningState>());
				wk->WriteProgram();
			}
		}
	}
};

class CNoonState : public CState
{
public:
	virtual void Handle(CWork *wk)override
	{
		if (wk != nullptr)
		{
			if (wk->GetHour() < 13)
			{
				std::cout << "noon\n";
			}
			else
			{
				wk->SetState(std::make_unique<CAfternoonState>());
				wk->WriteProgram();
			}
		}
	}
};

class CMorningState : public CState
{
public:
	virtual void Handle(CWork *wk)override
	{
		if (wk != nullptr)
		{
			if (wk->GetHour() < 12)
			{
				std::cout << "morning\n";
			}
			else
			{
				wk->SetState(std::make_unique<CNoonState>());
				wk->WriteProgram();
			}
		}
	}
};

int main()
{
	CWork wk;
	wk.SetState(std::make_unique<CMorningState>());
	wk.SetHour(8);
	wk.WriteProgram();
	wk.SetHour(10);
	wk.WriteProgram();
	wk.SetHour(12);
	wk.WriteProgram();
	wk.SetHour(13);
	wk.WriteProgram();
	wk.SetHour(15);
	wk.WriteProgram();
	wk.SetHour(18);

	wk.SetTaskFinishFlag(false);
	wk.WriteProgram();

	wk.SetHour(19);
	wk.WriteProgram();
	wk.SetHour(20);
	wk.WriteProgram();
	wk.SetHour(21);
	wk.WriteProgram();
	return 0;
}