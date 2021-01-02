#ifndef SFMLAPP_PLAYABLEAREA_H
#define SFMLAPP_PLAYABLEAREA_H
#include "libraryCalls.h"
class Area{
    private:
        //RectangleShape will be primarily used for all of the pieces.
        sf::RectangleShape shape;
        /*areaHeight and areaWidth are all used to keep track of what the shape will be.
        */
        unsigned int areaHeight;
        unsigned int areaWidth;
    public:
        //Default constructor.
        Area();
        //Constructor that takes parameters for the height, width, position, and fill color.
        Area(int width, int height, int x, int y, sf::Color color);
        //Draws the area.
        void draw(sf::RenderWindow &window) const;
        //Mutators and Accessors below.
        void setAreaHeight(unsigned int size);
        void setAreaWidth(unsigned int size);
        void setSize(int width, int height);
        int getAreaHeight() const;
        int getAreaWidth() const;
        void setPosition(int x, int y);
        int getXPosition() const;
        int getYPosition() const;
        void setOutlineColor(sf::Color color);
        void setFillColor(sf::Color color);
        void setOutlineThickness(float thickness);
        void setOutline(float thickness, sf::Color color);
        //Function never sees use.
        /*
        sf::RectangleShape getShape();
        */
};
#endif //SFMLAPP_PLAYABLEAREA_H
