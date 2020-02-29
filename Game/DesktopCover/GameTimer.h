#pragma once


#include <windows.h>
//GetTickCount();

class CGameTimer {
public:
	explicit CGameTimer(unsigned int timeout = 3000,//��Ϸ��ʱʱ��
		unsigned int timeval = 300) //ʱ����
		: m_timeout(timeout), m_timeval(timeval)
	{
	}
	virtual ~CGameTimer() {
	}

	//�����ܵĳ�ʱʱ��
	void SetTimeout(unsigned int timeout) {}
	//�ж��Ƿ�ʱ����ʱ�䣩
	bool IsTimeout() {
		return (GetTickCount() - m_timeStart) >= m_timeout;
	}
	//�ж��Ƿ񵽴�ʱ������������ˣ��Ƿ����
	bool IsTimeval(bool bUpdate = true) {
		if (GetTickCount() - m_timeStart >= m_timeout) {
			if (bUpdate) {
				m_timeLast = GetTickCount();
				++m_times;
			}
			return true;
		}
		return false;
	}

	size_t GetTimes() const {}
private:
	unsigned int m_timeStart{::GetTickCount()};//��ʱ����ʼʱ��
	unsigned int m_timeout;//�ܵĳ�ʱʱ��
	unsigned int m_timeLast{m_timeStart};//��һ�θ���ʱ��
	unsigned int m_timeval{300};//ʱ����
	unsigned int m_times{0};//����IsTimeval(trueע��)�Ĵ���
};


/*

CGameTime timer(5000, 100);
if(timer.IsTimeout()){
}
if(timer.IsTimeval()){
}

*/

