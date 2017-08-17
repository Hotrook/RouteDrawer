//
//  main.cpp
//  OpenGLLearn
//
//  Created by Hotrook on 08.08.2017.
//  Copyright © 2017 Sebastian Mróz. All rights reserved.
//

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "Drawer.hpp"

int main(int argc, const char * argv[]) {
    
    srand (time(NULL));
    
    std::vector<Point> points;
    std::vector<int> route;
    
    generatePoints(points, SIZE);
    generateRoute(route, SIZE);
    
    std::mutex routeMutex;
    
    SynchronizedRoute * sr = new SynchronizedRoute( points, route, routeMutex );
    
    sf::RenderWindow * window = new sf::RenderWindow( sf::VideoMode(X_SIZE, Y_SIZE), "My Window");
    
    drawRoute(window, sr);
    
    return 0;
}
