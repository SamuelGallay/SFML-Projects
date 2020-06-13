#ifndef Physical_hpp
#define Physical_hpp

#include <SFML/Graphics.hpp>

class Physical : public sf::Transformable , public sf::Drawable
{
public:
    Physical();
    Physical(Physical const&);
    virtual void update(sf::Time dt);
    
    sf::Vector2f getVelocity(){
        return velocity;
    }
    float getAngularVelocity(){
        return angularVelocity;
    }
    float getMass(){
        return mass;
    }
    
    void setVelocity(sf::Vector2f v){
        velocity = v;
    }
    void setAngularVelocity(float a){
        angularVelocity = a;
    }
    void setMass(float m){
        mass = m;
    }
    
private:
    sf::Vector2f velocity;
    float angularVelocity;
    float mass;
};

#endif /* Physical_hpp */
