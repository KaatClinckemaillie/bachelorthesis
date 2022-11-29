#pragma once

#include "ofMain.h"
#include "Lightbol.h"
#include "Player.h"
#include "ofxSimpleSerial.h"


class ofApp : public ofBaseApp{

	
public:
    void setup();
    void setupVideo();
    void update();
    void draw();
    void drawVideo(ofEventArgs & args);
    void keyReleased(int key);
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void windowResized(int w, int h);
    void update_lightbols();
    void check_lightbols_collision();
    void add_lightbol();
    void update_players();
    int round_position(float num);

    
    
    //technical setup
    // OOK IN ARDUINO VERANDEREN!!!
    int heightTable = 40;
    
    
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
        
    
    std::string positions;
    std::string prev_positions;
    
    // arduino

    char  bytesRead[4];  // data from serial, we will be trying to read 3
    char bytesReadString[5]; // a string needs a null terminator, so we need 3 + 1 bytes
    int nBytesRead; // how much did we read?
    int nTimesRead; // how many times did we read?
    float readTime; // when did we last read?
    
    std::string firstCharacter;
    std::string secondCharacter;
    
    ofSerial serial;

            
    
    //char byteData[4];
    int position = 50;
    
    vector <int> bytesData;
    
    vector <Lightbol> lightbols;
    vector <Player> players;
    
    // colors of the sticks and bolls
    // yellow , green, blue, pink
    int colors[4][3] = {{245, 215, 64},{1, 157, 89},{20, 37, 234},{253, 175, 221}};
    
    // hangt van de stokken van de tafel af
    int x_positions[4] = {30, 70, 110, 150};
    int y_positions[4] = {0,0,0,0};
    int prev_y_positions[4] = {0,0,0,0};
    
    
        
};
