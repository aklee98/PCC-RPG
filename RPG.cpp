#include "RPG.h"
RPG::RPG(){
    image_path = "RPGFiles/resources/images/RPG.png";
    title = "RPG";
}
void RPG::start(sf::RenderWindow& window){
    //size is set to the window's size, so everything is scaled appropriately
    // to whatever window setting is given.
    size = window.getSize();
    //playableArea is scaled appropriately to the window's size.
    playableArea = new Area(size.x/3, size.x/3,
            size.x/6, size.y/9.5, sf::Color::Green);
    //imageTracker is used to keep track of which MapCell is being edited in the for loop.
    int imageTracker = 0;
    //mapScale is a number made to scale down the images to an appropriate size for when in use.
    float mapScale = 0.3;
    //this for loop makes the mapGrid object into a multi-dimensional array of 3x3.
    for(int i=0;i<rows;i++){
        *(mapGrid+i) = new MapCell[columns];
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            /*An overloaded constructor is called, giving the object its values for the image scale,
             * the row, column, the image file, the outline color and its thickness, and
             * the window's size for scaling purposes.
            */
            (*(*(mapGrid + i) + j))= MapCell(mapScale,i,j,
                    "RPGFiles/resources/images/map"+std::to_string(imageTracker+1)+".jpg",
                    sf::Color::Blue,1,size);
            //the texture needs to be set twice, I'm unsure why.
            (*(*(mapGrid + i) + j)).setTextureAndColor(
                    "RPGFiles/resources/images/map"+std::to_string(imageTracker+1)+".jpg");
            //Increments imageTracker so that the next image can be taken from the folder.
            imageTracker++;
        }
    }
    /*The below variables are for adjusting for the construction of the mapHolder.
     *holderScale is for the scaling of the holder which holds the map pieces and grid.
     * mapHolderWidth and height are for the size of the entire holder.
     * the mapHolder(X or Y)PosAdjust variables adjust the size so that
     * the center of the mapHolder area has the MapCell objects in the middle.
    */
    float holderScale = 1.1;
    int mapHolderWidth = (*(*(mapGrid + 0) + 0)).getTexture().getSize().x * 3 *
            (*(*(mapGrid + 0) + 0)).getScale();
    int mapHolderHeight = (*(*(mapGrid + 0) + 0)).getTexture().getSize().y * 3 *
            (*(*(mapGrid + 0) + 0)).getScale();
    int mapHolderXPosAdjust = mapHolderWidth * holderScale - mapHolderWidth;
    int mapHolderYPosAdjust = mapHolderHeight * holderScale - mapHolderHeight;
    //mapHolder is an object of class Area which is just to hold space for the map pieces to look nice.
    //Of note, this is the only other Area to serve this purpose. If desired, consider doing more for
    //all of the sf::Text objects in the game too in the future.
    mapHolder = new Area(mapHolderWidth*holderScale,
                   mapHolderHeight*holderScale,
                   (*(*(mapGrid+0) + 0)).getMap().getPosition().x - 0.5*mapHolderXPosAdjust,
                   (*(*(mapGrid+0) + 0)).getMap().getPosition().y - 0.5*mapHolderYPosAdjust,
                   sf::Color::Yellow);

    //Initializes the player object with the following Stat values, number of health potions, and
    //sets the area and image.
    player = new Player(100, 10,0, 2,*playableArea,
                        "RPGFiles/resources/images/player.png");

    //Initializes the merchant object to be in the playableArea as well.
    merchant = new Merchant(*playableArea,
                            "RPGFiles/resources/images/merchant.png");

    //Due to how big the merchant's image is, a scale is further applied to it. This is done based
    //on the individual images and developer design. If the image was smaller, this line may not be needed.
    merchant->setScale(merchant->getScale()/1.25);
    //Sets the spawn location of the merchant to be a certain place.
    //This needs to be custom set as will be explained later with how the location of a sprite works
    //in conjunction with SFML's draw.
    merchant->setXandYSpawnPosition((playableArea->getAreaWidth()/2)+playableArea->getXPosition()-
                                            (merchant->getImage().getSize().x*merchant->getScale()/2),
                                    ((playableArea->getAreaHeight()/2)+playableArea->getYPosition()-
                                            (merchant->getImage().getSize().y*merchant->getScale())/2));
    //the merchant position is set to be that location due to it being in the first map cell
    //where the player starts.
    merchant->setPosition(merchant->getSpawnXPosition(),merchant->getSpawnYPosition());

    /*the enemy object is made to be an array, and then individually for all numberOfEnemies,
     * gives each their health, strength, defense, exp, and rupies. The former three are used
     * when the enemy fights while the latter two are to give the player a reward for winning.
    */
    enemy = new Enemy[numberOfEnemies];
    enemy[0] = Enemy(25,2,0,25,25);
    enemy[1] = Enemy(50,5,0,50,50);
    enemy[2] = Enemy(40,10,5,100,100);
    enemy[3] = Enemy(100, 20,20,200,200);
    enemy[4] = Enemy(80, 20, 50, 300, 150);
    enemy[5] = Enemy(300, 50, 50, 1000, 500);
    enemy[6] = Enemy(150, 40, 20, 500, 300);
    enemy[7] = Enemy(400, 80, 40, 500, 1000);
    enemy[8] = Enemy(200,50, 20, 400, 300);
    enemy[9] = Enemy(200, 30, 30,400, 300);
    enemy[10] = Enemy(200, 200, 50, 5000, 5000);
    enemy[11] = Enemy(1000, 100, 200, 7500, 7500);
    enemy[12] = Enemy(2000,200,200,10000,10000);
    enemy[13] = Enemy(4000, 300, 300, 0, 0);

    //The for loop below sets the images of each enemy and their position to be off-screen.
    //The position is done due to how draw works in conjunction with sprite positions.
    //This is because the sprite is still in that position even if it is not drawn, so
    //it needs to be set off of the screen in a different position to not interfere with the player's
    //movement.
    //A constructor is not made to set the image as well, because of the above implementation
    //with unique values set for each enemy.
    for(int i=0;i<numberOfEnemies;i++){
        enemy[i].setImage("RPGFiles/resources/images/enemies/enemy"+std::to_string(i+1)+".png",
                *playableArea);
        enemy[i].setPosition(-500,-500);
    }
    //As above with the merchant object, some enemies have way too large images, so more scale is
    //applied to them.
    enemy[1].setScale(enemy[1].getScale()/1.5);
    enemy[3].setScale(enemy[3].getScale()/1.5);
    enemy[8].setScale(enemy[8].getScale()/1.5);
    enemy[12].setScale(enemy[12].getScale()/1.5);

    //The location of each enemy is then set in conjunction with the map. This is so that if the
    //player enters a certain map cell, say (1,1), then the characters in that location will spawn.
    enemy[0].setXandYLocation(0,1);
    for(int i=0;i<2;i++){
        enemy[i+1].setXandYLocation(0,2);
        enemy[3+i].setXandYLocation(1,0);
        enemy[5+i].setXandYLocation(1,2);
        enemy[8+i].setXandYLocation(2,2);
        enemy[10+i].setXandYLocation(2,1);
        enemy[12].setXandYLocation(2,1);
    }
    enemy[7].setXandYLocation(2,0);
    enemy[13].setXandYLocation(1,1);

    //The next lines are to set the respawn of certain enemies off so they do not respawn.
    //With how big enemy[5] is as a sprite, then this is done to allow the player to access another
    //part of the map.
    //The ones in the for loop are done, so that upon the player beating those enemies, the player
    //will gain access to the final area of the game, and thus the final boss.
    enemy[5].setRespawn(false);
    for(int i=0;i<3;i++){
        enemy[10+i].setRespawn(false);
    }

    //This section is simply setting the spawn locations of each enemy just like the merchant.

    enemy[0].setXandYSpawnPosition(playableArea->getAreaWidth()+playableArea->getXPosition()-
                                   (enemy[0].getImage().getSize().x*enemy[0].getScale()*2),
                                   (playableArea->getAreaHeight()+playableArea->getYPosition()-
                                    (enemy[0].getImage().getSize().y*enemy[0].getScale()))/2);
    enemy[1].setXandYSpawnPosition((playableArea->getAreaWidth()/2)+playableArea->getXPosition()-
                                   (enemy[1].getImage().getSize().x*enemy[1].getScale()),
                                   (playableArea->getAreaHeight()+playableArea->getYPosition()-
                                     (enemy[1].getImage().getSize().y*enemy[1].getScale())));
    enemy[2].setXandYSpawnPosition(((playableArea->getAreaWidth())+playableArea->getXPosition())-
                                   (enemy[2].getImage().getSize().x*enemy[2].getScale()),
                                   (playableArea->getAreaHeight()+playableArea->getYPosition()-
                                   (enemy[2].getImage().getSize().y*enemy[2].getScale())));
    enemy[3].setXandYSpawnPosition(((playableArea->getAreaWidth()/2)+
                                   playableArea->getXPosition())-
                                   (enemy[3].getImage().getSize().x*enemy[3].getScale()/2),
                                     (playableArea->getYPosition())+
                                     (playableArea->getAreaHeight()/2));
    enemy[4].setXandYSpawnPosition(playableArea->getAreaWidth()+playableArea->getXPosition()-
                                   (enemy[4].getImage().getSize().x*enemy[4].getScale()),
                                   (playableArea->getYPosition()));
    enemy[5].setXandYSpawnPosition((playableArea->getAreaWidth()/2)+playableArea->getXPosition(),
                                   (playableArea->getYPosition()));
    enemy[6].setXandYSpawnPosition((playableArea->getAreaWidth()/2)+playableArea->getXPosition(),
                                   (playableArea->getAreaHeight()+playableArea->getYPosition()-
                                    (enemy[6].getImage().getSize().y*enemy[6].getScale())));
    enemy[7].setXandYSpawnPosition((playableArea->getAreaWidth())+playableArea->getXPosition()-
                                   (enemy[7].getImage().getSize().x*enemy[7].getScale()),
                                   (playableArea->getYPosition()));
    enemy[8].setXandYSpawnPosition((playableArea->getAreaWidth())+playableArea->getXPosition()-
                                   (enemy[8].getImage().getSize().x*enemy[8].getScale()),
                                   ((playableArea->getAreaHeight())+playableArea->getYPosition()-
                                    (enemy[8].getImage().getSize().y*enemy[8].getScale())));
    enemy[9].setXandYSpawnPosition((playableArea->getAreaWidth()/2)+playableArea->getXPosition()-
                                   (enemy[9].getImage().getSize().x*enemy[9].getScale()),
                                   ((playableArea->getAreaHeight())+playableArea->getYPosition()-
                                    (enemy[9].getImage().getSize().y*enemy[9].getScale())));
    enemy[10].setXandYSpawnPosition(playableArea->getXPosition(),
                                   ((playableArea->getAreaHeight()/2)+playableArea->getYPosition())-
                                   enemy[11].getImage().getSize().y*enemy[11].getScale());
    enemy[11].setXandYSpawnPosition(playableArea->getXPosition(),
                                    ((playableArea->getAreaHeight())+playableArea->getYPosition())-
                                    enemy[11].getImage().getSize().y*enemy[11].getScale());
    enemy[12].setXandYSpawnPosition((playableArea->getAreaWidth())+playableArea->getXPosition()-
                                    (enemy[12].getImage().getSize().x*enemy[12].getScale()),
                                    ((playableArea->getAreaHeight()/2)+playableArea->getYPosition())-
                                    enemy[9].getImage().getSize().y*enemy[9].getScale());
    enemy[13].setXandYSpawnPosition((playableArea->getAreaWidth()/2)+playableArea->getXPosition(),
                                    ((playableArea->getAreaHeight()/2)+playableArea->getYPosition()));
    //gameText takes in the window size for scaling, playableArea and mapHolder for positions
    //of the text objects.
    gameText = new TextPieces(window, *mapHolder, *playableArea,
            "RPGFiles/resources/OpenSans-Bold.ttf");
    //Will proceed to set the default text when the player first starts the game.
    gameText->loadNormalText(*player,player->getHealthPotion(),
            player->getEXP(), player->getRupies());
    //This line is called out here as well to be sure that the text objects in gameText are set
    //in the appropriate places.
    gameText->setDefaultPlayerTextPositions(*playableArea);
}
void RPG::addEvents(sf::RenderWindow &window){
    //No other events currently.
    //Unsure if this ever needs any. Perhaps some of the events in the
    //next function should be placed here.
}
void RPG::addEvents(const sf::RenderWindow &window, sf::Event& event){
    /*Event used to check for player input when freely moving.
     *
     * Section 1)
     * If the player presses a key and the player is not in a fight, nor buying anything, nor
     * dead, and the appropriate keys are pressed, then run player's move function to
     * then check if any of the keys pressed were correct for movement.
     * The problem with this is that it has to check for all of the keys in a weird if manner?
     * Unsure how it could be better done than to check for all of that.
     * For better implementation, consider figuring out how to implement a switch statement maybe.
     *
     * Section 2)
     * Otherwise, if a different key is pressed, Num2, then heal the player if the player has enough
     * health potions, set the text appropriately, and have the thread sleep just in case
     * the player is holding down the button. The problem with this implementation is that it does not
     * work to this intended goal for stopping the hold. Consider switching over to a timer usage with
     * SFML's clock(is that right?) usage.
    */
    if(event.type == sf::Event::KeyPressed &&
    (player->inFight()==false && player->isBuying()==false && player->isDead()==false)){
        //Read above for section 1's implementation.
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            player->move(*playableArea, mapGrid, enemy, numberOfEnemies, *merchant);
        }
        //Read above for section 2's implementation.
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            player->checkPotion();
            gameText->loadNormalText(*player,player->getHealthPotion(),
                                     player->getEXP(), player->getRupies());
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    /*If the above conditions are not reached, then that must mean the player is in a fight,
     * buying something, or dead, which then are covered below.
     *
     * Keep in mind, unlike the player's move function above, the lines for the merchant and enemies
     * when the if conditions are met are constantly being called which can possibly slow the game up.
     * If possible and if work is continued, fix the below to be like above, keeping in mind the comments
     * from the previous section.
     *
     * Section 1)
     * A for loop is run to check if the player collides with any of the enemy sprite's and if so,
     * then the text is set to load in the enemy's health(along with the rest of combat stuff),
     * and the player fights with the selected enemy. Appropriately set the positions of the
     * text pieces to just in case any of their values in length get bigger after the fight.
     *
     * Section 2)
     * If the player gets in range of the merchant, then set the text appropriately for the instructions
     * to tell the player what to do, and then check to see what keys the player will press inside
     * the showMenu function from the merchant. The player must have enough rupies to purchase the
     * items appropriately chosen.
     *
     * Note if the player is dead, then the player should not be able to do anything. That is why
     * there is no implementation below for any of that condition.
    */
    else{
        //Section 1)
        for(int i=0;i<numberOfEnemies;i++) {
            if (player->getSprite().getGlobalBounds().intersects(
                    enemy[i].getSprite().getGlobalBounds())){
                //The health of the player and enemy will update
                gameText->loadCombatText(*player,enemy[i],
                        player->getHealthPotion(),
                        player->getEXP(),player->getRupies());
                player->fight(enemy[i], *gameText);
                gameText->setTextBoxPositions(*mapHolder, *playableArea);
            }
        }
        //Section 2.
        if (player->getSprite().getGlobalBounds().intersects(
                merchant->getSprite().getGlobalBounds())){
            merchant->showMenu(*player, *gameText);
            gameText->setTextBoxPositions(*mapHolder, *playableArea);
        }
    }
    /*Considering these lines run last, then they should? overwrite any of the text setting from any
     * of the other events.
     *
     * If the player is dead, then set the instructions to say the player has lost.
     * If the player beats the final boss, then set the instructions to say the player has won.
    */
    if(player->isDead()==true){
        gameText->setInstructionsString(1,gameText->getDefaultText(2));
    }
    if(enemy[13].isDead()==true){
        gameText->setInstructionsString(1,gameText->getDefaultText(4));
    }
}
//Unsure if draw should have a condition to stop drawing everything, but as it is, then it just draws
//All of the objects in the game with their following conditions and all.
void RPG::draw(sf::RenderTarget &window, sf::RenderStates states) const{
    playableArea->draw(dynamic_cast<sf::RenderWindow &>(window));

    mapHolder->draw(dynamic_cast<sf::RenderWindow &>(window));
    //the mapGrid needs to be drawn second, so that mapHolder can be below it and thus display both.
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            (*(*(mapGrid + i) + j)).draw(dynamic_cast<sf::RenderWindow &>(window));
        }
    }

    for(int i=0;i<numberOfEnemies;i++){
        enemy[i].ifOnscreen(dynamic_cast<sf::RenderWindow &>(window), *player);
    }
    merchant->draw(dynamic_cast<sf::RenderWindow &>(window));
    player->draw(dynamic_cast<sf::RenderWindow &>(window),gameText->getEnemyText());

    //Draws the text.
    gameText->draw(dynamic_cast<sf::RenderWindow &>(window));
}
//This should just destruct everything that is set in the main. Unsure what else should be done.
void RPG::exit(){
    //Destructors for when the game exits.
    delete playableArea, player, mapHolder;
    for(int i=0;i<rows;i++){
        delete []*(mapGrid+i);
    }
    delete []enemy;
    delete merchant;
    delete []mapGrid;
    delete gameText;
}