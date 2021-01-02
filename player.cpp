#include "player.h"
//Default Constructor.
Player::Player(): Character(){
    //Default Constructor
}
/*Constructor for the player. Calls Character's constructor in relation to its health, strength,
 * defense, and the area and image. healthPotion's number is set along with exp and rupies being
 * constructed.
*/
Player::Player(int health, int strength, int defense, int healthPotions,
        Area area, std::string playerImage):
    Character(health,strength, defense, area, playerImage) {
    //Implementation above.
    healthPotion = HealthPotion(healthPotions);
    exp = EXP(0);
    rupies = Stat(0);
}
/*Overloaded function to draw the player sprite when the player
 * is still alive and also the health of an enemy when the player is in a fight.
*/
void Player::draw(sf::RenderWindow& window,sf::Text enemyHealth) const{
    if(isDead()==false){
        window.draw(getSprite());
    }
    if(inCombat==true){
        window.draw(enemyHealth);
    }
}
/*move will move the player according to key press of Left and A, Right and D, Up and W, or Down and S.
 * If the player sprite hits any of the boundaries of the area,
 * then the player will move to the other side of the area.
 * Based on the xLocation and yLocation of the player,
 * the player will not be able to move in certain ways. This is related to the mapGrid and which enemies
 * are still alive, thus limiting the player to the map areas. This function is very, very reliant
 * on a lot of variables for it to work and then move the player appropriately along the map.
 *
 * Other details include being sure to respawn the enemies if they are considered dead upon moving to
 * another map area. Calling the respawn here ensures they do not respawn as soon as you finish a fight.
 *
 * Tips to improve this function would be to possibly call another function, passing in certain
 * parameters that will then do what one section does which could be equivalent to the rest.
*/
void Player::move(Area area, MapCell *mapGrid[3],
        Enemy enemy[],const int numberOfEnemies, Character &merchant){
    //Movement is used to determine how fast the player's sprite will go based on the area.
    movement = area.getAreaHeight()/100;
    //If the player presses Left or A, then the player will move left and into areas that are not
    //restricted. Restricted areas include first column areas, and if the player
    //has yet to beat the three enemies to gain access to the middle map area.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        //If the player has beaten all of the required enemies, then it has access to the final area.
        if(getSprite().getPosition().x<area.getXPosition()+movement) {
            if(xLocation == 2 && yLocation == 1 &&
            (enemy[10].isDead()==true && enemy[11].isDead()==true && enemy[12].isDead()==true)){
                setPosition((area.getAreaWidth() + area.getXPosition() -
                             (getImage().getSize().x * getScale())) - movement,
                            getSprite().getPosition().y);
                //For loop used to respawn any enemy that was dead and is allowed to.
                for(int i=0;i<numberOfEnemies;i++){
                    enemy[i].checkRespawn();
                }
                xLocation--;
                mapGrid[yLocation][xLocation].setColor(yLocation,xLocation);
                mapGrid[yLocation][xLocation+1].setColor(yLocation,xLocation);
            }
            //Otherwise, then it has the normal limitations of movement.
            else if (!(xLocation == 0 || xLocation == 2 && yLocation == 1)) {
                setPosition((area.getAreaWidth() + area.getXPosition() -
                                    (getImage().getSize().x * getScale())) - movement,
                                            getSprite().getPosition().y);
                for(int i=0;i<numberOfEnemies;i++){
                    enemy[i].checkRespawn();
                }
                xLocation--;
                mapGrid[yLocation][xLocation].setColor(yLocation,xLocation);
                mapGrid[yLocation][xLocation+1].setColor(yLocation,xLocation);
            }
        }
        //If the player is not moving into any area, then it is okay to move the player sprite normally.
        else{
            character.move(-movement,0);
        }
    }
    //Implementation for the rest of the keys is as above.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (getSprite().getPosition().x >
        (area.getAreaWidth() + area.getXPosition() - (getImage().getSize().x * getScale())) - movement) {
            if (!(xLocation == 2 || xLocation == 0 && yLocation == 1)) {
                setPosition(area.getXPosition() + movement,
                                       getSprite().getPosition().y);
                for(int i=0;i<numberOfEnemies;i++){
                    enemy[i].checkRespawn();
                }
                xLocation++;
                mapGrid[yLocation][xLocation].setColor(yLocation,xLocation);
                mapGrid[yLocation][xLocation-1].setColor(yLocation,xLocation);

            }
        }
        else {
            character.move(movement, 0);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        if(getSprite().getPosition().y<area.getYPosition()+movement){
            if(!(yLocation==0|| (xLocation==1 && yLocation==2))) {
                setPosition(getSprite().getPosition().x,
                        area.getAreaHeight() + area.getYPosition()
                            -(getImage().getSize().y * getScale()) - movement);
                for(int i=0;i<numberOfEnemies;i++){
                    enemy[i].checkRespawn();
                }
                yLocation--;
                mapGrid[yLocation][xLocation].setColor(yLocation,xLocation);
                mapGrid[yLocation+1][xLocation].setColor(yLocation,xLocation);
            }
        }
        else {
            character.move(0, -movement);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
    sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        if(getSprite().getPosition().y>(area.getAreaHeight()+area.getYPosition()
        -(getImage().getSize().y*getScale())-movement)){
            if(!(yLocation==2|| xLocation==1 && yLocation==0) ) {
                setPosition(getSprite().getPosition().x,
                                   area.getYPosition() + movement);
                for(int i=0;i<numberOfEnemies;i++){
                    enemy[i].checkRespawn();
                }
                yLocation++;
                mapGrid[yLocation][xLocation].setColor(yLocation,xLocation);
                mapGrid[yLocation-1][xLocation].setColor(yLocation,xLocation);

            }

        }
        else {
            character.move(0, movement);
        }
    }
    //At the end of the movement, check if the player has collided with any of the enemies.
    checkCollision(enemy, numberOfEnemies, merchant);
}
/*checkCollision checks to see if the player has collided with any of the characters.
 * Perhaps not the best name as it also makes sure the enemies that are in the area
 * are there, and sets their positions to also be onScreen, otherwise setting them to be off if
 * they are not.
 *
 * If the player has collided with any of the characters, specifically the enemies or merchant,
 * then set the appropriate player status to true, so the events in "RPG.cpp" can be run.
*/
void Player::checkCollision(Enemy enemy[], int numberOfEnemies, Character &merchant){
    for(int i=0;i<numberOfEnemies;i++) {
        checkSameArea(enemy[i]);
        if (getSprite().getGlobalBounds().intersects(enemy[i].getSprite().getGlobalBounds())){
            setCombatStatus(true);
        }
    }
    checkSameArea(merchant);
    if(getSprite().getGlobalBounds().intersects(merchant.getSprite().getGlobalBounds())){
        setShopStatus(true);
    }
}
void Player::checkSameArea(Enemy &enemy) {
    if(enemy.isDead()==false  &&
       getXLocation()== enemy.getXLocation() && getYLocation() == enemy.getYLocation()) {
        enemy.setOnScreen(true);
        enemy.setPosition(enemy.getSpawnXPosition(), enemy.getSpawnYPosition());
    }
    else{
        enemy.setOnScreen(false);
        enemy.setPosition(-500,-500);
    }
}
void Player::checkSameArea(Character &merchant) {
    if(getXLocation()== merchant.getXLocation() && getYLocation() == merchant.getYLocation()) {
        merchant.setOnScreen(true);
        merchant.setPosition(merchant.getSpawnXPosition(), merchant.getSpawnYPosition());
    }
    else{
        merchant.setOnScreen(false);
        merchant.setPosition(-500,-500);
    }
}

/*fight takes in an enemy and the TextPieces object to then interact with them. Essentially,
 * it will ask the player to attack, heal themselves with a health potion, or run away. A
 * key press determines what action happens.
 *
 * If the player attacks, then the player and enemy deal damage to each other.
 * If the player heals, then the player heals, but the enemy still does damage to the player.
 * If the player runs away, then the combat comes to an end.
 *
 * sleeping the thread occurs plenty in this, and could be done better with usage of SFML's
 * clock? instead.
*/
void Player::fight(Enemy &enemy, TextPieces &text){
    //playerDamage and enemyDamage are set by calling calculateDamage in the Character class.
    int playerDamage = calculateDamage(enemy.getDefense());
    int enemyDamage = enemy.calculateDamage(getDefense());
    //The player will attack if Num1 is pressed. The enemy will also attack.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        dealDamage(enemy,playerDamage,enemyDamage);
        //Update the health here. Not needed in final product right now, because of implementation in
        //"RPG.cpp"
        //text.updateHealth(*this, enemy);
        /*Sleep_for is used to stop the player from potentially holding down the attack button and
         * going too fast. Although that doesn't really work as intended.
        */
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    //The player will heal if Num2 is pressed and the enemy will attack still.
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        //Check if the player has enough health potions and heal the player.
        healthPotion.checkPotion( *this);
        dealDamage(enemy,0,enemyDamage);
        //text.updateHealth(*this, enemy);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    //If Num3 is pressed, then the player will move away from the enemy, ending combat.
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        moveAway(enemy);
        //Set the enemy health back to max.
        enemy.setCurrentHealth(enemy.getMaxHealth());
        setCombatStatus(false);
        //Set the text of the game back to its normal defaults, mainly the instructions and
        //the enemy's health text bar are adjusted here.
        text.loadNormalText(*this, getHealthPotion(),
                getEXP(),getRupies());
    }
    /*If the enemy's health is reduced to 0, then add to the player's exp amount, give the player the
     * rupies the enemy had, and then call enemy's isDefeated function to set appropriate variables.
     *
     * Just like with the above implementation of runAway, set the player back to normal and
     * load the normal text.
    */
    if (enemy.getCurrentHealth() <= 0) {
        addRupieAmount(enemy.getMoney());
        calculateEXP(enemy.getEXP(),*this);
        enemy.isDefeated();
        enemy.setCurrentHealth(enemy.getMaxHealth());
        setCombatStatus(false);
        text.loadNormalText(*this, getHealthPotion(),
                            getEXP(),getRupies());
    }
    //If the player dies, then turn their combat status to off and make them defeated. As such,
    //in this state, the player has lost and cannot play anymore.
    if(getCurrentHealth() <=0){
        setCombatStatus(false);
        isDefeated();
        setCurrentHealth(0);
    }
}
//Have the player move back the direction it came away from the enemy.
void Player::moveAway(Character character) {
    //Just to make sure the player moves over twice the distance it usually would to move
    //into the enemy. This is simply to ensure the player doesn't get trapped.
    float moveAway = movement*2;
    //The next 8 variables are simply used to make the understanding of each side of the sprites easier.

    int playerRightSide = getSprite().getPosition().x+(getImage().getSize().x*getScale());
    int playerLeftSide = getSprite().getPosition().x;
    int playerTopSide = getSprite().getPosition().y;
    int playerBottomSide = getSprite().getPosition().y+(getImage().getSize().y*getScale());

    int enemyRightSide = character.getSprite().getPosition().x+
            (character.getImage().getSize().x*character.getScale());
    int enemyLeftSide = character.getSprite().getPosition().x;
    int enemyTopSide = character.getSprite().getPosition().y;
    int enemyBottomSide =  character.getSprite().getPosition().y+(
            character.getImage().getSize().y*character.getScale());
    //The second condition for each is required to check which side the player is on.
    //If the player is on the right side of the enemy, then move the player to the right.
    if(playerLeftSide<enemyRightSide && playerRightSide-(movement*2)>enemyLeftSide){

        this->character.move(moveAway,0);
    }
    //If the player is to the left of the enemy, then move the player to the left.
    if(playerRightSide>enemyLeftSide && playerLeftSide+(movement*2)<enemyRightSide){
        this->character.move(-moveAway,0);
    }
    //If the player is downward of the enemy, move the player down.
    if(playerTopSide<enemyBottomSide && playerBottomSide-(movement*2)>enemyTopSide){
        this->character.move(0,moveAway);
    }
    //If the player is above the enemy, move the player up.
    if(playerBottomSide>enemyTopSide && playerTopSide+(movement*2)<enemyBottomSide){
        this->character.move(0,-moveAway);
    }

}
//Miscellaneous setters and getters for the combat and shop status of the player.
void Player::setCombatStatus(bool status) {
    inCombat = status;
}
void Player::setShopStatus(bool status) {
    inShop = status;
}
bool Player::inFight() const{
    return inCombat;
}
bool Player::isBuying() const{
    return inShop;
}

//exp object interaction.

int Player::getEXP() const{
    return exp.getEXP();
}
/*The below function never sees use currently
void Player::setEXP(int EXP) {
    exp.setEXP(EXP);
}
*/
void Player::calculateEXP(int EXP, Character &player) {
    exp.calculateEXP(EXP, player);
}

//rupies object interaction.

int Player::getRupies() const{
    return rupies.getCurrentStat();
}
void Player::addRupieAmount(int rupies) {
    this->rupies.setCurrentStat(rupies+this->rupies.getCurrentStat());
}
void Player::subtractRupieAmount(int rupies){
    int finalAmount = this->rupies.getCurrentStat()-rupies;
    if(finalAmount<0){
        finalAmount=0;
    }
    this->rupies.setCurrentStat(finalAmount);
}

//healthPotion object interaction.

int Player::getHealthPotion() const{
    return healthPotion.getNumberOfHealthPotions();
}
void Player::setNumberOfHealthPotions(int number) {
    healthPotion.setNumberOfPotions(number);
}
void Player::checkPotion(){
    healthPotion.checkPotion(*this);
}