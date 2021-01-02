#ifndef SFMLAPP_PLAYER_H
#define SFMLAPP_PLAYER_H
#include "player_Resources/exp.cpp"
class Player: public Character{
    private:
        //inCombat and inShop are primarily used to check if the player can move or not.
        bool inCombat = false;
        bool inShop = false;
        //healthPotion is of the HealthPotion object. The player has three functions related to it
        //only to check how many healthPotions it has and another to then use any it has to heal.
        HealthPotion healthPotion;
        //movement is a number to check how many pixels the player will move. Set based off of
        //how large the area is passed into Player's move function.
        float movement;
        //exp is a EXP object which is primarily used to level up the player's inherited Character
        //Stat values when the player receives enough points to its exp value.
        EXP exp;
        //rupies is of Stat class to which this object will simply have a value to increase or lower.
        //This most likely could have been just an int variable too instead of making it an object.
        Stat rupies;
    public:
        //Default Constructor
        Player();
        //Overloaded constructor with more information to pass to the constructor in character.
        Player(int health, int strength, int defense, int healthPotions,
                Area area, std::string playerImage);
        //Overloaded function to draws the sprite.
        void draw(sf::RenderWindow &window, sf::Text enemyHealth) const;
        //Moves the sprite according to player key press along with restrictions to the area it is bound to.
        void move(Area area, MapCell *mapGrid[3],
                Enemy enemy[], int numberOfEnemies, Character &merchant);
        //Checks to see if the player collides with any of the enemies or the merchant in the game.
        void checkCollision(Enemy enemy[], int numberOfEnemies, Character &merchant);
        //The below functions are called in conjunction when the above is called.
        void checkSameArea(Enemy &enemy);
        void checkSameArea(Character &merchant);
        //Begins a fight between the selected character and another character.
        void fight(Enemy &enemy, TextPieces &text);
        //Moves the player sprite away from the character that is passed into it.
        //Should see usage in when the player moves into an enemy or the merchant right now.
        void moveAway(Character character);

        //Miscellaneous getters and setters for the boolean member variables this object has.
        void setCombatStatus(bool status);
        void setShopStatus(bool status);
        bool inFight() const;
        bool isBuying() const;

        //Usage with the exp object.
        int getEXP() const;
        //The below function never sees use.
        //void setEXP(int EXP);
        //calls the rest of the appropriate functions in player's EXP object class.
        void calculateEXP(int EXP,Character &player);

        //Usage with the rupies object.
        int getRupies() const;
        //Adds and subtracts based on which variable is called. Could have also been done with just
        //Setting values to - or + if a mutator function was made, but this is as it is now.
        void addRupieAmount(int rupies);
        void subtractRupieAmount(int rupies);

        //Usage with the healthPotion object.
        int getHealthPotion() const;
        void setNumberOfHealthPotions(int number);
        //Checks to see if the player has enough. Rest of the implementation in the HealthPotion class.
        void checkPotion();
};
#endif //SFMLAPP_PLAYER_H