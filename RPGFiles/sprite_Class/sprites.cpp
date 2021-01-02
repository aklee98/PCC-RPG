#include "sprites.h"
Sprites::Sprites(){
    //Default Constructor.
}
//Draws the sprite.
void Sprites::draw(sf::RenderWindow &window) const {
    window.draw(sprite);
}
void Sprites::setTexture(std::string imageFile) {
    if(!texture.loadFromFile(imageFile)){
        std::cout<<"The image "<<imageFile<<" does not exist."<<std::endl;
    }
    sprite.setTexture(texture);
}
//Scales the sprite appropriately based on what is passed in.
void Sprites::setScale(float scale) {
    scaleMeasurement = scale;
    sprite.setScale(scaleMeasurement,scaleMeasurement);
}
void Sprites::setPosition(int x, int y) {
    sprite.setPosition(x,y);
}
void Sprites::setColor(sf::Color color){
    sprite.setColor(color);
}
sf::Sprite Sprites::getSprite() const {
    return sprite;
}
sf::Texture Sprites::getImage() const{
    return texture;
}
float Sprites::getScale() const {
    return scaleMeasurement;
}
void Sprites::move(int x, int y) {
    sprite.move(x,y);
}