#ifndef SFMLAPP_ENEMY_H
#define SFMLAPP_ENEMY_H
#include "character.cpp"
class Enemy: public Character {
    private:
        //Determines if the character can respawn. Should only be set off for some enemies.
        bool respawn = true;
        //rupies and exp are determined upon Constructors.
        int rupies;
        int exp;
    public:
        Enemy();
        //Sets all the values for the enemy, primarily through calling of the Character constructor.
        Enemy(int health, int strength, int defense, int exp, int rupies);
        /*This constructor is not used.
        Enemy(int health, int strength, int defense, int exp, int rupies,
                Area area, std::string playerImage);
        */
        void checkRespawn();
        virtual void ifOnscreen(sf::RenderWindow &window, Character player);
        //Mutators and Accessors
        void setRespawn(bool respawn);
        /*These functions never see use currently.
        void setEXP(int exp);
        void setRupies(int rupies);
        */
        int getEXP() const;
        int getMoney() const;
        bool isRespawn() const;
};


#endif //SFMLAPP_ENEMY_H
