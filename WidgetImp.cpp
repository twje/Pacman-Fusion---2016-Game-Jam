/*
#include "Util.hpp"
#include "WidgetImp.hpp"
#include "Widget.hpp"


//****************
// CurvedWidgetImp
//****************
CurvedWidgetImp::CurvedWidgetImp(std::string l_textureId, int l_tileSize):
m_manager(ResourceManager::getInstance()),
m_tiles(9, sf::Sprite()),
m_textureId(l_textureId),
m_tileSize(l_tileSize)
{
    if (!m_manager->requireResource(ResourceType::TEXTURE, l_textureId)) {
        throw std::runtime_error("runtime_error - texture resource not available: " + l_textureId);
    }

    sf::Texture* tex = m_manager->getResource<sf::Texture>(ResourceType::TEXTURE, l_textureId);
    if (tex->getSize().x % l_tileSize != 0 || tex->getSize().x / l_tileSize != 3) {
        throw std::logic_error("logic_error - panel texture width isn't a multple of 3");
    }
    if (tex->getSize().y % l_tileSize != 0 || tex->getSize().y / l_tileSize != 3) {
        throw std::logic_error("logic_error - panel texture height isn't a multple of 3");
    }

    m_middleTex.reset(getMiddleTile(tex, l_tileSize));

    // 0. top left      1. top          2. top right
    // 3. left          4. middle       5. right
    // 6. bottom left   7. bottom       8. bottom right
    for(int i = 0; i < 9; i++) {
        if (i == 4) {
            m_tiles[i].setTexture(*m_middleTex.get());
            continue;
        }

        sf::IntRect region = getTileRegion(tex, i, l_tileSize, l_tileSize);
        m_tiles[i].setTexture(*tex);
        m_tiles[i].setTextureRect(region);
    }
}

sf::Drawable& CurvedWidgetImp::getTopLeftCorner()
{
    sf::Sprite& corner = m_tiles[0];
    corner.setPosition(getLeft(), getTop());

    return corner;
}

sf::Drawable& CurvedWidgetImp::getTopRightCorner()
{
    sf::Sprite& corner = m_tiles[2];
    corner.setPosition(getRight() - m_tileSize, getTop());

    return corner;
}

sf::Drawable& CurvedWidgetImp::getBottomRightCorner()
{
    sf::Sprite& corner = m_tiles[8];
    corner.setPosition(getRight() - m_tileSize, getBottom() - m_tileSize);

    return corner;
}

sf::Drawable& CurvedWidgetImp::getBottomLeftCorner()
{
    sf::Sprite& corner = m_tiles[6];
    corner.setPosition(getLeft(), getBottom() - m_tileSize);

    return corner;
}

sf::Drawable& CurvedWidgetImp::getLeftEdge()
{
    sf::Sprite& edge = m_tiles[3];
    edge.setPosition(getLeft(), getTop() + m_tileSize);
    edge.setScale(1, getHeightScale());

    return edge;
}

sf::Drawable& CurvedWidgetImp::getTopEdge()
{
    sf::Sprite& edge = m_tiles[1];
    edge.setPosition(getLeft() + m_tileSize, getTop());
    edge.setScale(getWidthScale(), 1);

    return edge;
}

sf::Drawable& CurvedWidgetImp::getRightEdge()
{
    sf::Sprite& edge = m_tiles[5];
    edge.setPosition(getRight() - m_tileSize, getTop() + m_tileSize);
    edge.setScale(1, getHeightScale());

    return edge;
}

sf::Drawable& CurvedWidgetImp::getBottomEdge()
{
    sf::Sprite& edge = m_tiles[7];
    edge.setPosition(getLeft() + m_tileSize, getBottom() - m_tileSize);
    edge.setScale(getWidthScale(), 1);

    return edge;
}

sf::Drawable& CurvedWidgetImp::getBody()
{
    sf::Sprite& body = m_tiles[4];
    body.setPosition(getLeft() + m_tileSize, getLeft() + m_tileSize);
    body.setScale(getWidthScale(), getHeightScale());

    return body;
}

sf::IntRect CurvedWidgetImp::getBounds()
{
    int x = getLeft() + m_tileSize;
    int y = getTop() + m_tileSize;
    int w = getRight() - getLeft() - 2 * m_tileSize;
    int h = getBottom() - getTop() - 2 * m_tileSize;

    return sf::IntRect(x, y, w, h);
}

sf::Texture* CurvedWidgetImp::getMiddleTile(sf::Texture* sourceTex, int tileSize)
{
    sf::Image sourceImg = sourceTex->copyToImage();
    sf::Image targetImg;
    targetImg.create(tileSize, tileSize);

    for(int x = 0; x < tileSize; x++)
    {
        for(int y = 0; y < tileSize; y++)
        {
            int pixelX = tileSize + x;
            int pixelY = tileSize + y;
            targetImg.setPixel(x, y, sourceImg.getPixel(pixelX, pixelY));
        }
    }

    sf::Texture* targetTex = new sf::Texture();
    targetTex->loadFromImage(targetImg);
    targetTex->setSmooth(true);

    return targetTex;
}

int CurvedWidgetImp::getLeft(){ return getWidget()->getPosition().x; }
int CurvedWidgetImp::getTop(){ return getWidget()->getPosition().y; }
int CurvedWidgetImp::getRight(){ return getWidget()->getPosition().x + getWidget()->getSize().x; }
int CurvedWidgetImp::getBottom(){ return getWidget()->getPosition().y + getWidget()->getSize().y; }

float CurvedWidgetImp::getHeightScale(){ return ((float)(std::abs(getBottom() - getTop()) - (2 * m_tileSize)) / (float) m_tileSize); }
float CurvedWidgetImp::getWidthScale(){ return ((float)(std::abs(getRight() - getLeft()) - (2 * m_tileSize)) / (float) m_tileSize); }
*/
