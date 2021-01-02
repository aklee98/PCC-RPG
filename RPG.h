#ifndef SFMLAPP_RPG_H
#define SFMLAPP_RPG_H
#include "../GameFiles/Game.h"
#include "merchant.cpp"
//A lot of times in this program, when loading from files, conditions are never set to avoid problems
//as those. If improvement is desired, figure out what to do if a file is not loaded into the game.
class RPG: public Game{
    private:
        //These next 2 variables, rows and columns, are made in use with the map of the game,
        //creating a 3x3 effectively.
        const int rows = 3;
        const int columns = 3;
        //numberOfEnemies determines how many enemy sprites are in the game.
        //Note if the number is raised or lower, be sure there are an appropriate # of images for
        //the game.
        static const int numberOfEnemies = 14;
        /*size is used in conjunction with what the window size is to scale a large portion
         * of this game's objects to the window's size.
        */
        sf::Vector2u size;
        //playableArea is the area in which the player moves and does all its actions in.
        Area *playableArea;
        //mapHolder is the area that encompasses the map pieces to make the map look
        //as if it's being held by this object.
        Area *mapHolder;
        //mapGrid is a multi-dimensional array of pointers which forms the 3x3 map grid of the game.
        MapCell **mapGrid = new MapCell*[rows];
        //The below three objects, Player, Enemy, and Merchant all inherit the class Character.
        //player is the player sprite that can move and fight primarily.
        Player *player;
        //enemy is created inside of the function start to be an array of Enemy objects.
        Enemy *enemy;
        //merchant is its own object which the player interacts with to purchase various things from.
        Merchant *merchant;
        /*gameText is an object that contains multiple sf::Text objects in it. Adwin would say it is
         * the worst object in the game. TextPieces as a class is used mostly
         * to ease up how many calls to text would be done on the call to start(). Has a lot of
         * specificity to it, and would not work well if implemented to another thing.
        */
        TextPieces *gameText;

    public:
        RPG();
        virtual void start(sf::RenderWindow& window);
        virtual void addEvents(sf::RenderWindow &window);
        virtual void addEvents(const sf::RenderWindow &window, sf::Event& event);
        virtual void draw(sf::RenderTarget &window, sf::RenderStates states) const;
        //This should just destruct everything that is set in the main. Unsure what else should be done.
        virtual void exit();
};
#endif //SFMLAPP_RPG_H