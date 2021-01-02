#include <thread>
#include "character.h"
#include "player.h"

Character::Character(){
    //Default constructor.
}
//Constructor that is mainly used by the enemy object.
Character::Character(int health, int strength, int defense) {
    this->health = Stat(health);
    this->strength = Stat(strength);
    this->defense = Stat(defense);
}
//Constructor that is mainly used by the merchant object. xLocation and yLocation are preset
//due to the merchant being in that area.
Character::Character(Area area, std::string playerImage){
    setImage(playerImage, area);
    character.setPosition(area.getXPosition(),area.getYPosition());
    xLocation=0;
    yLocation=0;
}
//Constructor that is called when the player's constructor is called, setting all of the appropriate
//variables and so forth.
Character::Character(int health, int strength, int defense, Area area, std::string playerImage) {
    this->health = Stat(health);
    this->strength = Stat(strength);
    this->defense = Stat(defense);
    setImage(playerImage, area);
    character.setPosition(area.getXPosition(),area.getYPosition());
    xLocation=0;
    yLocation=0;
}
//Sets the texture and sets the texture to the sprite. Also is sure to scale the sprite and images,
//appropriately by the playableArea of the game.
void Character::setImage(std::string image,Area area) {
    character.setTexture(image);
    //the height should be the same as width, so it doesn't matter.
    float scaleByArea = area.getAreaHeight();
    float averageSize = (getImage().getSize().x+getImage().getSize().y)/2;
    character.setScale((averageSize/scaleByArea)*2);
}
//draw will draw the character if it is onscreen.
void Character::draw(sf::RenderWindow &window) const{
    if(onScreen)
        character.draw(window);
}
//ifOnscreen checks if the character is in the same location as the player, and then draws them.
//If not, sets the onScreen stats to false and sets them somewhere off-screen.
void Character::ifOnscreen(sf::RenderWindow &window, Character player) {
    if(player.getXLocation()==getXLocation() && player.getYLocation() == getYLocation()) {
        setOnScreen(true);
        setPosition(spawnXPosition, spawnYPosition);
        draw(window);
    }
    else{
        setOnScreen(false);
        setPosition(-500,-500);
    }
}
/*calculateDamage takes in a value of enemyDefense and will calculate damage
 * based off of the character's own strength minus the enemyDefense and
 * then returns the damage. If the damage is <0, then it will instead set damage = 1;
*/
int Character::calculateDamage(int enemyDefense){
    int damage = getStrength()-enemyDefense;
    if(damage<0){
        damage = 1;
    }
    return damage;
}
/*dealDamage will set the health values for the character selected and the enemy.
 */
void Character::dealDamage(Character &enemy, int charDamage, int enemyDamage){
    int enemyFinalHealth = enemy.getCurrentHealth()-charDamage;
    int playerFinalHealth = getCurrentHealth()-enemyDamage;
    if(enemyFinalHealth<0){
        enemyFinalHealth=0;
    }
    if(playerFinalHealth<0){
        playerFinalHealth=0;
    }
    enemy.setCurrentHealth(enemyFinalHealth);
    setCurrentHealth(playerFinalHealth);
}
//Accessors and Mutators below.
sf::Sprite Character::getSprite() const{
    return character.getSprite();
}
sf::Texture Character::getImage() const{
    return character.getImage();
}
float Character::getScale() const{
    return character.getScale();
}
void Character::setPosition(int x, int y) {
    character.setPosition(x,y);
}
int Character::getCurrentHealth() const{
    return health.getCurrentStat();
}
int Character::getMaxHealth() {
    return health.getMaxStat();
}
void Character::setMaxHealth(int health){
    this->health.setMaxStat(health);
}
void Character::setCurrentHealth(int health) {
    this->health.setCurrentStat(health);
}
int Character::getStrength() const{
    return strength.getCurrentStat();
}
void Character::setStrength(int strength){
    this->strength.setCurrentStat(strength);
}
int Character::getDefense() const{
    return defense.getCurrentStat();
}
void Character::setDefense(int defense){
    this->defense.setCurrentStat(defense);
}
void Character::setOnScreen(bool status) {
    onScreen = status;
}
//Getters and setters. Consider removing if never used.
int Character::getXLocation() const{
    return xLocation;
}
int Character::getYLocation() const{
    return yLocation;
}
void Character::setXandYLocation(int x, int y) {
    xLocation = x;
    yLocation = y;
}
void Character::setScale(float scaleMeasurement){
    character.setScale(scaleMeasurement);
}

//Getters and setters.
void Character::setXandYSpawnPosition(int x, int y) {
    spawnXPosition = x;
    spawnYPosition = y;
}
int Character::getSpawnXPosition() const{
    return spawnXPosition;
}
int Character::getSpawnYPosition() const {
    return spawnYPosition;
}
void Character::setDead(bool dead) {
    this->dead = dead;
}
bool Character::isDead() const {
    return dead;
}
void Character::isDefeated(){
    setOnScreen(false);
    setDead(true);
    setPosition(-500,-500);
}