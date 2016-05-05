#include "utils.h"

bool getCollision(sf::Vector2f item1, float radius1, sf::Vector2f velocity,
                  sf::Vector2f item2, float radius2, sf::Vector2f* point){
    float a = velocity.x*velocity.x + velocity.y*velocity.y,
          b = item2.x*velocity.x + item2.y*velocity.y + item1.x*velocity.x + item1.y*velocity.y,
          c = item1.x*item1.x + item1.y*item1.y - item2.x*item1.x
            - item2.y*item1.y - item2.x*item2.x - item2.y*item2.y
            - radius2*radius2 - radius2*radius1 - radius1*radius1;
    float t;
    if(a==0){
        return false; // Velocity == (0,0)
    }else if(b==0){
        t = sqrt(-c/a);
    }else{
        t = b*b-4*a*c;
        if(t<0){
            return false;
        }else if(t==0){
            t = -b/(2*a);
        }else{
            float t2 = (-b+sqrt(t))/(2*a);
            t = (-b-sqrt(t))/(2*a);
            t = (abs(t)<abs(t2)?t:t2);
        }
    }
    if(t>1)
        return false;
    if(point!=nullptr){
        *point = item1 + velocity*t;
    }
    return true;
}
