#ifndef SFMLAPP_HEALTHPOTION_H
#define SFMLAPP_HEALTHPOTION_H
#include "../textPieces.cpp"
class HealthPotion {
    private:
        //number of healthPotions.
        int healthPotions;
        //Determines how much when a health potion is used, health will return to its max value by.
        int heal = 100;
    public:
        HealthPotion();
        //Constructor that initializes the number of healthPotions are available. Should always be
        //called in some way or manner.
        HealthPotion(int numberOfPotions);
        //Below 2 functions are mutators and accessors.
        int getNumberOfHealthPotions() const;
        void setNumberOfPotions(int numberOfPotions);

        //usePotion is called which heals the player, and checkPotion is to check if there is
        //more than 1 potion available.
        void usePotion(Character &character);
        void checkPotion(Character &character);
};


#endif //SFMLAPP_HEALTHPOTION_H
