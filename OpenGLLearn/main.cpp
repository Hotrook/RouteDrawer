//
//  main.cpp
//  OpenGLLearn
//
//  Created by Sebastian Mróz on 08.08.2017.
//  Copyright © 2017 Sebastian Mróz. All rights reserved.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;


const int X_SIZE = 1440;
const int Y_SIZE = 850;
const int SIZE = 10;
const int RADIUS = 4;

struct Point{
    int x;
    int y;
    
    Point( int x, int y) {
        this->x = x;
        this->y = y;
    }
};

struct SynchronizedRoute{
    bool updated;
    vector<Point> & route;
    std::mutex & routeMutex;
    
    SynchronizedRoute(vector<Point> & route, std::mutex & mutex ) :
        route( route ),
        routeMutex(mutex) {
        updated = true;
    }
};


sf::Color generateRandomColor();

void createCircle(Point & point, sf::CircleShape & circle);

void drawLine( Point & first, Point & second, sf::RenderWindow & window );

void generateRoute( vector<Point>& route, int size );

void drawPaths(vector<Point> & route, sf::RenderWindow & window);

void drawCircles(vector<Point> & route, sf::RenderWindow & window);

void drawRoute( vector<Point> & route, sf::RenderWindow & window );

void permute( vector<Point> & route );

void drawRoute(sf::RenderWindow * window, SynchronizedRoute * sroute);


void taniec( sf::RenderWindow * window, SynchronizedRoute * sroute );

int main(int argc, const char * argv[]) {
    
    srand (time(NULL));
    
    vector<Point> route;
    generateRoute(route, SIZE);
    std::mutex routeMutex;
    
    SynchronizedRoute * sr = new SynchronizedRoute( route, routeMutex );
    
    sf::RenderWindow * window = new sf::RenderWindow( sf::VideoMode(X_SIZE, Y_SIZE), "My Window");

    std::thread t(taniec, window, sr) ;

    
//    drawRoute(window, sr);
    std::this_thread::sleep_for (std::chrono::seconds(5));
    

    t.join();
    std::this_thread::sleep_for (std::chrono::seconds(5));

    
    return 0;
}

void taniec( sf::RenderWindow * window, SynchronizedRoute * sroute){
    cout << 2 << " " << "DZIEŃ DOBRY DZIKIE BOBRY!" << endl;
        while( window->isOpen() ){
//            sf::Event event;
//    
//            while( window->pollEvent(event)){
//                if( event.type == sf::Event::Closed )
//                    window->close();
//    
//            }
//    

            sroute->routeMutex.lock();
            if( sroute->updated ){
                cout << "XD \n";
                window->clear();
                drawRoute( sroute->route, *window );
                window->display();
            }
            sroute->routeMutex.unlock();
    
            std::this_thread::sleep_for (std::chrono::milliseconds(10));
        }
    cout << " trole\n ";

}


sf::Color generateRandomColor(){
    return sf::Color(rand()%255, rand()%255,rand()%255);
}

void createCircle(Point & point, sf::CircleShape & circle){
    circle.setPosition(point.x - circle.getRadius(), point.y - circle.getRadius());
    circle.setFillColor(sf::Color(100,250,50));
}

void drawLine( Point & first, Point & second, sf::RenderWindow & window ){
    sf::Vertex line[] = {
        sf::Vector2f(sf::Vector2f(first.x, first.y)),
        sf::Vector2f(sf::Vector2f(second.x, second.y))
    };
    
    line[0].color = generateRandomColor();
    line[1].color = generateRandomColor();
    
    window.draw(line, 2, sf::Lines);
}

void generateRoute( vector<Point>& route, int size ){
    route.clear();
    for( int i = 0 ; i < size ; ++i ){
        int x = rand() % X_SIZE;
        int y = rand() % Y_SIZE;
        
        Point point( x, y );
        
        route.push_back(point);
    }
}

void drawPaths(vector<Point> & route, sf::RenderWindow & window){
    for( int i = 0; i < route.size()-1 ; ++i ){
        drawLine( route[ i ], route[ i + 1 ], window);
    }
    drawLine( route[ route.size() - 1 ], route[ 0 ], window);
}

void drawCircles(vector<Point> & route, sf::RenderWindow & window){
    for( auto point : route ){
        sf::CircleShape circle(RADIUS);
        createCircle(point, circle);
        window.draw(circle);
    }
}

void drawRoute( vector<Point> & route, sf::RenderWindow & window ){
    drawPaths(route, window);
    drawCircles(route, window);
}

void permute( vector<Point> & route ){
    int permNumber = rand()%5;
    
    for( int i = 0 ; i < permNumber ; ++i ){
        int first = rand() % route.size();
        int second = rand() % route.size();
        
        swap( route[ first ], route[ second ]);
    }
}

void drawRoute(sf::RenderWindow * window, SynchronizedRoute * sroute){
    while( window->isOpen() ){
        sf::Event event;
        
        while( window->pollEvent(event)){
            if( event.type == sf::Event::Closed )
                window->close();
            
        }
        
        
        sroute->routeMutex.lock();
        if( sroute->updated ){
            window->clear();
            drawRoute( sroute->route, *window );
            window->display();
        }
        sroute->routeMutex.lock();
        
        std::this_thread::sleep_for (std::chrono::milliseconds(10));
    }
}
