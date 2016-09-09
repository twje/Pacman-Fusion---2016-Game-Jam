#ifndef _UTIL_
#define _UTIL_

#include <SFML/Graphics.hpp>

inline sf::IntRect getTileRegion(sf::Texture* l_tex, int l_frame, int l_sizeX, int l_sizeY) // 0 index
{
    int cols = l_tex->getSize().x/l_sizeX;
    int xIndex = l_frame % cols;
    int yIndex = l_frame / cols;

    int l = xIndex * l_sizeX;
    int r = l + l_sizeX;
    int t = yIndex * l_sizeY;
    int b = t + l_sizeY;

    sf::IntRect region(l, t, r - l, b - t);

    return region;
}



#endif // _UTIL_
