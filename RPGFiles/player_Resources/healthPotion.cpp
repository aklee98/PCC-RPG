#include "healthPotion.h"
HealthPotion::HealthPotion(){
    //Default Constructor.
}
HealthPotion::HealthPotion(int numberOfPotions) {
    healthPotions=numberOfPotions;
}
int HealthPotion::getNumberOfHealthPotions() const{
    return healthPotions;
}
void HealthPotion::setNumberOfPotions(int numberOfPotions) {
    healthPotions=numberOfPotions;
}
//usePotion will pretty much heal the character assigned, which in current usage is the player in
//the scope of the program.
void HealthPotion::usePotion(Character &character){
    character.setCurrentHealth(character.getCurrentHealth()+heal);
    //Makes sure not to overheal the player, so the currentHealth will never be greater than the max.
    if(character.getCurrentHealth()>character.getMaxHealth()){
        character.setCurrentHealth(character.getMaxHealth());
    }
    //Reduces potion count by 1.
    setNumberOfPotions(getNumberOfHealthPotions()-1);
}
//checkPotion will check if the player has more than 0 potions, if so, then it is okay to use.
void HealthPotion::checkPotion(Character &character){
    if(getNumberOfHealthPotions()>0){
        usePotion(character);
    }
}