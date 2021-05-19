#ifndef ENGINE_HEADER_HPP
#define ENGINE_HEADER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <memory>
#include <map>

//---------------------------------------------------------------------//
// Platform Dependent Code
//---------------------------------------------------------------------//

std::string getExecutablePath();


//---------------------------------------------------------------------//
// ResourceHolder - Simple Working Version
//---------------------------------------------------------------------//

void stream_of_file(sf::FileInputStream &mystream, std::string path);

template<typename T>
class ResourceHolder {
    public:
        std::shared_ptr<T> get(std::string key) {
            auto it = list.find(key);
            if (it != list.end()) {
                std::cout << "Access resource : " << key << std::endl;
                return it->second;
            }
            else {
                stream_of_file(slist[key], prefixPath + key);

                list[key] = std::make_shared<T>();

                bool success = m_loadFromStream(list[key], slist[key]);

                if (!success)
                    std::cout << "Failed to load resource : " << key << std::endl;
                else
                    std::cout << "Load resource : " << key << std::endl;
                return list[key];
            }
        }

        bool m_loadFromStream(std::shared_ptr<T> elt, sf::FileInputStream& s){
            return elt->loadFromStream(s);
        }

        ResourceHolder(){
            std::string path = getExecutablePath();
            std::size_t found = path.find_last_of("/\\");

            prefixPath = path.substr(0,found) + "/media/";

            std::cout << "Prefix Path : " << prefixPath << std::endl;
        }

    private:
        std::map<std::string, std::shared_ptr<T>> list;
        std::map<std::string, sf::FileInputStream> slist;
        std::string prefixPath;
};
template<>
bool ResourceHolder<sf::Music>::m_loadFromStream(std::shared_ptr<sf::Music> elt, sf::FileInputStream &s);


//---------------------------------------------------------------------//
// Holder
//---------------------------------------------------------------------//

struct Holder{
    ResourceHolder<sf::Image> image;
    ResourceHolder<sf::Texture> texture;
    ResourceHolder<sf::Font> font;
    ResourceHolder<sf::Shader> shader;
    ResourceHolder<sf::SoundBuffer> sound_buffer;
    ResourceHolder<sf::Music> music;
};



//---------------------------------------------------------------------//
// State
//---------------------------------------------------------------------//
class GameEngine;

class State {
    public:
        virtual void update(sf::Time dt) = 0;

        virtual void handleEvent(sf::Event event) = 0;

        virtual void draw() = 0;

        virtual void initialize() = 0;

        virtual void onResize();

        void build(
            const std::shared_ptr<GameEngine>       &engine,
            const std::shared_ptr<sf::RenderWindow> &window,
            const std::shared_ptr<Holder>           &holder);

    protected:
        std::shared_ptr<GameEngine>         stateEngine;
        std::shared_ptr<sf::RenderWindow>   window;
        std::shared_ptr<Holder>             holder;
};


//---------------------------------------------------------------------//
// GameEngine
//---------------------------------------------------------------------//
class GameEngine : public std::enable_shared_from_this<GameEngine> {
    public:
        static std::shared_ptr<GameEngine> create(){
            return std::shared_ptr<GameEngine>(new GameEngine());
        }

        void popState();

        std::shared_ptr<State> currentState();

        void gameLoop();

        template <typename T>
        void buildState(){
            states.push_back(std::make_shared<T>());
            states.back()->build(shared_from_this(), window, holder);
            states.back()->initialize();
        }

    private:
        GameEngine(){
            window = std::make_shared<sf::RenderWindow>();
            window->create(sf::VideoMode(800, 600), "GameEngine");
            window->setFramerateLimit(60);
            holder = std::make_shared<Holder>();
        }

        std::shared_ptr<sf::RenderWindow> window;
        std::vector<std::shared_ptr<State>> states;
        std::shared_ptr<Holder> holder;
};

#endif
