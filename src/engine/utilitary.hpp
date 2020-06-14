#ifndef UTILITARY_HPP
#define UTILITARY_HPP

#include <SFML/Graphics.hpp>

#include <sstream>
#include <cmath>

float norme(sf::Vector2f v);

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 1)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

#endif
