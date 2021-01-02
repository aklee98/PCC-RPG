#include "exp.h"
EXP::EXP(){
    //Default Constructor.
}
EXP::EXP(int exp){
    this->exp = Stat(exp);
}
int EXP::getEXP() const {
    return exp.getMaxStat();
}
/*
void EXP::setEXP(int exp){
    this->exp.setCurrentStat(exp+this->exp.getCurrentStat());
    this->exp.setMaxStat(this->exp.getMaxStat()+exp);
}
*/
/*calculateEXP is called whenever the player defeats an enemy. In this function, the player's max
 * EXP is set while they get more EXP added to their current. The function first checks if the player
 * has reached the threshold required, which is pre-set currently, and if so it will subtract
 * from the current EXP value the player has, looping until the requirement is greater, and then
 * finally setting the player's current value as such.
*/
void EXP::calculateEXP(int exp, Character &player) {
    this->exp.setMaxStat(exp+this->exp.getMaxStat());
    int newEXP = exp+this->exp.getCurrentStat();
    while(newEXP>=expRequired){
        newEXP-=expRequired;
        levelUp(player);
    }
    this->exp.setCurrentStat(newEXP);
}
//levelUp will increase the player's max health, strength, and defense by the appropriate values in the
//function.
void EXP::levelUp(Character &player) {
    int healthIncrease = 20;
    int strengthIncrease = 5;
    int defenseIncrease = 5;
    player.setMaxHealth(player.getMaxHealth()+healthIncrease);
    player.setStrength(player.getStrength()+strengthIncrease);
    player.setDefense(player.getDefense()+defenseIncrease);
}