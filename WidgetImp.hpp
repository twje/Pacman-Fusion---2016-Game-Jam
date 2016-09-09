/*
#ifndef _WIDGETIMP_
#define _WIDGETIMP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "ResourceManager.hpp"

// Forward declaration
class Widget;

//**********
// WidgetImp
//**********
class WidgetImp
{
private:
    Widget* m_widget;

public:
    void setWidget(Widget* l_widget){ m_widget = l_widget; }

    // Corners
    virtual sf::Drawable& getTopLeftCorner() = 0;
    virtual sf::Drawable& getTopRightCorner() = 0;
    virtual sf::Drawable& getBottomRightCorner() = 0;
    virtual sf::Drawable& getBottomLeftCorner() = 0;

    // Edges
    virtual sf::Drawable& getLeftEdge() = 0;
    virtual sf::Drawable& getTopEdge() = 0;
    virtual sf::Drawable& getRightEdge() = 0;
    virtual sf::Drawable& getBottomEdge() = 0;

    // Body
    virtual sf::Drawable& getBody() = 0;

    // Areas
    virtual sf::IntRect getBounds() = 0;

protected:
    Widget* getWidget(){ return m_widget; }
};

//****************
// CurvedWidgetImp
//****************
class CurvedWidgetImp: public WidgetImp
{
private:
    ResourceManager* m_manager;
    std::vector<sf::Sprite> m_tiles;
    std::string m_textureId;
    std::unique_ptr<sf::Texture> m_middleTex;
    int m_tileSize;

public:
    CurvedWidgetImp(std::string l_textureId, int l_tileSize);

    // Corners
    virtual sf::Drawable& getTopLeftCorner();
    virtual sf::Drawable& getTopRightCorner();
    virtual sf::Drawable& getBottomRightCorner();
    virtual sf::Drawable& getBottomLeftCorner();

    // Edges
    virtual sf::Drawable& getLeftEdge();
    virtual sf::Drawable& getTopEdge();
    virtual sf::Drawable& getRightEdge();
    virtual sf::Drawable& getBottomEdge();

    // Body
    virtual sf::Drawable& getBody();

    // Areas
    virtual sf::IntRect getBounds();

private:
    // Smooth rendering
    sf::Texture* getMiddleTile(sf::Texture* sourceTex, int tileSize);

    int getLeft();
    int getTop();
    int getRight();
    int getBottom();

    float getHeightScale();
    float getWidthScale();
};

#endif // _WIDGETIMP_
*/
