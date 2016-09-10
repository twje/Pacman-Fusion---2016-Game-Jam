#ifndef _TWEEN_
#define _TWEEN_

#include <iostream>

using TweenFunc = std::function<float(float, float, float, float)>;

inline float linear(float timePassed, float start, float distance, float duration)
{
    return distance * timePassed / duration + start;
}

//******
// Tween
//******
class Tween
{
private:
    float m_start;
    float m_finish;
    float m_distance;
    float m_current;
    float m_totalDistance;
    float m_timePassed;
    bool m_isFinished;
    TweenFunc m_tweenFunc;

public:
    Tween(){}

    Tween(float l_start, float l_finish, float l_totalDuration, TweenFunc l_tweenFunc = linear)
    {
        reset(l_start, l_finish, l_totalDuration, l_tweenFunc);
    };

    void reset(float l_start, float l_finish, float l_totalDuration, TweenFunc l_tweenFunc = linear)
    {
        m_start = l_start;
        m_finish = l_finish;
        m_totalDistance = l_totalDuration;
        m_tweenFunc = l_tweenFunc;
        m_isFinished = false;
        m_timePassed = 0;
        m_distance = l_finish - l_start;
    }

    void update(float dt)
    {
        m_timePassed += dt;
        m_current = m_tweenFunc(m_timePassed, m_start, m_distance, m_totalDistance);

        if (m_timePassed > m_totalDistance)
        {
            m_current = m_start + m_distance;
            m_isFinished = true;
        }
    }

    float value(){ return m_current; }

    bool isFinished(){ return m_isFinished; }
};

#endif // _TWEEN_
