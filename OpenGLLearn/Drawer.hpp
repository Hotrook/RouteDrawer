//
//  Drawer.hpp
//  OpenGLLearn
//
//  Created by Hotrook on 15.08.2017.
//  Copyright © 2017 Hotrook. All rights reserved.
//

#ifndef Drawer_hpp
#define Drawer_hpp

#include <stdio.h>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include "SynchronizedRoute.hpp"

const int X_SIZE = 1440;
const int Y_SIZE = 850;
const int SIZE = 10;
const int RADIUS = 4;

sf::Color generateRandomColor();

void createCircle(Point & point, sf::CircleShape & circle);

void drawLine( Point & first, Point & second, sf::RenderWindow & window );

void generateRoute( std::vector<Point>& route, int size );

void drawPaths(std::vector<Point> & route, sf::RenderWindow & window);

void drawCircles(std::vector<Point> & route, sf::RenderWindow & window);

void drawRoute( std::vector<Point> & route, sf::RenderWindow & window );

void permute( std::vector<Point> & route );

void drawRoute(sf::RenderWindow * window, SynchronizedRoute * sroute);



#endif /* Drawer_hpp */
