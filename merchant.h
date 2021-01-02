#ifndef SFMLAPP_MERCHANT_H
#define SFMLAPP_MERCHANT_H
#include "player.cpp"
//Inherits Character.
class Merchant: public Character{
    private:
    public:
        //Default Constructor.
        Merchant();
        //Takes in the area the merchant should be in and the file for its image.
        //Really just calls Character's constructor.
        Merchant(Area area, std::string playerImage);
        //showMenu has the player see what options it can do to use with the rupies it has to buy.
        void showMenu(Player &player, TextPieces &text);
};


#endif //SFMLAPP_MERCHANT_H