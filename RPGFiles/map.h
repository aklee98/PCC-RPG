#ifndef SFMLAPP_MAP_H
#define SFMLAPP_MAP_H
#include "sprite_Class/sprites.cpp"
class MapCell{
    private:
        //Contains an Area object such to create a grid that surrounds it.
        Area mapGrid;
        //Object for the map and texture.
        Sprites map;
        //Row and Column for use with interaction with the player.
        int row;
        int column;
        /*areaHeight and areaWidth are contained here to be use when setting positions of both grid and maps
            in conjunction with each other.
        */
        int areaHeight;
        int areaWidth;
    public:
        //Default constructor.
        MapCell();
        //Constructor for specificity.
        MapCell(float scale, int row, int column,std::string imageFile,
                sf::Color color, float outlineThickness, sf::Vector2u windowSize);
        //Draws the mapGrid and the map out.
        void draw(sf::RenderWindow &window) const;
        /*setColor should be called to set the color of each map based on the location of the player.
        */
        void setColor(int y, int x);
        //Loads the image for the texture and sets it to the sprite.
        void setTextureAndColor(std::string imageFile);
        //Mutators and Accessors for a lot of the various elements.
        sf::Sprite getMap() const;
        sf::Texture getTexture() const;
        void setRow(int row);
        void setColumn(int column);
        //setPosition has 4 elements to it to set both the position of the Area object and the Sprite.
        //This is due to the object and sprite having different sizes as of right now.
        void setPosition(int mapX, int mapY, int gridX, int gridY);
        void setScale(float scale);
        void setOutlineColor(sf::Color color);
        void setOutlineThickness(float thickness);
        float getScale() const;

        //Consider removing these in the final.
        Area& getMapGrid();
        int getRow();
        int getColumn();
        void setAreaHeight(unsigned int size);
        void setAreaWidth(unsigned int size);
        int getAreaHeight();
        int getAreaWidth();
        void setFillColor(sf::Color color);
};
#endif //SFMLAPP_MAP_H
