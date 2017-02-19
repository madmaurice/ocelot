
#pragma once

OC_NS_BG;

class Timer
{
public:
	Timer();

    // Total time in seconds (without paused duration)
	float GetElapsed() const;

    // Delta time between ticks in seconds
	float GetDelta() const;

    // Delta time between ticks in milliseconds
	float GetDeltaMs() const;

	void Start();
	void Stop();
	void Reset();

	void Tick();

private:
	double m_secondsPerCount;
	double m_deltaTime;

	int64 m_baseTime;
	int64 m_pausedTime;
	int64 m_stopTime;
	int64 m_prevTime;
	int64 m_currentTime;

	bool m_stopped;
};

OC_NS_END;