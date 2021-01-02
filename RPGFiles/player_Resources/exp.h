#ifndef SFMLAPP_EXP_H
#define SFMLAPP_EXP_H
#include "healthPotion.cpp"
class EXP {
    private:
        //exp being of class Stat is helpful to have a max value. The current value resets to make
        //calculation of when the player levels up easier while the max value continues to grow to
        //be a big number to make the player feel good.
        //In essence though, the only thing that will affect a level up is how much exp's current value
        //is when the calculateEXP is called.
        Stat exp;
        //expRequired is set to be how much is needed for a level up.
        int expRequired = 100;
    public:
        EXP();
        EXP(int exp);
        int getEXP() const;
        //Currently the below function does not see use.
        //void setEXP(int exp);
        //calculates if the player has enough EXP for a level up, otherwise, simply sets values around.
        void calculateEXP(int EXP,Character &player);
        //Increases the player's stats by a certain amount pre-set in the funciton.
        void levelUp(Character &player);
};


#endif //SFMLAPP_EXP_H
