#include "area.h"
//Default constructor. Minimal so that multiple areas can use this.
Area::Area(){
    setOutline(2, sf::Color::White);
}
//Overloaded constructor that sets the size of the rectangle shape and the color of its insides
//based on what is passed on. Also gives it a white outline of 2 pixels.
Area::Area(int width, int height, int x, int y, sf::Color color) {
    setSize(width,height);
    setPosition(x,y);
    setFillColor(color);
    setOutline(2, sf::Color::White);
}
//Draws the area.
void Area::draw(sf::RenderWindow &window) const{
    window.draw(shape);
}
/*Mutators and accessors as follows. The setters also set the shape's values
 * to keep it consistent with the object's member variables.
*/
void Area::setAreaHeight(unsigned int size){
    areaHeight = size;
    shape.setSize(sf::Vector2f(areaWidth,areaHeight));
}
void Area::setAreaWidth(unsigned int size){
    areaWidth = size;
    shape.setSize(sf::Vector2f(areaWidth,areaHeight));
}
int Area::getAreaHeight() const{
    return shape.getSize().y;
}
int Area::getAreaWidth() const{
    return shape.getSize().x;
}
int Area::getXPosition() const{
    return shape.getPosition().x;
}
int Area::getYPosition() const{
    return shape.getPosition().y;
}
void Area::setOutlineColor(sf::Color color){
    shape.setOutlineColor(color);
};
void Area::setFillColor(sf::Color color){
    shape.setFillColor(color);
};
void Area::setOutlineThickness(float thickness) {
    shape.setOutlineThickness(thickness);
}
void Area::setPosition(int x, int y){
    shape.setPosition(x,y);
}
void Area::setSize(int width, int height){
    setAreaHeight(height);
    setAreaWidth(width);
}
void Area::setOutline(float thickness, sf::Color color){
    setOutlineColor(color);
    setOutlineThickness(thickness);
}
//Function is never used.
/*
sf::RectangleShape Area::getShape() {
    return shape;
}
*/