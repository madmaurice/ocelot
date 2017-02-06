
#pragma once

OC_NS_BG;

class FpsCounter
{
public:
    FpsCounter();

    // Need to be called on every frames
    void UpdateFrame(float runningTime);

    uint32 GetFps() const;
    float GetFrameTimeMs() const;

private:
    uint32 m_fps;
    uint32 m_frameCount;
    float m_elapsedTime;
};

OC_NS_END;