#include "FantasyState.hpp"
#include "utilitary.hpp"

void FantasyState::initialize(){
    window->setVerticalSyncEnabled(true);
    window->setSize(sf::Vector2u(800, 600));
    window->setTitle("Le Monde");

    position = sf::Vector2i(8, 4);
    oldPosition = sf::Vector2i(8, 4);

    tempsDeplacement = 0.05f;
    zoom = 2.f;

    niveau = std::make_shared<Level>(holder);

    text.setFont(*holder->font.get("FiraSans-Light.otf"));
    text.setFillColor(sf::Color::Yellow);
    direction = sf::Vector2i(0,0);

    player = std::make_shared<Player>(holder->texture.get("terra.png"));
}

void FantasyState::handleEvent(sf::Event event){
    if(event.type == sf::Event::Closed)
        window->close();
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
        stateEngine->popState();
    }
}

void FantasyState::update(sf::Time){
    //On s'occupe de la direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        direction = sf::Vector2i(0,-1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        direction = sf::Vector2i(-1,0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction = sf::Vector2i(0,1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction = sf::Vector2i(1,0);
    else
        direction = sf::Vector2i(0,0);

    //On change nos coordonnees si possible
    if(clockDeplacement.getElapsedTime().asSeconds()>tempsDeplacement
       && direction != sf::Vector2i(0,0)
       && (*niveau)(position+direction))
    {
        oldPosition = position;
        position+=direction;
        clockDeplacement.restart();
        player->changeDirection(direction, tempsDeplacement);
    }

    //On deplace joueur
    if(clockDeplacement.getElapsedTime().asSeconds()<=tempsDeplacement)
    {
        float dt = clockDeplacement.getElapsedTime().asSeconds()/tempsDeplacement;
        player->setPosition( pt(position)*dt+pt(oldPosition)*(1-dt) );
    }
    else
        player->setPosition(pt(position));

    player->update();

    // Inventaire
    int g = niveau->getInventory().gold;
    if(g == 10)
        tempsDeplacement = 0.01f;
    text.setString("Gold : " + std::to_string(g));
}


void FantasyState::draw(){
    window->setView(sf::View(sf::Vector2f(player->getPosition().x, player->getPosition().y),
                             sf::Vector2f((int)((float)window->getSize().x/zoom), (int)((float)window->getSize().y/zoom))));

    window->draw(*niveau);
    window->draw(*player);

    setStandardView(window);

    window->draw(text);
}

