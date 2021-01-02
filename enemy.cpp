#include "enemy.h"
Enemy::Enemy(){
    //Default Constructor.
}
Enemy::Enemy(int health, int strength, int defense, int exp, int rupies):
    Character(health, strength, defense){
   //Implementation above.
   this->exp = exp;
   this->rupies = rupies;
}
/*
Enemy::Enemy(int health, int strength, int defense, int exp, int rupies,
        Area area, std::string playerImage):
                     Character(health, strength, defense, area, playerImage) {
    //Constructor with implementation for the Character's.
    this->exp=exp;
    this->rupies = rupies;
}
*/
//checkRespawn checks if the enemy is allowed to respawn based on their variable, and if so,
//then it sets their dead state to false.
void Enemy::checkRespawn() {
    if(isRespawn()) {
        setDead(false);
    }
}
//If the enemy is on screen, is not dead, and is in the same location as the player, then draw them
//to their spawn location and position. Otherwise put them offscreen and to a place where they
//cannot interact with the player.
void Enemy::ifOnscreen(sf::RenderWindow &window, Character player) {
    if(!isDead() &&
    player.getXLocation()==getXLocation() && player.getYLocation() == getYLocation()) {
        setOnScreen(true);
        setPosition(spawnXPosition, spawnYPosition);
        draw(window);
    }
    else{
        setOnScreen(false);
        setPosition(-500,-500);
    }
}
//Getters and setters.
void Enemy::setRespawn(bool respawn) {
    this->respawn = respawn;
}
/*These functions never see use currently.
void Enemy::setEXP(int exp){
    this->exp = exp;
}
void Enemy::setRupies(int rupies){
    this->rupies = rupies;
}
*/
int Enemy::getEXP()const{
    return exp;
}
int Enemy::getMoney() const{
    return rupies;
}
bool Enemy::isRespawn() const {
    return respawn;
}