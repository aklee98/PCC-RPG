#include <iostream>
#include <SFML/Graphics.hpp>
#include "RPGFiles/RPG.cpp"

/////////////
Player calcEXP(Player account);
Player levelUp(Player account);
/////////////


int main() {
    bool GAME_STARTED = true;
    sf::RenderWindow window(sf::VideoMode(1920,1080,32),"DaveStation");
    window.setFramerateLimit(60);
    RPG game;

    game.start(window);

    while(window.isOpen()){


        sf::Event event;

        while(window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();

            }
            game.addEvents(window, event);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            GAME_STARTED = false;
            game.exit();
        }

        window.clear(sf::Color::Black);
        if(GAME_STARTED) {
            game.addEvents(window);
            window.draw(game);
            //window.draw(game.getThumbnail());
            //window.draw(game.getInfo(window));
        }
        window.display();
    }
    return 0;
}



///////////////////////////////
/*
Player calcEXP(Player account)
{
    std::cout << "calculating EXP\n";

    account.setEXP(account.getEXP());
    std::cout << "EXP: " <<account.getEXP() << "/" << account.getEXPReq() << "\n";
    if (account.getEXP() >= account.getEXPReq())
    {
        levelUp(account);
    }
    return account;
}





Player levelUp(Player account)
{
    account.setLevel(account.getLevel()+1);
    account.setEXPReq();

    std::cout << "Level up! you are now level: " << account.getLevel() << "!\n";
    return account;
}
//////////////////////////////*/