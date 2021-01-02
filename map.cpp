#include "map.h"
MapCell::MapCell(){
    //Default Constructor.
}
/*Constructor with specific parameters for this project. If position of this map matters,
 * then any changes should happen here.
 *
 * Currently, this Constructor will set the row, column, image used, the color for the outline,
 * the thickness of the outline, and the location appropriate to the window.
*/
MapCell::MapCell(float scale, int row, int column,std::string imageFile,
        sf::Color color, float outlineThickness, sf::Vector2u windowSize){
    //Sets the row and column appropriately for use in relation to the player.
    setRow(row);
    setColumn(column);
    /*Sets the texture via string.
     * For some reason, setTexture both needs to be called outside of the constructor as well for the
     * image to load.
    */
    setTextureAndColor(imageFile);
    //Sets the scale of the image.
    setScale(scale);
    //Sets the variables below to an appropriate size and then sets the grid sizes to their values.
    int textureXSize = map.getImage().getSize().x*scale;
    int textureYSize = map.getImage().getSize().y*scale;
    mapGrid.setAreaWidth(textureXSize+1);
    mapGrid.setAreaHeight(textureYSize+1);
    //Sets the outline color and thickness of the grid.
    setOutlineColor(color);
    setOutlineThickness(outlineThickness);
    //Position is set based on the window size and custom placed based on row and column.
    //For best use of this, make sure that whatever images are passed in, they are all of the same
    //size.
    setPosition((windowSize.x/1.7 +column*textureXSize),
                windowSize.y/10 +row*textureYSize,
                windowSize.x/1.7 +column*textureXSize,
                windowSize.y/10 +row*textureYSize);
}
//draw draws the grid and map.
void MapCell::draw(sf::RenderWindow &window) const {
    mapGrid.draw(window);
    map.draw(window);
}
/*setColor will check the player's X location and Y location to see if it matches up with this,
 * and if so, then it will set the map color to that to show where the player is.
 * If the boss room(which is the middle of the game) is the current map,
 * then it will set that to be Red. If it is any other map then set the color to White.
 *
 * If the player enters the boss map, then the player's location will be blue instead of red,
 * just due to how this this is programmed.
*/
void MapCell::setColor(int y, int x){
    if(y == row && x == column){
        map.setColor((sf::Color::Blue));
    }
    else{
        if(this->row==1 && this->column==1){
            map.setColor((sf::Color::Red));
        }
        else {
            map.setColor((sf::Color::White));
        }
    }
}
/*setTexture will load the texture that contains the object in.
 * It will then set the texture to the sprite, and if the boss room
 * which is the final part of the game is the cell selected, then it will set the color to red.
 * Very specific function for this type of class.
*/
void MapCell::setTextureAndColor(std::string imageFile) {
    map.setTexture(imageFile);
    if(this->row==1 && this->column==1){
        map.setColor(sf::Color::Red);
    }
    else if(this->row==0 && this->column==0){
        map.setColor(sf::Color::Blue);
    }
}
//Getters and Setters below.
sf::Sprite MapCell::getMap() const{
    return map.getSprite();
}
void MapCell::setRow(int row) {
    this->row = row;
}
void MapCell::setColumn(int column) {
    this->column = column;
}
void MapCell::setPosition(int mapX, int mapY, int gridX, int gridY) {
    map.setPosition(mapX,mapY);
    mapGrid.setPosition(gridX,gridY);
}
void MapCell::setScale(float scale) {
    map.setScale(scale);
}
sf::Texture MapCell::getTexture() const{
    return map.getImage();
}
void MapCell::setOutlineColor(sf::Color color){
    mapGrid.setOutlineColor(color);
}
void MapCell::setOutlineThickness(float thickness) {
    mapGrid.setOutlineThickness(thickness);
}
float MapCell::getScale() const{
    return map.getScale();
}
//Functions do not see any use.
/*
Area& MapCell::getMapGrid(){
    return mapGrid;
}
void MapCell::setFillColor(sf::Color color){
    mapGrid.setFillColor(color);
}
void MapCell::setAreaHeight(unsigned int size){
    areaHeight = size;
    mapGrid.setAreaHeight(areaHeight);
}
void MapCell::setAreaWidth(unsigned int size){
    areaWidth = size;
    mapGrid.setAreaWidth(areaWidth);
}
int MapCell::getAreaHeight(){
    return areaHeight;
}
int MapCell::getAreaWidth() {
    return areaWidth;
}

int MapCell::getRow(){
    return row;
}
int MapCell::getColumn() {
    return column;
}
*/