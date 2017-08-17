//
//  SynchronizedRoute.hpp
//  OpenGLLearn
//
//  Created by Hotrook on 15.08.2017.
//  Copyright © 2017 Hotrook. All rights reserved.
//

#ifndef SynchronizedRoute_hpp
#define SynchronizedRoute_hpp

#include <stdio.h>
#include <vector>
#include "Point.hpp"
#include <mutex>

struct SynchronizedRoute{
    bool updated;
    std::vector<Point> & points;
    std::vector< int > & route;
    std::mutex & routeMutex;
    
    SynchronizedRoute(std::vector<Point> & points, std::vector< int > & route, std::mutex & mutex ) :
    route( route ),
    routeMutex(mutex),
    points(points) {
        updated = true;
    }
};

#endif /* SynchronizedRoute_hpp */
