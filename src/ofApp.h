#pragma once

#include "ofMain.h"
#include "Lightbol.h"



class ofApp : public ofBaseApp{

	
public:
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
    void keyPressed(int key);
    void update_lightbols();
    void check_lightbols_collision();
    
    //game setup
    string game_state;
    int score;
        
    // arduino
    ofSerial    serial;
    string sensorValue;
    int byteData;
    int position = 50;
    
    vector <Lightbol> lightbols;
    
    // colors of the sticks and bolls
    // yellow , green, blue, pink
    int colors[4][3] = {{245, 215, 64},{1, 157, 89},{20, 37, 234},{253, 175, 221}};
        
};
