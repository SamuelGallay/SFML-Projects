#ifndef GAMEENGINE_MENUSTATE_H
#define GAMEENGINE_MENUSTATE_H

#include "State.h"
#include "Button.h"

class MenuState : public State{
        public:
                virtual void update(sf::Time dt);

                virtual void handleEvent(sf::Event event);

                virtual void draw();

                virtual void initialize();

        private:
                Button button;
                Button button2;
};


#endif
