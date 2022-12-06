//elite dangerous, start out with only bottom thruster, then over time you acquire shit and you can upgrade your ship to have more thrusters, better control, better weapons, MULTIPLAYER,


#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>


sf::RenderWindow window(sf::VideoMode(1000, 1000), "window", sf::Style::Default);


const int n = 5;


class planetObjArray{
public:

    sf::CircleShape c[n];
    sf::RectangleShape r[n];
    
    planetObjArray(){
        for(int i = 0; i < n; i++){
            c[i].setRadius(rand() % 50 + 20);
            c[i].setFillColor(sf::Color({rand() % 255, rand() % 255, rand() % 255}));
            c[i].setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));

            r[i].setSize(sf::Vector2f(c[i].getGlobalBounds().width , c[i].getGlobalBounds().height));
            r[i].setFillColor(sf::Color::Transparent);
        }
    }
    
    void checkIfInt(){
        for(int i = 0; i < n; i++){
            for(int j = 1; j < n; j++ ){
                if(r[i].getGlobalBounds().intersects(r[j].getGlobalBounds()) && i != j){
                    c[i].setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
                }
            }
        }
    }
    
    void draw(){
        for (int i = 0; i < n; i++){
            r[i].setPosition(c[i].getPosition().x, c[i].getPosition().y);

            window.draw(r[i]);
            window.draw(c[i]);
        }        
    }

    
    
};

class shipObj{
public: 
    sf::RectangleShape s;

    sf::RectangleShape bounds;

    double throttle = 0;
    std::vector<double> acceleration = {0.0, 0.0};
    double theta = -90; 

    shipObj(){
        

        s.setSize(sf::Vector2f(window.getSize().x/50, window.getSize().y/100));
        s.setOrigin(s.getGlobalBounds().width/2, s.getGlobalBounds().height/2);
        s.setFillColor(sf::Color::White);
        s.setPosition(window.getSize().x/2, window.getSize().y/2);

    }
    
    void rotateShip(){

        if(abs(theta) > 359){
            theta = 0;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            theta -= 0.1;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            theta += 0.1;
        }


        s.setRotation(theta);


        //JUST BACK THRUSTER
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            throttle += 0.0001;
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            throttle -= 0.0001;
        }



        //LATER ON THRUSTERS
        // if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::S)){
        //     acceleration[1] += 0.1;
        // }
        // else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W)){
        //     acceleration[1] -= 0.1;
        // }
        // else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D)){
        //     acceleration[0] += 0.1;
        // }
        // else if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::A)){
        //     acceleration[0] -= 0.1;
        // }

    }

    void accelerateShip(){
        acceleration[0] = cos((theta * M_PI)/180);
        acceleration[1] = sin((theta * M_PI)/180);
    }

    void moveShip(){
        s.move(acceleration[0] * throttle, acceleration[1] * throttle);
    }
    
    void draw(){
        
        std::cout << "Theta: " << theta << " Cos: " <<cos((theta * M_PI)/180) <<std::endl;
        bounds.setSize(sf::Vector2f(s.getGlobalBounds().width, s.getGlobalBounds().height));
        bounds.setOrigin(bounds.getGlobalBounds().width/2, bounds.getGlobalBounds().height/2);
        bounds.setFillColor(sf::Color::Red);
        bounds.setPosition(s.getPosition().x, s.getPosition().y);
        window.draw(bounds);
        window.draw(s);
    }
};



int main(){
    // window.setFramerateLimit(4);

    planetObjArray planets;
    shipObj ship;


    while (window.isOpen()){
        sf::Event event;
 
        ship.rotateShip();
 
 
 
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                main();
            }

            
            
        }

        ship.accelerateShip();
        ship.moveShip();

        planets.checkIfInt();


        window.clear(sf::Color::Black);
        
        planets.draw();
        ship.draw();

        window.display();
    }

    return 0;
}