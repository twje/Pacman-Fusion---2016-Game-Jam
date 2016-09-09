#ifndef _ANIMATION_
#define _ANIMATION_

#include <vector>

//**********
// Animation
//**********
class Animation
{
private:
    std::vector<int> m_frames;
    float m_loop;
    float m_spf;
    float m_time;
    int m_index;

public:
    Animation(std::vector<int> l_frames, bool l_loop, float l_spf):
    m_frames(l_frames),
    m_loop(l_loop),
    m_spf(l_spf),
    m_time(0),
    m_index(0)
    {}

    void update(float dt)
    {
        m_time += dt;
        if (m_time >= m_spf) {
            m_index += 1;
            m_time = 0;

            if (m_index >= m_frames.size()) {
                if (m_loop) {
                    m_index = 0;
                } else {
                    m_index = m_frames.size() - 1;
                }
            }
        }
    }

    void setFrames(std::vector<int> l_frames)
    {
        m_frames = l_frames;
    }

    int getFrame()
    {
        return m_frames[m_index];
    }

    bool isFinished()
    {
        return (!m_loop && m_index == m_frames.size() - 1);
    }
};

#endif // _ANIMATION_
