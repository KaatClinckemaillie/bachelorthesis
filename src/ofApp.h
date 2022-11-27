#pragma once

#include "ofMain.h"
#include "Lightbol.h"
#include "Player.h"
#include "ofxBox2d.h"


class ofApp : public ofBaseApp{

	
public:
    void setup();
    void setupVideo();
    void update();
    void draw();
    void drawVideo(ofEventArgs & args);
    void keyReleased(int key);
    void keyPressed(int key);
    void windowResized(int w, int h);
    void update_lightbols();
    void check_lightbols_collision();
    void add_lightbol();
    
    
    
    //game setup
    int width = 1220;
    int height = 760;
    ofPoint nulPos;
    string game_state;
    int score = 0;
    int speed = 10;
    int catched_lightballs = 0;
    float nextLightbolSeconds = 0;
    int level;
        
    // arduino
    ofSerial    serial;
    string sensorValue;
    int byteData;
    int position = 50;
    

    
    vector <Lightbol> lightbols;
    vector <Player> players;
    
    // colors of the sticks and bolls
    // yellow , green, blue, pink
    int colors[4][3] = {{245, 215, 64},{1, 157, 89},{20, 37, 234},{253, 175, 221}};
    
    // hangt van de stokken van de tafel af
    int x_positions[4] = {30, 70, 110, 150};
    
    
        
};
