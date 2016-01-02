
#include "FpsCounter.h"

OC_NS_BG;

FpsCounter::FpsCounter()
    : m_fps(0)
    , m_frameCount(0)
    , m_elapsedTime(0)
{
}

void FpsCounter::UpdateFrame(float runningTime)
{
    ++m_frameCount;

    // Compute average over 1 seconds period
    if ( (runningTime - m_elapsedTime) >= 1.0f)
    {
        // Reset frame count for next average
        m_fps = m_frameCount;
        m_frameCount = 0;

        m_elapsedTime += 1.0f;
    }
}

uint32 FpsCounter::GetFps() const
{
    return m_fps;
}

float FpsCounter::GetFrameTimeMs() const
{
    return m_fps > 0 ? 1000 / (float)m_fps : 0;
}

OC_NS_END;