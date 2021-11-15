#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f; // 1.5 millisecond

class Timer {

public:
	void Tick();
	inline float getDeltaTime() { return m_DeltaTime; }
	inline static Timer* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();
	}

private:
	Timer() {}
	static Timer* s_Instance;
	float m_DeltaTime = TARGET_DELTATIME; // ���븳��ֵ����Ϊ��һ�μ����ֵ���ڵ�һ��ʹ�ô�ֵ֮��
	float m_LastTime;
};

#endif // TIMER_H