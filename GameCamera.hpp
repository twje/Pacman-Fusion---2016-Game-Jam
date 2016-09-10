#ifndef _GAMECAMERA_

#include <iostream>
#include "SharedContext.h"
#include "Tween.hpp"

//****************
// ViewPortStateID
//****************
enum class ViewPortStateID
{
    ACTIVE_RED,
    ACTIVE_GREEN,
    ACTIVE_BLUE,
    ACTIVE_START
};

//***********
// ViewPortID
//***********
enum class ViewPortID
{
    RED,
    GREEN,
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
    std::map<ViewPortID, sf::RectangleShape> m_borders;
    ViewPortStateID m_currentState;
    int m_currentSlider1;
    int m_currentSlider2;
    float m_duration;
    Tween m_slider1;
    Tween m_slider2;
    sf::View m_hud;
    float m_hudSpace;
    float m_dullColor;
    float m_expandDuration;

public:
    GameCamera(SharedContext* l_context, float l_hudSpace, float l_scaleRatio, float l_duration):
    m_context(l_context),
    m_duration(l_duration),
    m_dullColor(0.7f),
    m_expandDuration(0.01f),
    m_hudSpace(l_hudSpace)
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

        // Init borders
        sf::RectangleShape border;
        border.setOutlineThickness(-5);
        border.setFillColor(sf::Color::Transparent);

        m_borders[ViewPortID::RED] = border;
        m_borders[ViewPortID::GREEN] = border;
        m_borders[ViewPortID::BLUE] = border;

        // Init sliders
        m_slider1.reset(portWidth, portWidth, m_expandDuration);
        m_slider2.reset(2*portWidth, 2*portWidth, m_expandDuration);
        updateViewPorts();
    }

    bool isExpanding() { return !m_slider1.isFinished() || !m_slider2.isFinished(); }

    void update(float dt)
    {
        //std::cout << dt << std::endl;

        float constant = 3.0f;
        if (isExpanding())
        {
            m_slider1.update(dt * constant);
            m_slider2.update(dt * constant);
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
        return m_views[(ViewPortID)id];
    }

    void drawBorders(sf::RenderWindow& window)
    {
        sf::View temp = window.getView();
        window.setView(window.getDefaultView());

        window.draw(m_borders[ViewPortID::RED]);
        window.draw(m_borders[ViewPortID::BLUE]);
        window.draw(m_borders[ViewPortID::GREEN]);

        window.setView(temp);
    }

private:
    sf::Color dullCOlor(sf::Color source, float value)
    {
        source.r = source.r * value;
        source.g = source.g * value;
        source.b = source.b * value;

        return source;
    }

    void updateViewPorts()
    {
        updateViewPort0();
        updateViewPort1();
        updateViewPort2();
    }

    void updateViewPort0() // RED
    {
        sf::View& view = m_views[ViewPortID::RED];
        sf::RectangleShape& border = m_borders[ViewPortID::RED];

        float winWidth = m_context->m_wind->GetWindowSize().x;
        float winHeight = m_context->m_wind->GetWindowSize().y;

        float portWidth = m_slider1.value();
        float portHeight = winHeight - m_hudSpace;

        float l = 0;
        float t = 0;
        float w = portWidth/winWidth;
        float h = portHeight/winHeight;
        sf::FloatRect port(l, t, w, h);

        view.setViewport(port);
        view.setSize(w * winWidth, h * winHeight);
        view.setCenter(0, 0);

        border.setSize(view.getSize());
        border.setPosition(l * winWidth, t * winHeight);

        sf::Color borderColor = sf::Color::Red;
        if (m_currentState != ViewPortStateID::ACTIVE_RED || m_currentState == ViewPortStateID::ACTIVE_START)
        {
            borderColor = dullCOlor(borderColor, m_dullColor);
        }
        border.setOutlineColor(borderColor);
    }

    void updateViewPort1() // GREEN (FIX)
    {
        sf::View& view = m_views[ViewPortID::GREEN];
        sf::RectangleShape& border = m_borders[ViewPortID::GREEN];

        float winWidth = m_context->m_wind->GetWindowSize().x;
        float winHeight = m_context->m_wind->GetWindowSize().y;

        float portWidth = m_slider2.value() - m_slider1.value();
        float portHeight = winHeight - m_hudSpace;

        float l = m_slider1.value() / winWidth;
        float t = 0;
        float w = portWidth/winWidth;
        float h = portHeight/winHeight;
        sf::FloatRect port(l, t, w, h);

        view.setViewport(port);
        view.setSize(w * winWidth, h * winHeight);
        view.setCenter(0, 0);

        border.setSize(view.getSize());
        border.setPosition(l * winWidth, t * winHeight);

        sf::Color borderColor = sf::Color::Green;
        if (m_currentState != ViewPortStateID::ACTIVE_GREEN || m_currentState == ViewPortStateID::ACTIVE_START)
        {
            borderColor = dullCOlor(borderColor, m_dullColor);
        }
        border.setOutlineColor(borderColor);
    }

    void updateViewPort2() // BLUE
    {
        sf::View& view = m_views[ViewPortID::BLUE];
        sf::RectangleShape& border = m_borders[ViewPortID::BLUE];

        float winWidth = m_context->m_wind->GetWindowSize().x;
        float winHeight = m_context->m_wind->GetWindowSize().y;

        float portWidth = winWidth - m_slider2.value();
        float portHeight = winHeight  - m_hudSpace;

        float l = m_slider2.value() / winWidth;
        float t = 0;
        float w = portWidth/winWidth;
        float h = portHeight/winHeight;
        sf::FloatRect port(l, t, w, h);

        view.setViewport(port);
        view.setSize(w * winWidth, h * winHeight);
        view.setCenter(0, 0);

        border.setSize(view.getSize());
        border.setPosition(l * winWidth, t * winHeight);

        sf::Color borderColor = sf::Color::Blue;
        if (m_currentState != ViewPortStateID::ACTIVE_BLUE || m_currentState == ViewPortStateID::ACTIVE_START)
        {
            borderColor = dullCOlor(borderColor, m_dullColor);
        }
        border.setOutlineColor(borderColor);
    }
};

#endif // _GAMECAMERA_
