#include "textPieces.h"
TextPieces::TextPieces(){
    //Default Constructor.
}
//Constructor that takes in the appropriate parameters and scales the text to have the
//appropriate sizes for their character size. Afterwards, calls setTextBoxPositions() to set
//the text to their appropriate places.
TextPieces::TextPieces(sf::RenderWindow &window,Area area1, Area area2, std::string fontFile){
    if (!font.loadFromFile(fontFile))
    {
        std::cout<<"Error, "+fontFile+" does not exist."<<std::endl;
    }
    int i=0;
    characterSize = window.getSize().y/30;

    for(i=0;i<numberOfInstructions;i++){
        instructions[i].setFont(font);
        instructions[i].setCharacterSize(characterSize);
        instructions[i].setFillColor(sf::Color::White);
    }
    instructions[0].setStyle(sf::Text::Underlined);
    instructions[0].setFillColor(sf::Color::Cyan);
    instructions[1].setCharacterSize(characterSize/1.5);

    for(i=0;i<numberOfPlayerText;i++){
        playerText[i].setFont(font);
        playerText[i].setCharacterSize(characterSize);
        playerText[i].setFillColor(sf::Color::White);
    }
    enemyHealthText.setFont(font);
    enemyHealthText.setCharacterSize(characterSize);
    enemyHealthText.setFillColor(sf::Color::White);
    setTextBoxPositions(area1, area2);

}
//Sets the text strings to when the player is normally walking around.
void TextPieces::loadNormalText(Character player, int numberOfHealthPotions,
        int playerEXP,int playerMoney) {
    instructions[0].setString(defaultTitle);
    instructions[1].setString(defaultInstructionText[0]);
    loadPlayerText(player, numberOfHealthPotions,playerEXP,playerMoney);
}
//Sets the text strings to when the player is in combat, also updates the player and enemy's health
//due to how the this function is called.
void TextPieces::loadCombatText(Character player, Enemy enemy, int numberOfHealthPotions,
                                int playerEXP, int playerMoney){
    instructions[1].setString(defaultInstructionText[1]);
    loadPlayerText(player, numberOfHealthPotions,playerEXP,playerMoney);
    setEnemyHealthText("Enemy Health: "+std::to_string(enemy.getCurrentHealth()));
}
//Sets all of the player's texts to their appropriate values.
void TextPieces::loadPlayerText(Character player, int numberOfHealthPotions,
                                int playerEXP, int playerMoney){
    setPlayerTextString(0,"Health: "+std::to_string(player.getCurrentHealth())+"/"+
                          std::to_string(player.getMaxHealth()));
    setPlayerTextString(1,"Health Potions: "+std::to_string(numberOfHealthPotions));
    setPlayerTextString(2,"Strength: "+std::to_string(player.getStrength()));
    setPlayerTextString(3,"Defense: "+std::to_string(player.getDefense()));
    setPlayerTextString(4,"EXP: "+std::to_string(playerEXP));
    setPlayerTextString(5,"Rupies: "+std::to_string(playerMoney));
}
//Accessors for the appropriate places.
sf::Text TextPieces::getEnemyText() const{
    return enemyHealthText;
}
sf::Text TextPieces::getInstructions(int whichText) const {
    return instructions[whichText];
}
sf::Text TextPieces::getPlayerText(int whichText) const {
    return playerText[whichText];
}
/*Function is never used as of current.
void TextPieces::setFont(std::string font) {
    this->font.loadFromFile(font);
}
*/
//Draws all of the text in the game, except the enemyHealth which is drawn when the player's
//draw function is called and it is in combat.
void TextPieces::draw(sf::RenderWindow &window) const{
    int i=0;

    for(i=0;i<numberOfPlayerText;i++){
        window.draw(playerText[i]);
    }
    for(i=0;i<numberOfInstructions;i++){
        window.draw(instructions[i]);
    }
}
/*Function is never used currently.
std::string TextPieces::getDefaultTitle() {
    return defaultTitle;
}
*/
//returns the which text specified in the array of strings for use.
std::string TextPieces::getDefaultText(int whichText) {
    return defaultInstructionText[whichText];
}
//Sets the text positions of all of the ones in the game currently.
void TextPieces::setTextBoxPositions(Area area1, Area area2) {
    setInstructionsPosition(0, area1.getXPosition(),
                            area1.getYPosition()+(area1.getAreaHeight()+getCharacterSize()));
    setInstructionsPosition(1,getInstructions(0).getPosition().x,
                            getInstructions(0).getPosition().y+getCharacterSize());
    setDefaultPlayerTextPositions(area2);
}
void TextPieces::setInstructionsPosition(int whichText, int x, int y) {
    instructions[whichText].setPosition(x,y);
}
//sets the positions of the player's text to a determined spot specified in the function.
void TextPieces::setDefaultPlayerTextPositions(Area area) {
    setPlayerTextPosition(0,area.getXPosition(),
                          area.getYPosition()+(area.getAreaHeight()+
                          (getCharacterSize())));
    setPlayerTextPosition(1,getPlayerText(0).getPosition().x+
                                      getPlayerText(0).getGlobalBounds().width+
                                      getCharacterSize(),
                                    getPlayerText(0).getPosition().y);
    setPlayerTextPosition(2,area.getXPosition(),
                          getPlayerText(0).getPosition().y+
                          (getCharacterSize()*1.2));
    setPlayerTextPosition(3,getPlayerText(2).getPosition().x+
                            getPlayerText(2).getGlobalBounds().width+
                            getCharacterSize(),
                          getPlayerText(0).getPosition().y+
                          (getCharacterSize()*1.2));
    setPlayerTextPosition(4,area.getXPosition(),
                          getPlayerText(2).getPosition().y+
                          (getCharacterSize()*1.2));
    setPlayerTextPosition(5,getPlayerText(4).getPosition().x+
                            getPlayerText(4).getGlobalBounds().width+
                            getCharacterSize(),
                          getPlayerText(2).getPosition().y+
                          (getCharacterSize()*1.2));
    setEnemyHealthTextPosition(getPlayerText(0).getPosition().x,
                               getPlayerText(4).getPosition().y+
                               getCharacterSize()*1.2);
}
void TextPieces::setPlayerTextPosition(int whichText, int x, int y) {
    playerText[whichText].setPosition(x,y);
}
void TextPieces::setEnemyHealthTextPosition(int x, int y) {
    enemyHealthText.setPosition(x,y);
}
void TextPieces::setPlayerTextString(int whichText, std::string string) {
    playerText[whichText].setString(string);
}
void TextPieces::setInstructionsString(int whichText, std::string string) {
    instructions[whichText].setString(string);
}
void TextPieces::setEnemyHealthText(std::string string) {
    enemyHealthText.setString(string);
}
//Returns the characterSize that is generally used for all fonts.
int TextPieces::getCharacterSize() {
    return characterSize;
}
/*Function currently does not see use.
void TextPieces::updateHealth(Character player, Character enemy) {
    setPlayerTextString(0,"Health: "+std::to_string(player.getCurrentHealth())+"/"+
                          std::to_string(player.getMaxHealth()));
    //std::cout<<player.getCurrentHealth()<<std::endl;
    setEnemyHealthText("Enemy Health: "+std::to_string(enemy.getCurrentHealth()));
}
*/