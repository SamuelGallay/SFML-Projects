#include "ResourceHolder.h"

#include <cmrc/cmrc.hpp>

#include <iostream>

CMRC_DECLARE(holder);

int filesize(cmrc::file fd){
    return (reinterpret_cast<uintptr_t>(fd.end()) - reinterpret_cast<uintptr_t>(fd.begin())); 
}

sf::Font getMyFont(std::string key){
    sf::Font temp;
    sf::MemoryInputStream mystream;
    stream_of_file(mystream, key);
    bool success = temp.loadFromStream(mystream);
    if (success){
        std::cout << "Load resource : " << key << std::endl;
    }        
    return temp;
}


void stream_of_file(sf::MemoryInputStream &mystream, std::string path){
    auto fs = cmrc::holder::get_filesystem();

    auto fd = fs.open(path);

    mystream.open(fd.begin(), filesize(fd));
}
