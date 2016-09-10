#ifndef _GAMECAMERA_

#include <iostream>
#include "SharedContext.h"
#include "Tween.hpp"

//****************
// ViewPortStateID
//****************
enum class ViewPortStateID
{
    ACTIVE_GREEN,
    ACTIVE_RED,
    ACTIVE_BLUE,
    ACTIVE_START
};

//***********
// ViewPortID
//***********
enum class ViewPortID
{
    GREEN,
    RED,
    BLUE
};

//***********
// GameCamera
//***********
class GameCamera
{
private:
    SharedContext* m_context;

    std::map<ViewPortStateID, std::vector<int>> m_sliders;
    std::map<ViewPortID, sf::View> m_views;
    ViewPortStateID m_currentState;
    int m_currentSlider1;
    int m_currentSlider2;
    float m_duration;
    Tween m_slider1;
    Tween m_slider2;

public:
    GameCamera(SharedContext* l_context, float l_scaleRatio, float l_duration):
    m_context(l_context),
    m_duration(l_duration)
    {
        int portWidth = l_context->m_wind->GetWindowSize().x / 3.f;
        int expand = portWidth * l_scaleRatio;
        int unexpand = (l_context->m_wind->GetWindowSize().x - expand) / 2.f;

        // Init sliders
        m_sliders[ViewPortStateID::ACTIVE_START] = { portWidth, 2 * portWidth };
        m_sliders[ViewPortStateID::ACTIVE_RED] = {expand, expand + unexpand };
        m_sliders[ViewPortStateID::ACTIVE_GREEN] = {unexpand, unexpand + expand};
        m_sliders[ViewPortStateID::ACTIVE_BLUE] = {unexpand, 2 * unexpand};

        m_currentSlider1 = m_sliders[ViewPortStateID::ACTIVE_START][0];
        m_currentSlider2 = m_sliders[ViewPortStateID::ACTIVE_START][1];

        // Set views
        m_views[ViewPortID::RED] = sf::View();
        m_views[ViewPortID::GREEN] = sf::View();
        m_views[ViewPortID::BLUE] = sf::View();

        // Init sliders
        m_slider1.reset(portWidth, portWidth, 1.0f);
        m_slider2.reset(2*portWidth, 2*portWidth, 1.0f);
        updateViewPorts();
    }

    void update(float dt)
    {

    }

    bool isExpanding() { return m_slider1.isFinished() && m_slider2.isFinished(); }

    void update(float dt)
    {
        if (isExpanding())
        {
            m_slider1.update(dt);
            m_slider2.update(dt);
            updateViewPorts();
        }
    }

    void setViewPortState(ViewPortStateID l_stateId)
    {
        if (l_stateId == m_currentState){ return; }

        m_slider1.reset(m_currentSlider1, m_sliders[l_stateId][0], m_duration);
        m_slider2.reset(m_currentSlider2, m_sliders[l_stateId][1], m_duration);

        // reset state
        m_currentState = l_stateId;
        m_currentSlider1 = m_sliders[l_stateId][0];
        m_currentSlider2 = m_sliders[l_stateId][1];
    }

    // Getters
    sf::View& getView(int id)
    {
        //std::cout << "called: " << id << std::endl;
        return m_views[(ViewPortID)id];
    }

private:
    void updateViewPorts()
    {
        updateViewPort0();
        updateViewPort1();
        updateViewPort2();
    }

    void updateViewPort0() // RED
    {
        sf::View& view = m_views[ViewPortID::RED];

        float winWidth = m_context->m_wind->GetWindowSize().x;
        float winHeight = m_context->m_wind->GetWindowSize().y;

        float portWidth = m_slider1.value();
        float portHeight = winHeight;

        float l = 0;
        float t = 0;
        float w = portWidth/winWidth;
        float h = portHeight/winHeight;
        sf::FloatRect port(l, t, w, h);

        view.setViewport(port);
    }

    void updateViewPort1() // GREEN
    {
        sf::View view = m_views[ViewPortID::GREEN];

        float winWidth = m_context->m_wind->GetWindowSize().x;
        float winHeight = m_context->m_wind->GetWindowSize().y;

        float portWidth = m_slider2.value() - m_slider1.value();
        float portHeight = winHeight;

        float l = m_slider1.value() / winWidth;
        float t = 0;
        float w = portWidth/winWidth;
        float h = portHeight/winHeight;
        sf::FloatRect port(l, t, w, h);

        view.setViewport(port);

        m_views[ViewPortID::GREEN] = view;
    }

    void updateViewPort2() // BLUE
    {
        sf::View& view = m_views[ViewPortID::BLUE];

        float winWidth = m_context->m_wind->GetWindowSize().x;
        float winHeight = m_context->m_wind->GetWindowSize().y;

        float portWidth = winWidth - m_slider2.value();
        float portHeight = winHeight;

        float l = m_slider2.value() / winWidth;
        float t = 0;
        float w = portWidth/winWidth;
        float h = portHeight/winHeight;
        sf::FloatRect port(l, t, w, h);

        view.setViewport(port);
    }
};

#endif // _GAMECAMERA_
