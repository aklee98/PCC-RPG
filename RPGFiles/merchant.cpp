#include "merchant.h"
Merchant::Merchant(){
    //Default Constructor.
}
//Because Merchant doesn't ever fight, its Stat variables(under Character) do not need to be set.
Merchant::Merchant(Area area, std::string playerImage):
    Character(area, playerImage){
    //Constructor with Implementation above.
}
/*showMenu will first set the instructions to tell the player what to do. It also creates
 * two variables for the rupieRequirement and statIncreases which are set if the player presses
 * any of the available options, checking if the player has enough rupies to buy the option
 * and then increasing that selection of whatever by the increase.
 */
void Merchant::showMenu(Player &player, TextPieces &text) {
    text.setInstructionsString(1,text.getDefaultText(3));
    int rupieRequirement;
    int statIncrease;
    //Press 1 to subtract 50 from player's rupie count and add 1 to their health potions if enough.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        rupieRequirement=50;
        statIncrease=1;
        if(player.getRupies()>=rupieRequirement){
            player.subtractRupieAmount(rupieRequirement);
            player.setNumberOfHealthPotions(player.getHealthPotion()+statIncrease);
            text.loadPlayerText(player,player.getHealthPotion(),player.getEXP(), player.getRupies());
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

        }
    }
    //Press 2 to subtract 40 from player's rupie count and add 20 to their health stat if enough.
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        rupieRequirement=40;
        statIncrease = 20;
        if(player.getRupies()>=rupieRequirement){
            player.subtractRupieAmount(rupieRequirement);
            player.setCurrentHealth(player.getCurrentHealth()+statIncrease);
            player.setMaxHealth(player.getMaxHealth()+statIncrease);
            text.loadPlayerText(player,player.getHealthPotion(),player.getEXP(), player.getRupies());
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    //Press 3 to subtract 40 from player's rupie count and add 10 to the strength and defense
    // stat if enough.
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        rupieRequirement=40;
        statIncrease=10;
        if(player.getRupies()>=rupieRequirement){
            player.subtractRupieAmount(rupieRequirement);
            player.setStrength(player.getStrength()+statIncrease);
            player.setDefense(player.getStrength()+statIncrease);
            text.loadPlayerText(player,player.getHealthPotion(),player.getEXP(), player.getRupies());
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    //Player moves away and sets the player's shopping status to off, so it can move normally.
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        player.setShopStatus(false);
        player.moveAway(*this);
        text.loadNormalText(player,player.getHealthPotion(),player.getEXP(), player.getRupies());
    }
}
