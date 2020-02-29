#pragma once


#include <windows.h>
//GetTickCount();

class CGameTimer {
public:
	explicit CGameTimer(unsigned int timeout = 3000,//游戏超时时间
		unsigned int timeval = 300) //时间间隔
		: m_timeout(timeout), m_timeval(timeval)
	{
	}
	virtual ~CGameTimer() {
	}

	//设置总的超时时间
	void SetTimeout(unsigned int timeout) {}
	//判断是否超时（总时间）
	bool IsTimeout() {
		return (GetTickCount() - m_timeStart) >= m_timeout;
	}
	//判断是否到达时间间隔：如果到了，是否更新
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
	unsigned int m_timeStart{::GetTickCount()};//计时器开始时间
	unsigned int m_timeout;//总的超时时间
	unsigned int m_timeLast{m_timeStart};//上一次更新时间
	unsigned int m_timeval{300};//时间间隔
	unsigned int m_times{0};//符合IsTimeval(true注意)的次数
};


/*

CGameTime timer(5000, 100);
if(timer.IsTimeout()){
}
if(timer.IsTimeval()){
}

*/

