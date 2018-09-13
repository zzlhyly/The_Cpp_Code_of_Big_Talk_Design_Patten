#include <iostream>
#include <vector>
#include <string>

class CSubject;
class CObserver
{
public:
	explicit CObserver(CSubject *subject)
		: m_subject(subject)
	{

	}

	virtual ~CObserver() = default;
	virtual void Update() = 0;
protected:
	CSubject *m_subject;
};

class CSubject
{
public:
	virtual ~CSubject() = default;
	void Attach(CObserver *observer)
	{
		m_observers.push_back(observer);
	}

	void detach(CObserver *observer)
	{
		auto it = m_observers.begin();
		while (it != m_observers.end())
		{
			if (*it == observer)
			{
				it = m_observers.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	void Notify()
	{
		for (auto observer : m_observers)
		{
			observer->Update();
		}
	}

	void SetState(const std::string &state)
	{
		m_subject_state = state;
	}

	std::string GetState()const
	{
		return m_subject_state;
	}
private:
	std::string m_subject_state;
	std::vector<CObserver*> m_observers;
};

class CConcreteObserver : public CObserver
{
public:
	CConcreteObserver(CSubject *subject, const std::string &state)
		: CObserver(subject), m_observer_state(state)
	{

	}

	virtual void Update() override
	{
		if (m_subject != nullptr)
		{
			m_observer_state = m_subject->GetState();
		}
		
		std::cout << "当前观察者状态为：" << m_observer_state << "\n";
	}
private:
	std::string m_observer_state;
};


int main()
{
	CSubject sub;
	CConcreteObserver obA(&sub, "A");
	CConcreteObserver obB(&sub, "B");
	CConcreteObserver obC(&sub, "C");
	CConcreteObserver obD(&sub, "D");
	
	sub.Attach(&obA);
	sub.Attach(&obB);
	sub.Attach(&obC);
	sub.Attach(&obD);

	sub.detach(&obB);

	sub.SetState("FF");

	sub.Notify();

	return 0;
}