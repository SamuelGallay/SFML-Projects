#ifndef GAMEENGINE_RESOURCEHOLDER_H
#define GAMEENGINE_RESOURCEHOLDER_H

#include <string>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

void stream_of_file(sf::MemoryInputStream &mystream, std::string path);

template<typename T>
class ResourceHolder {
    public:
        const T& get(std::string key) {
            auto it = list.find(key);
            if (it != list.end()) {
                std::cout << "Access resource : " << key << std::endl;
                return it->second;
            }
            else {
                auto &elt = list[key];

                //bool success = elt.loadFromFile(key);

                stream_of_file(slist[key], key);
                bool success = elt.loadFromStream(slist[key]);

                if (!success)
                    std::cout << "Failed to load resource : " << key << std::endl;
                else
                    std::cout << "Load resource : " << key << std::endl;
                return elt;
            }
        }

    private:
        std::map<std::string, T> list;
        std::map<std::string, sf::MemoryInputStream> slist;
};

struct Holder{
    ResourceHolder<sf::Image> image;
    ResourceHolder<sf::Texture> texture;
    ResourceHolder<sf::Font> font;
    ResourceHolder<sf::Shader> shader;
};

#endif
