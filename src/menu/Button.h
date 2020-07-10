#ifndef GAMEENGINE_BUTTON_H
#define GAMEENGINE_BUTTON_H

#include <SFML/Graphics.hpp>
#include <memory>

class Button : public sf::Drawable, public sf::Transformable {
    public:
        void set(std::string t,
               std::shared_ptr<sf::Font> f,
               std::shared_ptr<sf::RenderWindow> w,
               std::function<void(void)> c);
        void update();

    private:
        sf::Text text;
        sf::RectangleShape rect;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        std::shared_ptr<sf::RenderWindow> window;
        std::function<void(void)> callback;
};
#endif
