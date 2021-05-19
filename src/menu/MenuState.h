#ifndef GAMEENGINE_MENUSTATE_H
#define GAMEENGINE_MENUSTATE_H

#include "Button.h"

#include "engine.h"

class MenuState : public State{
        public:
                virtual void update(sf::Time dt);

                virtual void handleEvent(sf::Event event);

                virtual void draw();

                virtual void initialize();

                virtual void onResize();

        private:
                Button button;
                Button button2;
                Button button3;
                Button button4;
                Button button5;
};


#endif
