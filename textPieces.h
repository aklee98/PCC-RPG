#ifndef SFMLAPP_TEXTPIECES_H
#define SFMLAPP_TEXTPIECES_H
#include "enemy.cpp"
class TextPieces {
    private:
        //There are 2 instruction texts in the game and 6 player texts. These variables are
        //used for those.
        static const int numberOfInstructions = 2;
        static const int numberOfPlayerText = 6;
        //characterSize is used to set how large the text size is.
        int characterSize;
        //instructions is an array of how many texts there are. These are the title for the instructions,
        //and the text to tell what the player should do.
        sf::Text instructions[numberOfInstructions];
        /*playerText is very similar to the above with the instructions. Here, the array follows as suit:
         * 1)Health
         * 2)Health Potions
         * 3)Strength
         * 4)Defense
         * 5)EXP
         * 6)Rupies
        */
        sf::Text playerText[numberOfPlayerText];
        //enemyHealthText is to display how much health which enemy the player is fighting, and
        //only shows up if the player is in combat. This is determined in player's draw.
        sf::Text enemyHealthText;
        //font is here to set the font of all of the text's in the game.
        sf::Font font;
        //Default text for the title. Can call upon this to set it as such. Never gets used though.
        std::string defaultTitle = "Instructions \n";
        //All of the variations of text that instructions can be set as. This is used across the
        //game instead of individually writing the strings again.
        //Could very much possibly instead have an i/o file read these instead, but an array is used now.
        std::string defaultInstructionText[5] = {
                                           "Use w, a, s, d or the\n"
                                           "arrows to move your\n"
                                           "character. Press 2 to heal\n"
                                           "if you have enough potions.\n"
                                           "Your goal is to beat the enemy\n"
                                           "in the middle square. Beat\n"
                                           "the enemies in the far right\n"
                                           "area to unlock the final area.\n",
                                                "You are now in combat.\n"
                                                "Press 1 to attack, 2 to heal,\n"
                                                "or 3 to run away.\n",
                                                    "You have lost.\n",
                                                        "You are at the shop.\n"
                                                        "Press 1 to buy a health\n"
                                                        "potions for 50 rupies.\n"
                                                        "Press 2 to upgrade your\n"
                                                        "health by 20 for 40 rupies.\n"
                                                        "Press 3 to upgrade your\n"
                                                        "strength and defense by 10\n"
                                                        "for 40 rupies.\n"
                                                        "Press 4 to leave.\n",
                                                            "You win.\n"};
    public:
        //Constructor.
        TextPieces();
        //Takes in the window for scale and places the text underneath 2 areas, along with loading
        //the font for each text piece.
        TextPieces(sf::RenderWindow &window, Area area1, Area area2, std::string fontFile);
        //Loads the normal text of how it is normally when the player is moving around.
        void loadNormalText(Character player, int numberOfHealthPotions, int playerEXP, int playerMoney);
        //Loads the combat text settings. Probably unneeded, but ensures the enemy's health is set.
        void loadCombatText(Character player, Enemy enemy,
                            int numberOfHealthPotions, int playerEXP, int playerMoney);
        //Loads the text for the player. Should be called inside Normal and Combat loading.
        void loadPlayerText(Character player, int numberOfHealthPotions, int playerEXP, int playerMoney);
        //Accessors for each text. Instructions and Player has a parameter to specify which one.
        sf::Text getEnemyText() const;
        sf::Text getInstructions(int whichText) const;
        sf::Text getPlayerText(int whichText) const;
        //Function does not see use.
        //void setFont(std::string font);
        //Draws each text element.
        void draw(sf::RenderWindow &window) const;
        //Sets the text positions of instructions and player text to be in the correct areas.
        void setTextBoxPositions(Area area1, Area area2);
        void setDefaultPlayerTextPositions(Area area);
        void setInstructionsPosition(int whichText, int x, int y);
        void setPlayerTextPosition(int whichText, int x, int y);
        void setEnemyHealthTextPosition(int x, int y);
        /*Saw use previously in fight under player.cpp but is no lolnger used.
        void updateHealth(Character player, Character enemy);
        */
        //Sets the string for the player text, enemy, and instructions appropriately.
        void setInstructionsString(int whichText, std::string string);
        void setPlayerTextString(int whichText, std::string string);
        void setEnemyHealthText(std::string string);
        //Title never changes, so this function never gets called.
        //std::string getDefaultTitle();
        std::string getDefaultText(int whichText);
        int getCharacterSize();

};
#endif //SFMLAPP_TEXTPIECES_H
