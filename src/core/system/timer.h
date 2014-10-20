
#pragma once

class Timer
{
public:
	Timer();

    // Total time in seconds (without paused duration)
	float getElapsed() const;

    // Delta time between ticks in seconds
	float getDelta() const;

	void start();
	void stop();
	void reset();

	void tick();

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