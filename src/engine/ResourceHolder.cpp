#include "ResourceHolder.h"

#include <cmrc/cmrc.hpp>

#include <iostream>

CMRC_DECLARE(app1);

int filesize(cmrc::file fd){
    return (reinterpret_cast<uintptr_t>(fd.end()) - reinterpret_cast<uintptr_t>(fd.begin())); 
}

sf::Font getMyFont(std::string key){
    sf::Font temp;
    sf::MemoryInputStream mystream = stream_of_file(key);
    bool success = temp.loadFromStream(mystream);
    if (success){
        std::cout << "Load resource : " << key << std::endl;
    }        
    return temp;
}


sf::MemoryInputStream stream_of_file(std::string path){
    auto fs = cmrc::app1::get_filesystem();

    auto fd = fs.open(path);

    sf::MemoryInputStream mystream;
    mystream.open(fd.begin(), filesize(fd));

    return mystream;
}


