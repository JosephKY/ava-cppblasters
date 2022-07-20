//
//  main.cpp
//  cppblasters
//
//  Created by Joseph Shackleford on 7/20/22.
//  Copyright © 2022 Joseph Shackleford. All rights reserved.
//

#include <math.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"

using namespace sf;
using namespace std;

int main(int, char const**){
    
    RenderWindow window(VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),"Blasters");
    Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    int Scale = 20;
    Color ShuttleColor(255,0,0,0);
    
    ConvexShape shuttle;
    shuttle.setOutlineColor(Color::White);
    shuttle.setOutlineThickness(1);
    shuttle.setFillColor(Color::Transparent);
    shuttle.setPointCount(3);
    shuttle.setPoint(0, Vector2f(0 * Scale, 1 * Scale));
    shuttle.setPoint(1, Vector2f(2.5 * Scale, 0 * Scale));
    shuttle.setPoint(2, Vector2f(0 * Scale, -1 * Scale));
    shuttle.setPosition(window.getSize().x / 2,window.getSize().y / 2);
    
    while (window.isOpen()){
        // Process events
        Event event;
        while (window.pollEvent(event)){
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if(event.type == Event::MouseButtonPressed){
                float winsize2x = (window.getSize().x / 2);
                float winsize2y = (window.getSize().y / 2);
                ConvexShape pellet;
                pellet.setOutlineColor(Color::White);
                pellet.setOutlineThickness(1);
                pellet.setFillColor(Color::Transparent);
                pellet.setPointCount(4);
                pellet.setPoint(0, Vector2f(Scale/10,Scale/10));
                pellet.setPoint(1, Vector2f(Scale/10 * -1,Scale/10));
                pellet.setPoint(2, Vector2f(Scale/10 * -1,Scale/10 * -1));
                pellet.setPoint(3, Vector2f(Scale/10,Scale/10 * -1));
                pellet.setPosition(winsize2x, winsize2y);
                
                pellet.setPosition(pellet.getPosition().x, pellet.getPosition().y + 10);
            }
            
            if(event.type == Event::MouseMoved){
                //float x = sf::Mouse::getPosition(window).x - (window.getSize().x / 2);
                //float y = sf::Mouse::getPosition(window).y - (window.getSize().y / 2);
                float winsize2x = (window.getSize().x / 2);
                float winsize2y = (window.getSize().y / 2);
                float x = Mouse::getPosition(window).x;
                float y = Mouse::getPosition(window).y;
                x = x - winsize2x;
                y = y - winsize2y;
                
                float magic = 180/3.14; // trig is cool
                shuttle.setRotation(atan2(y,x) * magic);
                printf( (to_string(shuttle.getRotation()) + ", " + to_string(x) + ", " + to_string(y) + "\n").c_str()  );
            }
            
        }

        // Clear screen
        window.clear();
        
        window.draw(shuttle);

        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
