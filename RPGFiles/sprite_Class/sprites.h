#ifndef SFMLAPP_SPRITES_H
#define SFMLAPP_SPRITES_H
#include "../area.cpp"
class Sprites {
    private:
        //Contains the sprite and texture for a map look.
        sf::Sprite sprite;
        sf::Texture texture;
        //scaleMeasurement is used to keep track of how much the sprite is scaled down by.
        float scaleMeasurement;
    public:
        Sprites();
        //Moves the sprite based on what is passed in.
        void move(int x, int y);
        //Draws the sprite out.
        void draw(sf::RenderWindow &window) const;
        //Loads the image for the texture and sets it to the sprite.
        void setTexture(std::string imageFile);
        //Sets the scale for the sprite to use.
        void setScale(float scale);
        void setPosition(int x, int y);
        void setColor(sf::Color color);
        sf::Sprite getSprite() const;
        sf::Texture getImage() const;
        float getScale() const;
};


#endif //SFMLAPP_SPRITES_H
