#ifndef SFMLAPP_CHARACTER_H
#define SFMLAPP_CHARACTER_H
#include "stats_Character/stat.cpp"

class Character {
    protected:
        //Sprites are used here for the character sprite.
        Sprites character;
        //Determines how much health a character has.
        Stat health;
        //Determines how much damage a character will do.
        Stat strength;
        //Determines how much damage a character will take.
        Stat defense;
        //Determines if the character should be on screen.
        bool onScreen = true;
        //Determines if a character is dead or not.
        bool dead = false;
        //xLocation and yLocation are used to keep track of
        // where the character is in relation to the map.
        int xLocation;
        int yLocation;
        //spawnXPosition and spawnYPosition are used to set the character to the place on the
        //game when they should be drawn in.
        int spawnXPosition;
        int spawnYPosition;
    public:
        //Constructors.
        Character();
        Character(int health, int strength, int defense);
        Character(Area area, std::string playerImage);
        Character(int health, int strength, int defense, Area area, std::string playerImage);
        //Sets the image to the sprite and scales the sprite appropriately.
        void setImage(std::string image, Area area);
        //Draws the sprite.
        void draw(sf::RenderWindow &window) const;
        //Checks if the character is on screen with relation to the player's location, and if so,
        //draws the character.
        virtual void ifOnscreen(sf::RenderWindow &window, Character player);
        //Calculates damage done to another character.
        int calculateDamage(int enemyDefense);
        //Does the full fight calculations during battle.
        void dealDamage(Character &enemy, int selfDamage, int enemyDamage);
        //Accessors and Mutators for all of the variables.
        int getCurrentHealth() const;
        int getMaxHealth();
        void setMaxHealth(int health);
        void setCurrentHealth(int health);
        int getStrength() const;
        void setStrength(int strength);
        int getDefense() const;
        void setDefense(int defense);
        //Returns the sprite.
        sf::Sprite getSprite() const;
        //Returns the image.
        sf::Texture getImage() const;
        //Sets whether the character should be onScreen or not.
        void setOnScreen(bool status);
        //Sets the scale of the sprite.
        float getScale() const;
        //Sets the position of the sprite.
        void setPosition(int x, int y);
        //Getters and Setters for the map location of the character.
        int getXLocation() const;
        int getYLocation() const;
        void setXandYLocation(int x, int y);
        void setScale(float scaleMeasurement);
        void setXandYSpawnPosition(int x, int y);
        int getSpawnXPosition() const;
        int getSpawnYPosition() const;
        void setDead(bool dead);
        bool isDead() const;
        void isDefeated();
};

#endif //SFMLAPP_CHARACTER_H
